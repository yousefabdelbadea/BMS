import 'package:flutter/material.dart';

import './screens/splash_screen.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  // This widget is the root of your application.
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'BMS',
      theme: ThemeData.dark().copyWith(
        primaryColor: Colors.teal[900],
        accentColor: Colors.blueGrey,
      ),
      home: SplashScreen(),
    );
  }
}
