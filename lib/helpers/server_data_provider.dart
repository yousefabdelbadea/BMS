import 'dart:convert';

import 'package:connectivity/connectivity.dart';
import 'package:http/http.dart' as http;
import 'package:shared_preferences/shared_preferences.dart';

import '../providers/cells.dart';

class ServerAsync {
  String carId;
  String stagingUrl = "https://guarded-journey-91897.herokuapp.com/api/v1";
  Future<String> getCar(String carid) async {
    List<CellDataHistory> cells = [];
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
  }

  Future<void> getCarId() async {
    var url = Uri.parse("$stagingUrl/cars/");
    try {
      http.Response response = await http.post(
        url,
        headers: {"Content-Type": "application/json"},
        body: json.encode(
          {
            "number": 13,
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
        prefs.setString("carID", carId);
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
          "cellId": cell.id,
          "current": cell.current,
          "temperatue": cell.temp,
          "voltage": cell.volt,
          "percentage": cell.sOC,
          "dateTime": DateTime.now().toIso8601String(),
        });
        prefs.setString("waiting_data", json.encode({"cellDetails": oldData}));
      } else {
        prefs.setString(
            "waiting_data",
            json.encode({
              "cellDetails": [
                {
                  "cellId": cell.id,
                  "current": cell.current,
                  "temperatue": cell.temp,
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
          "cellId": cell.id,
          "current": cell.current,
          "temperatue": cell.temp,
          "voltage": cell.volt,
          "percentage": cell.sOC,
          "dateTime": DateTime.now().toIso8601String(),
        });
        prefs.setString("waiting_data", json.encode({"cellDetails": oldData}));
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
        url = Uri.parse("$stagingUrl/cars/$carId/${cell.id}/cellDetails");
        try {
          final response = await http.post(
            url,
            body: json.encode({
              "current": cell.current,
              "temperatue": cell.temp,
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
