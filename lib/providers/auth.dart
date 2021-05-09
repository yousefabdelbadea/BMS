import 'dart:convert';

import 'package:flutter/cupertino.dart';
import 'package:crypto/crypto.dart';
import 'package:http/http.dart' as http;

class User with ChangeNotifier {
  String _token;
  DateTime _tokenExpiryTime;
  String connectedCar;
  void signIn(String userName, String password) async {
    // connect to server to recieve the token
    password = sha512.convert(utf8.encode(password)).toString();
    var url = Uri.parse('');
    try {
      var response = await http.post(url,
          body: json.encode({"email": userName, "password": password}));
      if (json.decode(response.body)['token'] != null) {
        _token = json.decode(response.body)['token'];
      }
    } catch (e) {}
  }

  String get token {
    return _token;
  }

  bool get isAuth {
    return true;
    //return _token != null ? true : false;
  }
}
