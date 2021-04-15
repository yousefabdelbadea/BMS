import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:flutter/material.dart';
import 'package:flutter_speedometer/flutter_speedometer.dart';
import 'package:provider/provider.dart';

class CellMeters extends StatelessWidget {
  final int maxVolt, maxTemp, maxCurrent, volt, current, temp;
  CellMeters({
    @required this.current,
    @required this.temp,
    @required this.volt,
    this.maxCurrent = 25,
    this.maxTemp = 50,
    this.maxVolt = 80,
  });

  @override
  Widget build(BuildContext context) {
    return Container(
      color: ThemeData.dark().primaryColor,
      child: SafeArea(
        child: RefreshIndicator(
          onRefresh: () =>
              Provider.of<BTHelper>(context, listen: false).getData(),
          child: SingleChildScrollView(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                Speedometer(
                  displayText: "C",
                  size: MediaQuery.of(context).size.height * .2,
                  minValue: 0,
                  maxValue: maxTemp,
                  warningValue: 40,
                  currentValue: temp,
                  backgroundColor: ThemeData.dark().primaryColor,
                ),
                Speedometer(
                  displayText: "V",
                  size: MediaQuery.of(context).size.height * .4,
                  minValue: 0,
                  maxValue: maxVolt,
                  warningValue: 65,
                  currentValue: volt,
                  backgroundColor: ThemeData.dark().primaryColor,
                ),
                Speedometer(
                  displayText: "A",
                  size: MediaQuery.of(context).size.height * .2,
                  minValue: 0,
                  maxValue: maxCurrent,
                  warningValue: 20,
                  currentValue: current,
                  backgroundColor: ThemeData.dark().primaryColor,
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
