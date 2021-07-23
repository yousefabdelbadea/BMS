import 'dart:convert';

import 'package:connectivity/connectivity.dart';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:intl/intl.dart';
import 'package:shared_preferences/shared_preferences.dart';

import '../providers/cells.dart';

class ServerAsync with ChangeNotifier {
  String carId;
  String stagingUrl = "https://guarded-journey-91897.herokuapp.com/api/v1";
  Future<String> getCar(String carid) async {
    carId = carid;
    var url = Uri.parse("$stagingUrl/cars/$carId");
    try {
      http.Response response = await http.get(
        url,
        headers: {"Content-Type": "application/json"},
      );
      /* List<Map<String, dynamic>> cellsFromServer =
          json.decode(response.body)['cellDetails'];
      cellsFromServer.forEach((element) {
        cells.add(CellDataHistory(
          current: element['current'],
          volt: element['voltage'],
          dateTime: element['dateTime'],
          temp: element['temperature'],
          index: element['id'] + 1,
        ));
      }); */
      print(response.body);
      if (response.statusCode == 200) {
        return "Data fetched Successfully";
      } else if (response.statusCode == 400) {
        return "Invalid Car Id";
      }
    } catch (e) {}
    notifyListeners();
  }

  Future<void> getCellData(int cellId) async {
    List<CellDataHistory> cells = [];
    var url = Uri.parse("$stagingUrl/cars/$carId/$cellId");
    print(carId);
    try {
      http.Response response = await http.get(
        url,
        headers: {"Content-Type": "application/json"},
      );
      List<dynamic> cellsFromServer = json.decode(response.body)['cellDetails'];
      cellsFromServer.forEach((element) {
        cells.add(CellDataHistory(
          current: element['current'],
          volt: element['voltage'],
          dateTime: DateFormat("yy/MM/dd - HH:mm")
              .format(DateTime.parse(element['dateOfRecord']))
              .toString(),
          temp: element['temperature'] as int,
          index: cellId + 1,
        ));
      });
      print(response.statusCode);
    } catch (e) {
      print(e);
    }
    return cells;
  }

  Future<void> getCarId() async {
    var url = Uri.parse("$stagingUrl/cars/");
    try {
      http.Response response = await http.post(
        url,
        headers: {"Content-Type": "application/json"},
        body: json.encode(
          {
            "number": 236,
            "model": "BMW",
            "numberOfCells": 6,
          },
        ),
      );
      if (response.statusCode == 200 || response.statusCode == 400) {
        print(response.body);
        carId = json.decode(response.body)["carId"];
        print(carId);
        print('bla');
        SharedPreferences prefs = await SharedPreferences.getInstance();
        await prefs.setString("carID", carId);
      }
    } catch (e) {}
  }

  Future<void> setCell(Cell cell) async {
    SharedPreferences prefs = await SharedPreferences.getInstance();
    var connectivityResult = await (Connectivity().checkConnectivity());
    if (connectivityResult == ConnectivityResult.none) {
      if (prefs.containsKey('waiting_data')) {
        List<Map<String, dynamic>> oldData =
            json.decode(prefs.getString('waiting_data'))["cellDetails"];
        oldData.add({
          "cellId": cell.id - 1,
          "current": cell.current,
          "temperature": cell.temp,
          "voltage": cell.volt,
          "percentage": cell.sOC,
          "dateTime": DateTime.now().toIso8601String(),
        });
        await prefs.setString(
            "waiting_data", json.encode({"cellDetails": oldData}));
      } else {
        await prefs.setString(
            "waiting_data",
            json.encode({
              "cellDetails": [
                {
                  "cellId": cell.id - 1,
                  "current": cell.current,
                  "temperature": cell.temp,
                  "voltage": cell.volt,
                  "percentage": cell.sOC,
                  "dateTime": DateTime.now().toIso8601String(),
                }
              ]
            }));
      }
    } else {
      if (!prefs.containsKey('carId')) {
        await getCarId();
      } else {
        carId = prefs.getString('carId');
      }
      var url = Uri.parse("$stagingUrl/cars/cell/cellDetails/$carId");
      if (prefs.containsKey('waiting_data')) {
        List<Map<String, dynamic>> oldData =
            json.decode(prefs.getString('waiting_data'))["cellDetails"];
        oldData.add({
          "cellId": cell.id - 1,
          "current": cell.current,
          "temperature": cell.temp,
          "voltage": cell.volt,
          "percentage": cell.sOC,
          "dateTime": DateTime.now().toIso8601String(),
        });
        await prefs.setString(
            "waiting_data", json.encode({"cellDetails": oldData}));
        try {
          final response = await http.post(
            url,
            body: prefs.getString('waiting_data'),
            headers: {"Content-Type": "application/json"},
          );
          if (response.statusCode == 200) {
            prefs.remove('waiting_data');
          } else {
            print(response.body);
          }
        } catch (e) {
          print(e);
        }
      } else {
        url = Uri.parse("$stagingUrl/cars/$carId/${cell.id - 1}/cellDetails");
        try {
          final response = await http.post(
            url,
            body: json.encode({
              "current": cell.current,
              "temperature": cell.temp,
              "voltage": cell.volt,
              "percentage": cell.sOC,
            }),
            headers: {"Content-Type": "application/json"},
          );
          if (response.statusCode == 200) {
          } else {
            print(response.body);
          }
        } catch (e) {
          print(e);
        }
      }
    }
  }
}
