import 'dart:async';
import 'dart:convert';

import 'package:bms/helpers/db_helper.dart';
import 'package:bms/providers/cells.dart';
import 'package:bms/helpers/notifications_helper.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter_blue/flutter_blue.dart';
import 'package:intl/intl.dart';

const String Current_data_service = "0000180f-0000-1000-8000-00805f9b34fb";
const String Alarming_service = "00001802-0000-1000-8000-00805f9b34fb";
const Device_name = "00002a00-0000-1000-8000-00805f9b34fb";
const Temperature = "00002a6e-0000-1000-8000-00805f9b34fb";
const Current = "00002ae0-0000-1000-8000-00805f9b34fb";
const Voltage = "00002ae1-0000-1000-8000-00805f9b34fb";
const SOC = "00002a19-0000-1000-8000-00805f9b34fb";

class BTHelper with ChangeNotifier {
  List<Cell> _cells;
  set cells(List<Cell> cells) {
    _cells = cells;
  }

  FlutterBlue flutterBlue = FlutterBlue.instance;
  List<BluetoothDevice> _devices = [];
  List<bool> _devicesStates = [];
  BluetoothDevice _connectedDevice;
  BluetoothDevice targetDevice;
  List<BluetoothService> _sevices = [];
  int temp, sOC, id;
  double current, volt;
  Future<void> getDevices() async {
    flutterBlue.stopScan();
    StreamSubscription subscription;
    flutterBlue
        .startScan(timeout: Duration(seconds: 5))
        .then((value) => subscription.cancel());
    subscription =
        flutterBlue.scanResults.listen((List<ScanResult> results) async {
      // do something with scan results
      for (ScanResult r in results) {
        if (!_devices.any((element) => element.id == r.device.id)) {
          _devices.add(r.device);
          _devicesStates.add(false);
          notifyListeners();
        }
      }
    });
    flutterBlue.connectedDevices.asStream().listen((event) async {
      for (BluetoothDevice bd in event) {
        if (!_devices.contains(bd)) {
          _devices.add(bd);
          _devicesStates.add(true);
          _connectedDevice = bd;
          _sevices = await _connectedDevice.discoverServices();
          notifyListeners();
        }
        print(bd.id);
      }
    });
    print(_devices.length);
  }

  Future<void> disConnect() async {
    if (_connectedDevice == null) return;
    await _connectedDevice.disconnect();
    for (var item in _devicesStates) {
      item = false;
    }
    notifyListeners();
  }

  Future<bool> connect(int index) async {
    flutterBlue.stopScan();
    try {
      await _devices[index].connect(autoConnect: false);
      _connectedDevice = _devices[index];
      _connectedDevice.state.listen((event) async {
        if (event == BluetoothDeviceState.disconnected) {
          _sevices = [];
          _connectedDevice = null;
          _devicesStates = [];
          _devices = [];
          notifyListeners();
        }
      });
      await discoverServices();
      List<BluetoothDevice> _connectedDevices =
          await flutterBlue.connectedDevices;
      for (var i = 0; i < _connectedDevices.length; i++) {
        if (_devices[index] == _connectedDevices[i]) {
          _devicesStates[index] = true;
          notifyListeners();
          return true;
        }
      }

      notifyListeners();
    } catch (e) {
      print(e);
    }
    return false;
  }

  Future<void> discoverServices() async {
    if (_connectedDevice == null) return;
    print(_connectedDevice.name);
    _sevices = await _connectedDevice.discoverServices();
    notifyListeners();
    await getData();
  }

