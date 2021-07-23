import 'package:bms/helpers/server_data_provider.dart';
import 'package:bms/widgets/app_drawer.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class RemoteConnectionScreen extends StatelessWidget {
  static final String routeName = "/remote_connect";
  TextEditingController carId = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      drawer: AppDrawer(),
      appBar: AppBar(
        title: Text("Connect to A Car"),
        leading: Builder(builder: (context) {
          return Padding(
            padding: EdgeInsets.only(left: 5),
            child: Hero(
              child: TextButton(
                child: Image.asset('assets/images/logo.png'),
                onPressed: () => Scaffold.of(context).openDrawer(),
              ),
              tag: 'logo',
            ),
          );
        }),
      ),
      body: Column(
        children: [
          Form(
            child: Expanded(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: TextFormField(
                      controller: carId,
                      decoration: InputDecoration(labelText: 'Car Id'),
                    ),
                  ),
                  SizedBox(
                    height: 20,
                  ),
                  ElevatedButton(
                    child: Text('Connect Car'),
                    onPressed: () async {
                      print(carId.text);
                      String messgae =
                          await Provider.of<ServerAsync>(context, listen: false)
                              .getCar(carId.text);
                      ScaffoldMessenger.of(context).showSnackBar(
                        SnackBar(
                          content: Text(messgae),
                        ),
                      );
                    },
                    style: ElevatedButton.styleFrom(
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(30),
                      ),
                      padding:
                          EdgeInsets.symmetric(horizontal: 30.0, vertical: 8.0),
                    ),
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}
