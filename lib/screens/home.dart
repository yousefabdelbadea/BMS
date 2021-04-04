import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:bms/screens/advanced_screen.dart';
import 'package:bms/screens/car_connection_screen.dart';
import 'package:bms/screens/driver_screen.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class Home extends StatefulWidget {
  @override
  _HomeState createState() => _HomeState();
}

class _HomeState extends State<Home> {
  PageController pageController;
  int pageIndex = 0;
  final _scaffoldKey = GlobalKey<ScaffoldState>();
  onTap(int pageIndex) {
    pageController.animateToPage(
      pageIndex,
      duration: Duration(milliseconds: 300),
      curve: Curves.easeInOutCubic,
    );
  }

  onPageChanged(int pageIndex) {
    setState(() {
      this.pageIndex = pageIndex;
    });
  }

  @override
  void initState() {
    pageController = PageController(); //can change initital page
    super.initState();
  }

  @override
  void dispose() {
    pageController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return ChangeNotifierProvider(
      create: (ctx) => BTHelper(),
      child: Scaffold(
        key: _scaffoldKey,
        body: PageView(
          children: <Widget>[
            CarConnection(),
            DriverScreen(),
            AdvancedScreen(3, 2),
          ],
          controller: pageController,
          onPageChanged: onPageChanged,
          physics: NeverScrollableScrollPhysics(),
        ),
        bottomNavigationBar: CupertinoTabBar(
          activeColor: Theme.of(context).primaryColor,
          currentIndex: pageIndex,
          onTap: onTap,
          items: [
            BottomNavigationBarItem(
                icon: Icon(Icons.bluetooth_connected_sharp)),
            BottomNavigationBarItem(
              icon: Icon(
                Icons.speed,
                size: 35.0,
              ),
            ),
            BottomNavigationBarItem(
              icon: Icon(
                Icons.battery_full,
              ),
            ),
          ],
        ),
      ),
    );
  }
}
