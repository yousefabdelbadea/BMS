/* import 'package:bms/helpers/bluetooth_helper.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class DiscoveryScreen extends StatelessWidget {
  final int index;
  DiscoveryScreen(this.index);
  @override
  Widget build(BuildContext context) {
    var _data = Provider.of<BTHelper>(context);
    return Scaffold(
      appBar: AppBar(
        title: Text(_data.devices[index].name),
      ),
      body: _data.devicesStates[index]
          ? RefreshIndicator(
              onRefresh: () async {
                await _data.discoverServices();
              },
              child: Container(
                height: 500,
                child: ListView.builder(
                  itemBuilder: (ctx, index) => Column(
                    children: [
                      Text(_data.sevices[index].uuid.toString()),
                      ListView.builder(
                          itemBuilder: (ctx, i) {
                            return ListTile(
                              title: Text(_data
                                  .sevices[index].characteristics[i].uuid
                                  .toString()),
                              subtitle: Text(String.fromCharCodes(_data
                                  .sevices[index]
                                  .characteristics[i]
                                  .lastValue)),
                            );
                          },
                          itemCount:
                              _data.sevices[index].characteristics.length),
                    ],
                  ),
                  itemCount: _data.sevices.length,
                ),
              ),
            )
          : Center(
              child: Text('Device Not Connected'),
            ),
    );
  }
}
 */