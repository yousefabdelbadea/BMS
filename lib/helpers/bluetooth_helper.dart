import 'package:flutter/cupertino.dart';
import 'package:flutter_blue/flutter_blue.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart' as BS;

class BTHelper with ChangeNotifier {
  FlutterBlue flutterBlue = FlutterBlue.instance;
  List<BluetoothDevice> _devices = [];
  Future<void> getDevices() async {
/*     _devices = await FlutterBluetoothSerial.instance.getBondedDevices();
    notifyListeners(); */
    flutterBlue.stopScan();
    flutterBlue.startScan(timeout: Duration(seconds: 5));
    _devices = [];
    notifyListeners();
    flutterBlue.scanResults.listen((List<ScanResult> results) {
      // do something with scan results
      for (ScanResult r in results) {
        if (!_devices.contains(r.device)) {
          _devices.add(r.device);
          print(r.device.name);
        }
      }
      notifyListeners();
    });
    flutterBlue.connectedDevices.asStream().listen((event) {
      for (BluetoothDevice bd in event) {
        if (!_devices.contains(bd)) _devices.add(bd);
      }
      notifyListeners();
    });
  }

  Future<bool> enableBluttoth() async {
    return await BS.FlutterBluetoothSerial.instance.requestEnable();
  }

  Future<bool> disableBluttoth() async {
    _devices = [];
    notifyListeners();
    return await BS.FlutterBluetoothSerial.instance.requestDisable();
  }

  Future<void> openSettings() async {
    await BS.FlutterBluetoothSerial.instance.openSettings();
  }

  Future<bool> connect(int index) async {
    flutterBlue.stopScan();
    try {
      await _devices[index].connect();
    } catch (e) {
      print(e);
      return false;
    }
    return true;
    /* BluetoothConnection _bluetoothConnection;
    try {
      _bluetoothConnection = await BluetoothConnection.toAddress(address);
      return _bluetoothConnection.isConnected ? true : false;
    } catch (e) {
      print(e);
    } */
  }

  List<BluetoothDevice> get devices {
    return [..._devices];
  }
}
