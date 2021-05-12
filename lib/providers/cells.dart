import 'package:bms/helpers/db_helper.dart';
import 'package:flutter/cupertino.dart';
import 'package:intl/intl.dart';

class Cell {
  final int temp, current, volt, sOC, id;
  Cell({this.id, this.current, this.sOC, this.temp, this.volt});
}

class CellDataHistory {
  final int temp, current, volt;
  final String dateTime;
  final int index;
  CellDataHistory(
      {this.current, this.dateTime, this.temp, this.volt, this.index});
}

class Cells with ChangeNotifier {
  List<CellDataHistory> _cellHistoryData = [];
  List<Cell> cells = [
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 1),
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 2),
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 3),
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 4),
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 5),
    Cell(temp: 0, current: 0, volt: 0, sOC: 0, id: 6),
  ];
  Future<void> setCellValue(Cell cell) async {
    cells[cell.id - 1] = cell;
    notifyListeners();
    print("value seted");
    await DBHelper.insert('cells_data', {
      'id': cell.id,
      'temp': cell.temp,
      'volt': cell.volt,
      'current': cell.current,
      'time': DateFormat("yy/MM/dd - HH:mm").format(DateTime.now()).toString(),
    });
    notifyListeners();
  }

  Cell getCellCurrentData(int index) {
    return cells[index];
  }

  Future<void> getHistoryData() async {
    _cellHistoryData = [];
    var data = await DBHelper.getData('cells_data');
    data.forEach((element) {
      _cellHistoryData.add(
        CellDataHistory(
          current: element['current'],
          volt: element['volt'],
          dateTime: element['time'],
          index: element['id'],
          temp: element['temp'],
        ),
      );
      notifyListeners();
    });
  }

  List<CellDataHistory> getCellHistoryData(int cellId) {
    print('bla bla here');
    return _cellHistoryData
        .where((element) => element.index == (cellId + 1))
        .toList();
  }

  int getOverallTemp() {
    int temp = 0;
    for (Cell cell in cells) {
      temp += cell.temp;
    }
    return temp;
  }

  int getOverallCurrent() {
    int current = 0;
    for (Cell cell in cells) {
      current += cell.current;
    }
    return current;
  }

  int getOverallVoltage() {
    int volt = 0;
    for (Cell cell in cells) {
      volt += cell.volt;
    }
    return volt;
  }
}
