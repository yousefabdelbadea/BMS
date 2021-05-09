import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:bms/screens/advanced_screen.dart';
import 'package:bms/screens/car_connection_screen.dart';
import 'package:bms/screens/driver_screen.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class AppDrawer extends StatelessWidget {
  final bool isAuth;
  AppDrawer(this.isAuth);
  @override
  Widget build(BuildContext context) {
    String connectedCar = Provider.of<BTHelper>(context).connectedDeviceName;
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
                  child: TextButton(
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
            onPressed: () {},
            icon: Icon(isAuth ? Icons.logout : Icons.admin_panel_settings),
            label: Text(isAuth ? "Log out" : "Log in as crew member"),
          ),
        ],
      ),
    );
  }
}
