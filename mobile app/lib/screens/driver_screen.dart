import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:bms/providers/cells.dart';
import 'package:bms/widgets/app_drawer.dart';
import 'package:flutter/material.dart';
import 'package:flutter_speedometer/flutter_speedometer.dart';
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
        child: Container(
          color: ThemeData.dark().primaryColor,
          child: Column(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: [
              Speedometer(
                displayText: "C",
                size: MediaQuery.of(context).size.height * .2,
                minValue: 0,
                maxValue: 40,
                warningValue: 30,
                currentValue: Provider.of<Cells>(context).getOverallTemp(),
                backgroundColor: ThemeData.dark().primaryColor,
              ),
              Speedometer(
                displayText: "V",
                size: MediaQuery.of(context).size.height * .4,
                minValue: 6.96,
                maxValue: 8.32,
                warningValue: 8,
                currentValue: Provider.of<Cells>(context).getOverallVoltage(),
                backgroundColor: ThemeData.dark().primaryColor,
              ),
              Speedometer(
                displayText: "A",
                size: MediaQuery.of(context).size.height * .2,
                minValue: 0,
                maxValue: 12,
                warningValue: 12,
                currentValue: Provider.of<Cells>(context).getOverallCurrent(),
                backgroundColor: ThemeData.dark().primaryColor,
              ),
            ],
          ),
        ),
      ),
    );
  }
}
