import 'package:flutter/cupertino.dart';

class Cell {
  double temp, current, volt, sOC, id;
  Cell({this.id, this.current, this.sOC, this.temp, this.volt});
}

class Cells with ChangeNotifier {
  List<Cell> _cells = [
    Cell(temp: 25.0, current: 0, volt: 30, sOC: 60, id: 1),
    Cell(temp: 25.0, current: 0, volt: 30, sOC: 60, id: 2),
    Cell(temp: 25.0, current: 0, volt: 30, sOC: 60, id: 3),
    Cell(temp: 25.0, current: 0, volt: 30, sOC: 60, id: 4),
    Cell(temp: 25.0, current: 0, volt: 30, sOC: 60, id: 5),
    Cell(temp: 25.0, current: 0, volt: 30, sOC: 60, id: 6),
  ];
  void setCellValue(int index, Cell cell) {
    _cells[index] = cell;
    notifyListeners();
  }

  Cell getCellData(int index) {
    return _cells[index];
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
