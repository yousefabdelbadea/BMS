import 'package:bms/screens/home.dart';
import 'package:flutter/material.dart';
import 'package:animated_splash_screen/animated_splash_screen.dart';

class SplashScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return AnimatedSplashScreen(
      splash: Container(
        child: Column(
          children: [
            Hero(
              child: Image.asset('assets/images/logo.png'),
              tag: 'logo',
            ),
            Center(
              child: Text(
                'BMS',
                style: TextStyle(
                  fontSize: 28,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ),
            Center(
              child: Text(
                'Your Car Battery Helper',
                style: TextStyle(
                  fontSize: 20,
                  fontWeight: FontWeight.w500,
                ),
              ),
            ),
          ],
        ),
      ),
      nextScreen: Home(),
      backgroundColor: Colors.black54,
      duration: 2000,
      splashTransition: SplashTransition.sizeTransition,
      splashIconSize: MediaQuery.of(context).size.width * .95,
      animationDuration: Duration(milliseconds: 2000),
      curve: Curves.fastLinearToSlowEaseIn,
    );
  }
}
