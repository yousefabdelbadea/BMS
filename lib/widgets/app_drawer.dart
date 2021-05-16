import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:bms/providers/cells.dart';
import 'package:bms/screens/advanced_screen.dart';
import 'package:bms/screens/car_connection_screen.dart';
import 'package:bms/screens/driver_screen.dart';
import 'package:bms/screens/login_screen.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:bms/providers/auth.dart';

class AppDrawer extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    bool isAuth = Provider.of<Auth>(context).isAuth();
    String connectedCar = Provider.of<BTHelper>(context).connectedDeviceName;
    String sOC = Provider.of<Cells>(context).getOverallSOC.toString();
    return Drawer(
      child: Column(
        children: [
          Expanded(
            child: Column(
              children: [
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
                            fontSize: 30,
                            color: Theme.of(context).primaryColor,
                          ),
                        ),
                      ),
                      if (sOC != null) Text("$sOC%"),
                    ],
                  ),
                ),
                TextButton.icon(
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
                  label: Text("Your Car history"),
                ),
              ],
            ),
          ),
          TextButton.icon(
            onPressed: () {
              Navigator.of(context)
                  .push(MaterialPageRoute(builder: (ctx) => LoginScreen()));
            },
            icon: Icon(isAuth ? Icons.logout : Icons.admin_panel_settings),
            label: Text(isAuth ? "Log out" : "Log in as crew member"),
          ),
        ],
      ),
    );
  }
}
