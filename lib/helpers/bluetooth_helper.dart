import 'dart:async';
import 'dart:convert';

import 'package:flutter/cupertino.dart';
import 'package:flutter_blue/flutter_blue.dart';

const Current_data_service = '180f';
const Alarming_service = "1802";
const Device_name = "2A00";
const Temperature = "2A6E";
const Current = "2AEE";
const Voltage = "2B18";
const SOC = "2A19";

class BTHelper with ChangeNotifier {
  FlutterBlue flutterBlue = FlutterBlue.instance;
  List<BluetoothDevice> _devices = [];
  bool isConnected = false;
  var _connectedDevice;
  BluetoothDevice targetDevice;
  Future<void> getDevices() async {
/*     _devices = await FlutterBluetoothSerial.instance.getBondedDevices();
    notifyListeners(); */
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
          _devices.insert(0, r.device);
          print('${r.device.name} found! rssi: ${r.rssi}');
          print(r.advertisementData);
          print(r.device.id);
          print(_devices.length);
          if (r.device.name == 'ESP32') {
            print('found');
            targetDevice = r.device;
            subscription.cancel();
            flutterBlue.stopScan();
            try {
              await targetDevice.connect();
              await discoverServices();
              // ignore: unrelated_type_equality_checks
              if (targetDevice.state == BluetoothDeviceState.connected) {
                isConnected = true;
                _connectedDevice = targetDevice;
              }
              notifyListeners();
            } catch (e) {
              print(e);
              print(isConnected);
              print(targetDevice.name);
            }
          }
        }
      }
      notifyListeners();
    });
    flutterBlue.connectedDevices.asStream().listen((event) {
      for (BluetoothDevice bd in event) {
        if (!_devices.contains(bd)) _devices.add(bd);
        print(bd.id);
      }
      notifyListeners();
    });
    print(_devices.length);
  }

  Future<bool> connect(int index) async {
    flutterBlue.stopScan();
    try {
      await _devices[index].connect();
      await discoverServices();
      if (_devices[index].state == BluetoothDeviceState.connected) {
        isConnected = true;
        _connectedDevice = targetDevice;
      }
      notifyListeners();
    } catch (e) {
      print(e);
    }

    return isConnected;
  }

  discoverServices() async {
    if (_connectedDevice == null) return;

    List<BluetoothService> services = await _connectedDevice.discoverServices();
    services.forEach((service) {
      if (service.uuid.toString() == Current_data_service) {
        service.characteristics.forEach((charac) {
          double temp, current, volt, sOC;
          if (charac.uuid.toString() == Device_name) {
            charac.value.listen((event) async {
              // set all data
              current = double.parse(await readData(service.characteristics
                  .firstWhere(
                      (element) => element.uuid.toString() == Current)));
              volt = double.parse(await readData(service.characteristics
                  .firstWhere(
                      (element) => element.uuid.toString() == Voltage)));
              temp = double.parse(await readData(service.characteristics
                  .firstWhere(
                      (element) => element.uuid.toString() == Temperature)));
              sOC = double.parse(await readData(service.characteristics
                  .firstWhere((element) => element.uuid.toString() == SOC)));
              writeData('00', charac);
            });
          }
        });
      }
      print(service.uuid.toString());
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
}