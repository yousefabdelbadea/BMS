import 'package:flutter/material.dart';
import 'package:flutter_speedometer/flutter_speedometer.dart';

class CellMeters extends StatelessWidget {
  final double maxVolt, maxTemp, maxCurrent, volt, current, temp;
  CellMeters({
    @required this.current,
    @required this.temp,
    @required this.volt,
    this.maxCurrent = 5.0,
    this.maxTemp = 60,
    this.maxVolt = 4.5,
  });

  @override
  Widget build(BuildContext context) {
    return Container(
      color: ThemeData.dark().primaryColor,
      child: Column(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: [
          Speedometer(
            displayText: "C",
            size: MediaQuery.of(context).size.height * .2,
            minValue: 0,
            maxValue: maxTemp.toDouble(),
            warningValue: 50,
            currentValue: temp,
            backgroundColor: ThemeData.dark().primaryColor,
          ),
          Speedometer(
            displayText: "V",
            size: MediaQuery.of(context).size.height * .4,
            minValue: 3.6,
            maxValue: maxVolt,
            warningValue: 4.2,
            currentValue: volt,
            backgroundColor: ThemeData.dark().primaryColor,
          ),
          Speedometer(
            displayText: "A",
            size: MediaQuery.of(context).size.height * .2,
            minValue: 0,
            maxValue: maxCurrent,
            warningValue: 3,
            currentValue: current,
            backgroundColor: ThemeData.dark().primaryColor,
          ),
        ],
      ),
    );
  }
}
