import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:bms/widgets/app_drawer.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class CarConnection extends StatefulWidget {
  static const String routeName = "/blueConnectScreen";
  @override
  _CarConnectionState createState() => _CarConnectionState();
}

class _CarConnectionState extends State<CarConnection> {
  @override
  void didChangeDependencies() async {
    await Provider.of<BTHelper>(context, listen: false).getDevices();
    super.didChangeDependencies();
  }

  @override
  Widget build(BuildContext context) {
    String deviceName = Provider.of<BTHelper>(context).connectedDeviceName;
    return Scaffold(
      appBar: AppBar(
        actions: [
          TextButton.icon(
            onPressed: () {
              deviceName = Provider.of<BTHelper>(context, listen: false)
                  .connectedDeviceName;
            },
            icon: Icon(Icons.car_rental),
            label: Text(deviceName),
          )
        ],
        leading: Builder(builder: (context) {
          return Padding(
            padding: EdgeInsets.only(left: 5),
            child: Hero(
              child: TextButton(
                child: Image.asset('assets/images/logo.png'),
                onPressed: () => Scaffold.of(context).openDrawer(),
              ),
              tag: 'logo',
            ),
          );
        }),
      ),
      drawer: AppDrawer(),
      body: RefreshIndicator(
        onRefresh: () =>
            Provider.of<BTHelper>(context, listen: false).getDevices(),
        child: Column(
          children: [
            /* Padding(
              padding: const EdgeInsets.all(8.0),
              child: ListTile(
                title: Text('Enable Bluetooth'),
                trailing: Switch(
                    value: bluetoothData.isEnabled,
                    onChanged: (value) async {
                      bluetoothData.isEnabled
                          ? await Provider.of<BTHelper>(context, listen: false)
                              .disbleBluetooth()
                          : await Provider.of<BTHelper>(context, listen: false)
                              .enableBluetooth();
                    }),
              ),
            ), */
            Expanded(
              child: FutureBuilder(
                future:
                    Provider.of<BTHelper>(context, listen: false).getDevices(),
                builder: (ctx, data) => data.connectionState ==
                        ConnectionState.waiting
                    ? Center(
                        child: CircularProgressIndicator(),
                      )
                    : Consumer<BTHelper>(builder: (ctx, devices, _) {
                        return ListView.builder(
                          itemBuilder: (ctx, i) => ListTile(
                            onTap: () => devices.discoverServices(),
                            title: Text(devices.devices[i].name),
                            trailing: TextButton(
                              child: devices.devicesStates.isEmpty
                                  ? null
                                  : devices.devicesStates[i]
                                      ? Text('Connected')
                                      : Text('Connect'),
                              onPressed: () async {
                                if (!devices.devicesStates[i]) {
                                  try {
                                    bool newValue = await devices.connect(i);
                                    newValue == false
                                        ? ScaffoldMessenger.of(context)
                                            .showSnackBar(
                                            SnackBar(
                                              content: Text(
                                                  'Error in connecection !'),
                                            ),
                                          )
                                        : ScaffoldMessenger.of(context)
                                            .showSnackBar(
                                            SnackBar(
                                              content:
                                                  Text('Device Connected!'),
                                            ),
                                          );
                                  } catch (e) {
                                    showDialog(
                                      context: context,
                                      builder: (ctx) => AlertDialog(
                                        title: Text('Error in connection'),
                                        content: Text(e.toString()),
                                      ),
                                    );
                                  }
                                } else {
                                  showDialog(
                                    context: context,
                                    builder: (ctx) => AlertDialog(
                                      title: Text('Already Connected'),
                                      content: Text('Want to disconnect!'),
                                      actions: [
                                        TextButton(
                                            onPressed: () async {
                                              /* await Provider.of<BTHelper>(
                                                      context,
                                                      listen: false)
                                                  .disConnect(); */
                                            },
                                            child: Text('Yes'))
                                      ],
                                    ),
                                  );
                                }
                              },
                              style: TextButton.styleFrom(
                                shadowColor: Theme.of(context).primaryColorDark,
                              ),
                            ),
                          ),
                          itemCount: devices.devices.length,
                        );
                      }),
              ),
            ),
            /* ListTile(
                title: Text('Can not find your car!'),
            ),
            Padding(
                padding: const EdgeInsets.only(bottom: 20),
                child: ElevatedButton(
                  onPressed: () async {
                    await BTHelper().openSettings();
                  },
                  child: Text('Open Settings'),
                  style: ElevatedButton.styleFrom(
                      tapTargetSize: MaterialTapTargetSize.shrinkWrap,
                      elevation: 5,
                      shape: RoundedRectangleBorder(
                        side: BorderSide.none,
                        borderRadius: BorderRadius.circular(25),
                      ),
                      padding: const EdgeInsets.all(10)),
                ),
            ), */
          ],
        ),
      ),
    );
  }
}
