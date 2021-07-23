import 'package:flutter/material.dart';
import 'package:flutter_speedometer/flutter_speedometer.dart';

class CellMeters extends StatelessWidget {
  final double maxVolt, maxTemp, maxCurrent, volt, current, temp;
  CellMeters({
    @required this.current,
    @required this.temp,
    @required this.volt,
    this.maxCurrent = 4,
    this.maxTemp = 40,
    this.maxVolt = 4.2,
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
            warningValue: 30,
            currentValue: temp,
            backgroundColor: ThemeData.dark().primaryColor,
          ),
          Speedometer(
            displayText: "V",
            size: MediaQuery.of(context).size.height * .4,
            minValue: 3.2,
            maxValue: maxVolt,
            warningValue: 4.1,
            currentValue: volt,
            backgroundColor: ThemeData.dark().primaryColor,
          ),
          Speedometer(
            displayText: "A",
            size: MediaQuery.of(context).size.height * .2,
            minValue: 0,
            maxValue: maxCurrent,
            warningValue: 3.5,
            currentValue: current,
            backgroundColor: ThemeData.dark().primaryColor,
          ),
        ],
      ),
    );
  }
}
