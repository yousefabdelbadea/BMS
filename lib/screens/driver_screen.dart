import 'package:bms/widgets/cell_meters.dart';
import 'package:flutter/material.dart';

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
          current: 15,
          volt: 65,
          temp: 25,
        ),
      ),
    );
  }
}
