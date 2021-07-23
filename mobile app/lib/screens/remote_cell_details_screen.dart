import 'package:bms/helpers/server_data_provider.dart';
import 'package:bms/providers/cells.dart';
import 'package:bms/widgets/cell_history_tile.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class RemoteCellHistoryScreen extends StatelessWidget {
  final int cellId;
  const RemoteCellHistoryScreen(this.cellId);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Cell ${cellId + 1}'),
      ),
      body: FutureBuilder(
        future: Provider.of<ServerAsync>(context).getCellData(cellId),
        builder: (context, snapshot) {
          if (snapshot.hasData) {
            List<CellDataHistory> cells = snapshot.data;
            return Padding(
              padding: const EdgeInsets.all(15.0),
              child: ListView.builder(
                itemBuilder: (context, index) => CellHistoryTile(
                  current: cells[index].current.toString(),
                  temp: cells[index].temp.toString(),
                  volt: cells[index].volt.toString(),
                  dateTime: cells[index].dateTime.toString(),
                ),
                itemCount: cells.length,
              ),
            );
          }
          return Center(child: CircularProgressIndicator());
        },
      ),
    );
  }
}
