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
    notifyListeners();
  }

  Future<bool> connect(int index) async {
    flutterBlue.stopScan();
    try {
      await _devices[index].connect(autoConnect: false);
      _connectedDevice = _devices[index];
      _connectedDevice.state.listen((event) {
        if (event == BluetoothDeviceState.disconnected) {
          _sevices = [];
          _connectedDevice = null;
          _devicesStates = [];
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
      throw e;
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
    _sevices.forEach((service) {
      if (service.uuid.toString() == Current_data_service) {
        service.characteristics.forEach((charac) async {
          if (charac.uuid.toString() == Device_name) {
            await charac.setNotifyValue(true);
            charac.value.listen((value) async {
              if (value != [0x00] && value != []) {
                print(value);
                if (value[0] != null) id = value[0];
                service.characteristics.forEach((charac) async {
                  if (charac.uuid.toString() == Current) {
                    Future.delayed(Duration(milliseconds: 200), () async {
                      List<int> data = await charac.read();
                      if (data[0] != null) current = data[0].toDouble() / 100;
                      //print(current);
                      //print('current');
                    });
                  }
                  if (charac.uuid.toString() == Voltage) {
                    await Future.delayed(Duration(milliseconds: 400), () async {
                      List<int> data = await charac.read();
                      if (data[0] != null) volt = data[0].toDouble() / 10;
                      //print(volt);
                      //print('volt');
                    });
                  }
                  if (charac.uuid.toString() == SOC) {
                    await Future.delayed(Duration(milliseconds: 600), () async {
                      List<int> data = await charac.read();
                      if (data[0] != null) sOC = data[0];
                      //print(sOC);
                      //print('Soc');
                    });
                  }
                  if (charac.uuid.toString() == Temperature) {
                    await Future.delayed(Duration(milliseconds: 800), () async {
                      List<int> data = await charac.read();
                      if (data[0] != null) temp = data[0];
                      //print(temp);
                      //print('temp');
                    });
                  }
                });
                _cells[id.toInt() - 1] = (Cell(
                  id: id,
                  temp: temp,
                  current: current,
                  volt: volt,
                  sOC: sOC,
                ));
                notifyListeners();
                await charac.write([0x00]);
                Cell cell = _cells[id.toInt() - 1];
                await DBHelper.insert('cells_data', {
                  'id': cell.id,
                  'temp': cell.temp,
                  'volt': cell.volt,
                  'current': cell.current,
                  'time': DateFormat("yy/MM/dd - HH:mm")
                      .format(DateTime.now())
                      .toString(),
                });
                notifyListeners();
                if (temp > 40) {
                  LocalNotification().cancelAllNotifications();
                  LocalNotification().showNotification(
                      channelID: "Warnning",
                      channelName: "Warnning",
                      channelDesc: "channelDesc",
                      notificationTitle: "Temp is high",
                      notificationBody:
                          "Temp in Cell ${cell.id} is high its ${temp}C");
                }
                if (current > 40) {
                  LocalNotification().cancelAllNotifications();
                  LocalNotification().showNotification(
                      channelID: "Warnning",
                      channelName: "Warnning",
                      channelDesc: "channelDesc",
                      notificationTitle: "Temp is high",
                      notificationBody:
                          "Current in Cell ${cell.id} is high its ${current}C");
                }
                if (volt > 40) {
                  LocalNotification().cancelAllNotifications();
                  LocalNotification().showNotification(
                      channelID: "Warnning",
                      channelName: "Warnning",
                      channelDesc: "channelDesc",
                      notificationTitle: "Temp is high",
                      notificationBody:
                          "Volt in Cell ${cell.id} is high its ${volt}C");
                }
              }
            });
          }
        });
      }
    });
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

/* import 'dart:async';
import 'dart:typed_data';

import 'package:bms/providers/cells.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter_ble_lib/flutter_ble_lib.dart' as BM;
import 'package:flutter_blue/flutter_blue.dart';
//import 'package:flutter_blue/flutter_blue.dart' as FB;

const String Current_data_service = "0000180f-0000-1000-8000-00805f9b34fb";
const String Alarming_service = "00001802-0000-1000-8000-00805f9b34fb";
const Device_name = "00002a00-0000-1000-8000-00805f9b34fb";
const Temperature = "00002a6e-0000-1000-8000-00805f9b34fb";
const Current = "00002ae0-0000-1000-8000-00805f9b34fb";
const Voltage = "00002ae1-0000-1000-8000-00805f9b34fb";
const SOC = "00002a19-0000-1000-8000-00805f9b34fb";

class BTHelper with ChangeNotifier {
  final Cells _cells;
  BM.BleManager bleManager = BM.BleManager();
  BTHelper(this._cells) {
    bleManager.createClient();
    bleManager.observeBluetoothState().listen((btState) {
      print(btState);
      _isbluetoothEnabled = btState == BM.BluetoothState.POWERED_ON;
      notifyListeners();
      //do your BT logic, open different screen, etc.
    });
  }

  //var defintions
  BluetoothState bluetoothState;
  BluetoothDevice _connectedDevice;
  List<BluetoothDevice> _devices = [];
  List<bool> _devicesStates = [];
  List<BluetoothService> _services = [];
  bool _isbluetoothEnabled;
  int _temp, _current, _volt, _sOC;
  FlutterBlue flutterBlue = FlutterBlue.instance;
  StreamSubscription subscription;
  Future<void> getDevices() async {
    flutterBlue.stopScan();
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
        }
      }
      notifyListeners();
    });
    flutterBlue.connectedDevices.asStream().listen((event) async {
      for (BluetoothDevice bd in event) {
        if (!_devices.contains(bd)) {
          _devices.add(bd);
          _devicesStates.add(true);
          _connectedDevice = bd;
        }
      }
      notifyListeners();
    });
    print(_devices.length);
  }

  Future<bool> connect(int index) async {
    flutterBlue.stopScan();
    try {
      await _devices[index].connect();
      _connectedDevice = _devices[index];
      _connectedDevice.state.listen((event) {
        if (event == BluetoothDeviceState.disconnected) {
          /* _services = [];
          _connectedDevice = null;
          _devicesStates = []; */
          print("disconnected");
          print(event);
        }
      });
      notifyListeners();
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
      throw e;
    }
    return false;
  }

  Future<void> discoverServices() async {
    if (_connectedDevice == null) return;
    print(_connectedDevice.name);
    _services = await _connectedDevice.discoverServices();
    notifyListeners();
    await getData();
  }

  getData() async {
    print("Iam here");
    print(_services.length);
    _services.forEach((service) {
      print(service.uuid.toString());
      if (service.uuid.toString() == Current_data_service) {
        service.characteristics.forEach((charac) async {
          if (charac.uuid.toString() == Current) {
            Future.delayed(Duration(milliseconds: 200), () async {
              List<int> data = await charac.read();
              _current = data[0];
              print(_current);
              print('current');
            });
          }
          if (charac.uuid.toString() == Voltage) {
            Future.delayed(Duration(milliseconds: 400), () async {
              List<int> data = await charac.read();
              _volt = data[0];
              print(_volt);
              print('volt');
            });
          }
          if (charac.uuid.toString() == SOC) {
            Future.delayed(Duration(milliseconds: 600), () async {
              List<int> data = await charac.read();
              _sOC = data[0];
              print(_sOC);
              print('Soc');
            });
          }
          if (charac.uuid.toString() == Temperature) {
            Future.delayed(Duration(milliseconds: 800), () async {
              List<int> data = await charac.read();
              _temp = data[0];
              print(_temp);
              print('temp');
            });
          }
          if (charac.uuid.toString() == Device_name) {
            Future.delayed(Duration(milliseconds: 1000), () async {
              List<int> data = await charac.read();
              await _cells.setCellValue(Cell(
                id: data[0],
                temp: _temp,
                current: _current,
                volt: _volt,
                sOC: _sOC,
              ));
              await charac.write([0x00]);
              print(data.toString());
              print('here');
            });
            notifyListeners();
          }
        });
      }
    });
  }

  // methods
  Future<void> enableBluetooth() async {
    await bleManager.enableRadio();
  }

  Future<void> disbleBluetooth() async {
    await bleManager.disableRadio();
  }

  // geters
  List<BluetoothDevice> get devices {
    return [..._devices];
  }

  List<BluetoothService> get sevices {
    return [..._services];
  }

  List<bool> get devicesStates {
    return [...devicesStates];
  }

  String get connectedDeviceName {
    return _connectedDevice == null ? "No device Yet" : _connectedDevice.name;
  }

  bool get isEnabled {
    return _isbluetoothEnabled;
  }
}