  Future<void> getData() async {
    try {
      bool _isListinig = false;
      _sevices.forEach((service) {
        if (service.uuid.toString() == Current_data_service) {
          service.characteristics.forEach((charac) async {
            if (charac.uuid.toString() == Device_name) {
              await charac.setNotifyValue(true);
              charac.value.listen((value) async {
                if (value != [0x00] && value != [] && !_isListinig) {
                  Timer _timer = Timer(Duration(seconds: 2), () {
                    _isListinig = false;
                  });
                  _isListinig = true;

                  print(value);
                  if (value != [] && _connectedDevice != null) {
                    id = value[0];
                    service.characteristics.forEach((charac) async {
                      if (charac.uuid.toString() == Current &&
                          _connectedDevice != null) {
                        Future.delayed(Duration(milliseconds: 400), () async {
                          try {
                            List<int> data = await charac.read();
                            if (data != []) current = data[0].toDouble() / 100;
                            //print(current);
                            //print('current');
                          } catch (e) {
                            return;
                          }
                        });
                      }
                      if (charac.uuid.toString() == Voltage &&
                          _connectedDevice != null) {
                        await Future.delayed(Duration(milliseconds: 800),
                            () async {
                          try {
                            List<int> data = await charac.read();
                            if (data != [] && _connectedDevice != null)
                              volt = data[0].toDouble() / 10;
                          }
                          //print(volt);
                          //print('volt');
                          catch (e) {
                            return;
                          }
                        });
                      }
                      if (charac.uuid.toString() == SOC &&
                          _connectedDevice != null) {
                        await Future.delayed(Duration(milliseconds: 1200),
                            () async {
                          try {
                            List<int> data = await charac.read();
                            if (data != [] && _connectedDevice != null)
                              sOC = data[0];
                          } catch (e) {
                            return;
                          }
                          //print(sOC);
                          //print('Soc');
                        });
                      }
                      if (charac.uuid.toString() == Temperature &&
                          _connectedDevice != null) {
                        await Future.delayed(Duration(milliseconds: 1600),
                            () async {
                          try {
                            List<int> data = await charac.read();
                            if (data != [] && _connectedDevice != null)
                              temp = data[0];
                          } catch (e) {
                            return;
                          }
                          //print(temp);
                          //print('temp');
                        });
                      }
                    });
                    Cell cell;
                    if (id != null) {
                      _cells[id.toInt() - 1] = (Cell(
                        id: id,
                        temp: temp,
                        current: current,
                        volt: volt,
                        sOC: sOC,
                      ));
                      notifyListeners();
                      try {
                        await charac.write([0x00]);
                      } catch (e) {
                        return;
                      }
                      cell = _cells[id.toInt() - 1];
                    }
                    if (cell.id != null &&
                        cell.current != null &&
                        cell.volt != null &&
                        cell.temp != null) {
                      await DBHelper.insert('cells_data', {
                        'id': cell.id,
                        'temp': cell.temp,
                        'volt': cell.volt,
                        'current': cell.current,
                        'time': DateFormat("yy/MM/dd - HH:mm")
                            .format(DateTime.now())
                            .toString(),
                      });
                      if (temp > 80) {
                        LocalNotification().cancelAllNotifications();
                        LocalNotification().showNotification(
                            channelID: "Warnning",
                            channelName: "Warnning",
                            channelDesc: "channelDesc",
                            notificationTitle: "Temp is High",
                            notificationBody:
                                "Temp in Cell ${cell.id} is High its ${temp}C");
                      } else if (temp < 10) {
                        LocalNotification().cancelAllNotifications();
                        LocalNotification().showNotification(
                          channelID: "Warnning",
                          channelName: "Warnning",
                          channelDesc: "channelDesc",
                          notificationTitle: "Temp is Low",
                          notificationBody:
                              "Temp in Cell ${cell.id} is Low its ${temp}C",
                        );
                      }
                      if (volt > 4.2) {
                        LocalNotification().cancelAllNotifications();
                        LocalNotification().showNotification(
                          channelID: "Warnning",
                          channelName: "Warnning",
                          channelDesc: "channelDesc",
                          notificationTitle: "Volt is High",
                          notificationBody:
                              "Volt in Cell ${cell.id} is High its ${volt}C",
                        );
                      }
                      if (volt < 3.2) {
                        LocalNotification().cancelAllNotifications();
                        LocalNotification().showNotification(
                          channelID: "Warnning",
                          channelName: "Warnning",
                          channelDesc: "channelDesc",
                          notificationTitle: "Volt is Low",
                          notificationBody:
                              "Volt in Cell ${cell.id} is Low its ${volt}C",
                        );
                      }
                    }
                    notifyListeners();
                  }
                }
              });
            }
          });
        }
      });
    } catch (e) {
      print(e);
      return;
    }
  }

  writeData(String data, BluetoothCharacteristic targetCharacteristic) {
    if (targetCharacteristic == null) return;
    List<int> bytes = utf8.encode(data);
    targetCharacteristic.write(bytes);
  }

  Future<String> readData(BluetoothCharacteristic targetCharacteristic) async {
    // ignore: unnecessary_null_comparison
    if (targetCharacteristic == null) return null;
    String data = String.fromCharCodes(await targetCharacteristic.read());
    return data;
  }

  List<BluetoothDevice> get devices {
    return [..._devices];
  }

  List<bool> get devicesStates {
    return [..._devicesStates];
  }

  List<BluetoothService> get sevices {
    return [..._sevices];
  }

  String get connectedDeviceName {
    return _connectedDevice == null ? "No device Yet" : _connectedDevice.name;
  }
}
