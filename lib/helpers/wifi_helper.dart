/* import 'dart:async';

import 'package:flutter/cupertino.dart';
import 'package:flutter_p2p/flutter_p2p.dart';
import 'package:flutter_p2p/gen/protos/protos.pb.dart';

class WifiHelper with ChangeNotifier, WidgetsBindingObserver {
  List<StreamSubscription> _subscriptions = [];
  List<WifiP2pDevice> _peers = [];

  List<WifiP2pDevice> get peers {
    return [..._peers];
  }

  static Future<bool> checkPermission() async {
    if (!await FlutterP2p.isLocationPermissionGranted()) {
      await FlutterP2p.requestLocationPermission();
      return false;
    }
    return true;
  }

  void register() async {
    if (!await WifiHelper.checkPermission()) {
      return;
    }
    WifiHelper()
        ._subscriptions
        .add(FlutterP2p.wifiEvents.stateChange.listen((change) {
      // Handle wifi state change
    }));

    WifiHelper()
        ._subscriptions
        .add(FlutterP2p.wifiEvents.connectionChange.listen((change) {
      // Handle changes of the connection
    }));

    WifiHelper()
        ._subscriptions
        .add(FlutterP2p.wifiEvents.thisDeviceChange.listen((change) {
      // Handle changes of this device
    }));

    WifiHelper()
        ._subscriptions
        .add(FlutterP2p.wifiEvents.peersChange.listen((change) {
      _peers = change.devices;
      notifyListeners();
    }));

    WifiHelper()
        ._subscriptions
        .add(FlutterP2p.wifiEvents.discoveryChange.listen((change) {
      // Handle discovery state changes
    }));

    FlutterP2p
        .register(); // Register to the native events which are send to the streams above
    WidgetsBinding.instance.addObserver(this);
  }

  void unregister() {
    WifiHelper()._subscriptions.forEach(
        (subscription) => subscription.cancel()); // Cancel subscriptions
    FlutterP2p.unregister(); // Unregister from native events
    WidgetsBinding.instance.removeObserver(this);
  }

  static Future<void> discover() async {
    await FlutterP2p.discoverDevices();
    print(WifiHelper().peers[0].deviceName);
  }
}
 */