/* FlutterBlue flutterBlue = FlutterBlue.instance;
  List<BluetoothDevice> _devices = [];
  List<bool> _devicesStates = [];
  BluetoothDevice _connectedDevice;
  List<BluetoothBluetoothService> _services = [];
  int _temp, _current, _volt, _sOC;
  
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
  
  Future<void> getDevices() async {
    print("bla");
    /* StreamSubscription subscription;
    List<String> uuids = [];
    flutterBlue.stopScan();
    flutterBlue
        .startScan(timeout: Duration(seconds: 5))
        .then((value) => subscription.cancel());
    subscription =
        flutterBlue.scanResults.listen((List<FB.ScanResult> results) async {
      // do something with scan results
      for (FB.ScanResult r in results) {
        r.device.
      }
    });
    flutterBlue.connectedDevices.asStream().listen((event) async {
      for (FB.BluetoothDevice bd in event) {
        
      }
    }); */
    bleManager.stopBluetoothDeviceScan();
    Future.delayed(Duration(seconds: 6), () => bleManager.stopBluetoothDeviceScan());
    bleManager
        .startBluetoothDeviceScan(scanMode: ScanMode.lowLatency)
        .listen((scanresult) async {
      print(
          "Scanned BluetoothDevice ${scanresult.BluetoothDevice.name}, RSSI ${scanresult.rssi}");
      bleManager.stopBluetoothDeviceScan();
      /* _devices.add(scanresult.BluetoothDevice);
      _devicesStates.add(false); */
      notifyListeners();
    });
    print(_devices);
  }

  Future<bool> connect(int index) async {
    bleManager.stopBluetoothDeviceScan();
    await _devices[index].connect();
    _devices[index]
        .observeConnectionState(
            completeOnDisconnect: true, emitCurrentValue: true)
        .listen((connectionState) async {
      _devicesStates[index] = await _devices[index].isConnected();
    });
    if (_devicesStates[index]) _connectedDevice = _devices[index];
    notifyListeners();
    print(_connectedDevice);
    await discoverBluetoothServices();
    return _devicesStates[index];
  }

  Future<void> discoverBluetoothServices() async {
    bleManager.stopBluetoothDeviceScan();
    if (_connectedDevice == null) return;
    print(_connectedDevice.name);
    await _connectedDevice.discoverAllBluetoothServicesAndCharacteristics();
    _services = await _connectedDevice.services();
    notifyListeners();
    await getData();
  }

  getData() async {
    print("Iam here");
    print(_services.length);
    _services.forEach((service) async {
      print(service.uuid.toString());
      if (service.uuid.toString() == Current_data_service) {
        List<Characteristic> chars = await service.characteristics();
        chars.forEach((charac) async {
          if (charac.uuid .toString()== Current) {
            Future.delayed(Duration(milliseconds: 200), () async {
              List<int> data = await charac.read();
              _current = data[0];
              print(_current);
              print('current');
            });
          }
          if (charac.uuid .toString()== Voltage) {
            Future.delayed(Duration(milliseconds: 400), () async {
              List<int> data = await charac.read();
              _volt = data[0];
              print(_volt);
              print('volt');
            });
          }
          if (charac.uuid .toString()== SOC) {
            Future.delayed(Duration(milliseconds: 600), () async {
              List<int> data = await charac.read();
              _sOC = data[0];
              print(_sOC);
              print('Soc');
            });
          }
          if (charac.uuid .toString()== Temperature) {
            Future.delayed(Duration(milliseconds: 800), () async {
              List<int> data = await charac.read();
              _temp = data[0];
              print(_temp);
              print('temp');
            });
          }
          if (charac.uuid .toString()== Device_name) {
            Future.delayed(Duration(milliseconds: 1000), () async {
              List<int> data = await charac.read();
              await _cells.setCellValue(Cell(
                id: data[0],
                temp: _temp,
                current: _current,
                volt: _volt,
                sOC: _sOC,
              ));
              await charac.write(Uint8List.fromList([0]), false);
              print(data.toString());
              print('here');
            });
            notifyListeners();
          }
        });
      }
    });
  }
  */
 */
