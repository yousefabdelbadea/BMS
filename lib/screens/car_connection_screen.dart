import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class CarConnection extends StatefulWidget {
  @override
  _CarConnectionState createState() => _CarConnectionState();
}

class _CarConnectionState extends State<CarConnection> {
  bool _isEnabled = false;
  @override
  void initState() {
    super.initState();
  }

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
              BTHelper().getDevices();
              print(Provider.of<BTHelper>(context, listen: false).devices);
            },
            icon: Icon(Icons.replay_outlined),
            label: Text('Refresh'),
          )
        ],
      ),
      body: Column(
        children: [
          ListTile(
            title: Text('Enable Bluetooth'),
            trailing: Switch(
                value: _isEnabled,
                onChanged: (value) async {
                  _isEnabled
                      ? await BTHelper().disableBluttoth()
                      : await BTHelper().enableBluttoth();
                  setState(() {
                    _isEnabled = !_isEnabled;
                  });
                }),
          ),
          ListTile(
            title: Text('Paired devices'),
          ),
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
                      bool connected = false;
                      return ListView.builder(
                        itemBuilder: (ctx, i) => ListTile(
                          title: Text(devices.devices[i].name),
                          trailing: TextButton(
                            child:
                                connected ? Text('Connected') : Text('Connect'),
                            onPressed: () async {
                              bool newValue = await BTHelper().connect(i);
                              setState(() {
                                connected = newValue;
                              });
                              newValue == false
                                  ? ScaffoldMessenger.of(context).showSnackBar(
                                      SnackBar(
                                          content:
                                              Text('Error in connecection !')))
                                  : null;
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
          ListTile(
            title: Text('Can not find your car!'),
            subtitle: Text('Please pair with it from setting'),
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
          ),
        ],
      ),
    );
  }
}
