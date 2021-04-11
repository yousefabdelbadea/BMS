import 'package:bms/providers/cells.dart';
import 'package:bms/widgets/cell_meters.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class DriverScreen extends StatefulWidget {
  @override
  _DriverScreenState createState() => _DriverScreenState();
}

class _DriverScreenState extends State<DriverScreen> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: CellMeters(
          current: Provider.of<Cells>(context).getOverallCurrent().toInt(),
          volt: Provider.of<Cells>(context).getOverallVoltage().toInt(),
          temp: Provider.of<Cells>(context).getOverallTemp().toInt(),
        ),
      ),
    );
  }
}
