import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:bms/providers/cells.dart';
import 'package:bms/widgets/app_drawer.dart';
import 'package:bms/widgets/cell_meters.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class DriverScreen extends StatefulWidget {
  static const String routeName = "/mainMetersScreen";
  @override
  _DriverScreenState createState() => _DriverScreenState();
}

class _DriverScreenState extends State<DriverScreen> {
  @override
  Widget build(BuildContext context) {
    String deviceName = Provider.of<BTHelper>(context).connectedDeviceName;
    return Scaffold(
      appBar: AppBar(
        actions: [
          TextButton.icon(
            onPressed: () async {
              Provider.of<BTHelper>(context, listen: false).discoverServices();
            },
            icon: Icon(Icons.refresh),
            label: Text("Refresh Data"),
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
      body: SingleChildScrollView(
        physics: AlwaysScrollableScrollPhysics(),
        child: CellMeters(
          current: Provider.of<Cells>(context).getOverallCurrent(),
          volt: Provider.of<Cells>(context).getOverallVoltage(),
          temp: Provider.of<Cells>(context).getOverallTemp(),
        ),
      ),
    );
  }
}
