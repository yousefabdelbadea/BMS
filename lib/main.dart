import 'package:bms/providers/auth.dart';
import 'package:bms/screens/advanced_screen.dart';
import 'package:bms/screens/car_connection_screen.dart';
import 'package:bms/screens/cell_deatils_screen.dart';
import 'package:bms/screens/driver_screen.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:bms/providers/cells.dart';
import './screens/splash_screen.dart';
import 'providers/notifications.dart';

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
        ChangeNotifierProvider(create: (ctx) => User()),
        ChangeNotifierProvider(create: (ctx) => Cells()),
        ChangeNotifierProvider(create: (_) => LocalNotification()),
        ChangeNotifierProxyProvider<Cells, BTHelper>(
          create: (_) => BTHelper(),
          update: (_, data, old) => old..cells = data.cells,
        ),
      ],
      child: MaterialApp(
        title: 'BMS',
        theme: ThemeData.dark().copyWith(
          primaryColor: Colors.teal[900],
          accentColor: Colors.blueGrey,
        ),
        home: SplashScreen(),
        routes: {
          CarConnection.routeName: (context) => CarConnection(),
          AdvancedScreen.routeName: (context) => AdvancedScreen(3, 2),
          DriverScreen.routeName: (context) => DriverScreen(),
          CellDetailsScreen.routeName: (context) => CellDetailsScreen(),
        },
      ),
    );
  }
}
