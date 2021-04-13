import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:flutter/material.dart';
import 'package:flutter_blue/flutter_blue.dart';
import 'package:provider/provider.dart';

class CarConnection extends StatefulWidget {
  @override
  _CarConnectionState createState() => _CarConnectionState();
}

class _CarConnectionState extends State<CarConnection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        leading: Hero(
          child: Image.asset('assets/images/logo.png'),
          tag: 'logo',
        ),
        actions: [
          TextButton.icon(
            onPressed: () async {
              Provider.of<BTHelper>(context, listen: false).getDevices();
              print(Provider.of<BTHelper>(context, listen: false).devices);
            },
            icon: Icon(Icons.replay_outlined),
            label: Text('Refresh'),
          )
        ],
      ),
      body: StreamBuilder<BluetoothState>(
          stream: FlutterBlue.instance.state,
          initialData: BluetoothState.unknown,
          builder: (c, snapshot) {
            final state = snapshot.data;
            if (state == BluetoothState.on) {
              return RefreshIndicator(
                onRefresh: () =>
                    Provider.of<BTHelper>(context, listen: false).getDevices(),
                child: Column(
                  children: [
                    /* Padding(
                padding: const EdgeInsets.all(8.0),
                child: ListTile(
                  title: Text('Enable Bluetooth'),
                  trailing: Switch(
                      value: _isEnabled,
                      onChanged: (value) async {
                        _isEnabled
                            ? await BTHelper().disableBluttoth()
                            : await BTHelper().enableBluttoth();
                      }),
                ),
            ), */
                    Expanded(
                      child: FutureBuilder(
                        future: Provider.of<BTHelper>(context, listen: false)
                            .getDevices(),
                        builder: (ctx, data) => data.connectionState ==
                                ConnectionState.waiting
                            ? Center(
                                child: CircularProgressIndicator(),
                              )
                            : Consumer<BTHelper>(builder: (ctx, devices, _) {
                                return ListView.builder(
                                  itemBuilder: (ctx, i) => ListTile(
                                    title: Text(devices.devices[i].name),
                                    trailing: TextButton(
                                      child: devices.devicesStates[i]
                                          ? Text('Connected')
                                          : Text('Connect'),
                                      onPressed: () async {
                                        if (!devices.devicesStates[i]) {
                                          try {
                                            bool newValue =
                                                await devices.connect(i);

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
                                                      content: Text(
                                                          'Device Connected!'),
                                                    ),
                                                  );
                                          } catch (e) {
                                            showDialog(
                                              context: context,
                                              builder: (ctx) => AlertDialog(
                                                title:
                                                    Text('Error in connection'),
                                                content: Text(e.toString()),
                                              ),
                                            );
                                          }
                                        } else {
                                          showDialog(
                                            context: context,
                                            builder: (ctx) => AlertDialog(
                                              title: Text('Already Connected'),
                                              content:
                                                  Text('Want to disconnect!'),
                                              actions: [
                                                TextButton(
                                                    onPressed: () {},
                                                    child: Text('lesa ya amir'))
                                              ],
                                            ),
                                          );
                                        }
                                      },
                                      style: TextButton.styleFrom(
                                        shadowColor:
                                            Theme.of(context).primaryColorDark,
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
              );
            }
            return BluetoothOffScreen(state: state);
          }),
    );
  }
}

class BluetoothOffScreen extends StatelessWidget {
  const BluetoothOffScreen({Key key, this.state}) : super(key: key);

  final BluetoothState state;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.lightBlue,
      body: Center(
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: <Widget>[
            Icon(
              Icons.bluetooth_disabled,
              size: 200.0,
              color: Colors.white54,
            ),
            Text(
              'Bluetooth Adapter is ${state != null ? state.toString().substring(15) : 'not available'}.',
            ),
          ],
        ),
      ),
    );
  }
}
