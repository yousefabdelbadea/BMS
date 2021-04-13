import 'package:bms/helpers/db_helper.dart';
import 'package:flutter/cupertino.dart';
import 'package:intl/intl.dart';

class Cell {
  final double temp, current, volt, sOC, id;
  Cell({this.id, this.current, this.sOC, this.temp, this.volt});
}

class CellDataHistory {
  final double temp, current, volt;
  final String dateTime;
  final int index;
  CellDataHistory(
      {this.current, this.dateTime, this.temp, this.volt, this.index});
}

class Cells with ChangeNotifier {
  List<CellDataHistory> _cellHistoryData = [];
  List<Cell> _cells = [
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 1),
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 2),
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 3),
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 4),
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 5),
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 6),
  ];
  void setCellValue(Cell cell) {
    _cells[cell.id.toInt() - 1] = cell;
    notifyListeners();
    DBHelper.insert('cellsData', {
      'temp': cell.temp,
      'volt': cell.volt,
      'current': cell.current,
      'time': DateFormat("yy/MM/dd - HH:mm").format(DateTime.now()).toString(),
    });
  }

  Cell getCellCurrentData(int index) {
    return _cells[index];
  }

  Future<void> getHistoryData() async {
    _cellHistoryData = [];
    var data = await DBHelper.getData('cells_data');
    data.forEach((element) {
      print(element);
      _cellHistoryData.add(
        CellDataHistory(
          temp: element['temp'],
          current: element['current'],
          volt: element['volt'],
          dateTime: element['time'],
          index: element['id'],
        ),
      );
    });
    notifyListeners();
  }

  List<CellDataHistory> getCellHistoryData(int cellId) {
    return _cellHistoryData
        .where((element) => element.index == cellId + 1)
        .toList();
  }

  double getOverallTemp() {
    double temp = 0;
    for (Cell cell in _cells) {
      temp += cell.temp;
    }
    return temp;
  }

  double getOverallCurrent() {
    double current = 0;
    for (Cell cell in _cells) {
      current += cell.current;
    }
    return current;
  }

  double getOverallVoltage() {
    double volt = 0;
    for (Cell cell in _cells) {
      volt += cell.volt;
    }
    return volt;
  }
}
