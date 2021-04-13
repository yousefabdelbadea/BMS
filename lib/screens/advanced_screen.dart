import 'package:bms/screens/cell_deatils_screen.dart';
import 'package:bms/screens/driver_screen.dart';
import 'package:flutter/material.dart';

class AdvancedScreen extends StatefulWidget {
  final int hieght, width;
  AdvancedScreen(this.hieght, this.width);
  @override
  _AdvancedScreenState createState() => _AdvancedScreenState();
}

class _AdvancedScreenState extends State<AdvancedScreen> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Detailed Cells Stauts'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(8.0),
        child: GridView.builder(
          gridDelegate: SliverGridDelegateWithFixedCrossAxisCount(
            crossAxisCount: widget.width,
            childAspectRatio: 3 / 2,
            mainAxisSpacing: 10,
            crossAxisSpacing: 10,
          ),
          itemBuilder: (context, index) {
            return InkWell(
              onTap: () {
                Navigator.of(context).push(MaterialPageRoute(
                    builder: (context) => CellDetailsScreen(index)));
              },
              child: GridTile(
                child: Container(
                  color: Colors.lightGreen,
                  height: MediaQuery.of(context).size.height * .25,
                ),
                footer: GridTileBar(
                  backgroundColor: Colors.black45,
                  title: Text('Cell ${index + 1}'),
                  trailing: Icon(
                    Icons.favorite,
                    color: Colors.green,
                  ),
                ),
              ),
            );
          },
          itemCount: (widget.hieght) * (widget.width),
        ),
      ),
    );
  }
}
