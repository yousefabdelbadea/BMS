import 'package:flutter/material.dart';

class CellHistoryTile extends StatelessWidget {
  const CellHistoryTile(
      {@required this.current,
      @required this.temp,
      @required this.volt,
      @required this.dateTime});

  final String dateTime, current, volt, temp;

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Text(dateTime),
        Row(
          children: [
            Text('Tempreture: '),
            Text(temp),
          ],
        ),
        Row(
          children: [
            Text('Current: '),
            Text(current),
          ],
        ),
        Row(
          children: [
            Text('Voltage: '),
            Text(volt),
          ],
        ),
      ],
    );
  }
}
