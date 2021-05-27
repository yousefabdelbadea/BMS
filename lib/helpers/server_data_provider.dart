import 'dart:convert';

import 'package:connectivity/connectivity.dart';
import 'package:http/http.dart' as http;
import 'package:shared_preferences/shared_preferences.dart';

import '../providers/cells.dart';

class ServerAsync {
  String stagingUrl = "https://guarded-journey-91897.herokuapp.com/api/v1";
  Future<List<CellDataHistory>> getCar(String carId) async {}
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
      var carId;
      if (!prefs.containsKey('carId')) {
        //post request car and get carid
      } else {
        carId = prefs.getString('carId');
      }
      var url = Uri.parse("$stagingUrl/cars/$carId");
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
        url = Uri.parse("$stagingUrl/cars/$carId/${cell.id}");
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
