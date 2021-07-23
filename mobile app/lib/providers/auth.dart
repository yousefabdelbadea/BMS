import 'dart:async';
import 'dart:convert';

import 'package:flutter/cupertino.dart';
import 'package:http/http.dart' as http;

class Auth with ChangeNotifier {
  String _token, _userId;
  bool isAuth() {
    return _token != null;
  }

  String get token {
    if (_token != null) return _token;
    return null;
  }

  String get userId {
    return _userId;
  }

  Future<void> signIn(String email, String passowrd) async {
    var url = Uri.parse(
        'https://guarded-journey-91897.herokuapp.com/api/v1/users/login');
    try {
      final response = await http.post(url,
          headers: {"Content-Type": "application/json"},
          body: jsonEncode({'email': email, 'password': passowrd}));
      final responseData = json.decode(response.body);
      _token = responseData['token'];
      notifyListeners();
    } catch (e) {
      print("error :$e");
    }
  }

  Future<void> logOut() async {
    _userId = null;
    _token = null;
    notifyListeners();
  }
}
