import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:bms/providers/cells.dart';
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
    return MultiProvider(
      providers: [
        ChangeNotifierProvider(create: (ctx) => Cells()),
        ChangeNotifierProxyProvider<Cells, BTHelper>(
          create: (ctx) => BTHelper(null),
          update: (ctx, cells, _) => BTHelper(cells),
        ),
      ],
      child: MaterialApp(
        title: 'BMS',
        theme: ThemeData.dark().copyWith(
          primaryColor: Colors.teal[900],
          accentColor: Colors.blueGrey,
        ),
        home: SplashScreen(),
      ),
    );
  }
}
