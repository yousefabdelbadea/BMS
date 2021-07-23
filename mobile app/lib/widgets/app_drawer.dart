import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:bms/providers/cells.dart';
import 'package:bms/screens/advanced_screen.dart';
import 'package:bms/screens/car_connection_screen.dart';
import 'package:bms/screens/driver_screen.dart';
import 'package:bms/screens/login_screen.dart';
import 'package:bms/screens/remote_connection_screen.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:bms/providers/auth.dart';

class AppDrawer extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    bool isAuth = Provider.of<Auth>(context).isAuth();
    String connectedCar = Provider.of<BTHelper>(context).connectedDeviceName;
    String sOC = Provider.of<Cells>(context).getOverallSOC.toString() ?? 0;
    return Drawer(
      child: SafeArea(
        child: Column(
          children: [
            Expanded(
              child: Column(
                children: [
                  if (!isAuth)
                    Container(
                      height: 120,
                      width: double.infinity,
                      padding: const EdgeInsets.all(20),
                      alignment: Alignment.centerLeft,
                      color: Theme.of(context).accentColor,
                      child: Row(
                        mainAxisAlignment: MainAxisAlignment.spaceAround,
                        children: [
                          TextButton(
                            onPressed: () => Navigator.of(context)
                                .pushReplacementNamed(CarConnection.routeName),
                            child: Text(
                              connectedCar != null
                                  ? connectedCar
                                  : "No connected Device",
                              style: TextStyle(
                                fontWeight: FontWeight.w900,
                                fontSize: 20,
                                color: Theme.of(context).primaryColor,
                              ),
                            ),
                          ),
                          if (sOC != null) Text("$sOC%"),
                        ],
                      ),
                    ),
                  isAuth
                      ? TextButton.icon(
                          onPressed: () {
                            Navigator.of(context).pushReplacementNamed(
                                RemoteConnectionScreen.routeName);
                          },
                          icon: Icon(Icons.car_repair),
                          label: Text("Connect Car"),
                        )
                      : TextButton.icon(
                          onPressed: () {
                            Navigator.of(context)
                                .pushReplacementNamed(DriverScreen.routeName);
                          },
                          icon: Icon(Icons.speed_rounded),
                          label: Text("Current Measurements"),
                        ),
                  TextButton.icon(
                    onPressed: () {
                      Navigator.of(context)
                          .pushReplacementNamed(AdvancedScreen.routeName);
                    },
                    icon: Icon(Icons.history),
                    label: Text("Car history"),
                  ),
                ],
              ),
            ),
            TextButton.icon(
              onPressed: () {
                if (isAuth) {
                  Provider.of<Auth>(context, listen: false).logOut();
                  Navigator.of(context).pushNamed(CarConnection.routeName);
                }
                if (!isAuth) {
                  Navigator.of(context)
                      .push(MaterialPageRoute(builder: (ctx) => LoginScreen()));
                }
              },
              icon: Icon(isAuth ? Icons.logout : Icons.admin_panel_settings),
              label: Text(isAuth ? "Log out" : "Log in as crew member"),
            ),
          ],
        ),
      ),
    );
  }
}
