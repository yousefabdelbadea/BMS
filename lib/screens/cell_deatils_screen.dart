import 'package:bms/helpers/db_helper.dart';
import 'package:bms/providers/cells.dart';
import 'package:bms/widgets/cell_meters.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:intl/intl.dart';

class CellDetailsScreen extends StatefulWidget {
  final int cellIndex;
  CellDetailsScreen(this.cellIndex);

  @override
  _CellDetailsScreenState createState() => _CellDetailsScreenState();
}

class _CellDetailsScreenState extends State<CellDetailsScreen> {
  bool _expanded = false;
  @override
  void initState() {
    DBHelper.insert('cells_data', {
      'id': 1,
      'temp': 25.5,
      'volt': 30,
      'current': 15,
      'time': DateFormat("yy/MM/dd - HH:mm").format(DateTime.now()).toString()
    });
    super.initState();
  }

  @override
  void didChangeDependencies() {
    Provider.of<Cells>(context).getHistoryData();
    super.didChangeDependencies();
  }

  @override
  Widget build(BuildContext context) {
    var providerData = Provider.of<Cells>(context);
    Cell cellData = providerData.getCellCurrentData(widget.cellIndex);
    return Scaffold(
      appBar: AppBar(
        title: Text('Cell ${cellData.id.toInt()}'),
      ),
      body: SingleChildScrollView(
        child: Column(
          children: [
            Padding(
              padding: const EdgeInsets.all(10.0),
              child: Text(
                'Current Data',
                style: Theme.of(context).textTheme.headline6,
              ),
            ),
            Divider(),
            ListTile(
              leading: CircleAvatar(
                child: Text(cellData.sOC.toString()),
              ),
              title: Text(
                  '${DateFormat("yy/MM/dd - HH:mm").format(DateTime.now()).toString()}'),
              trailing: IconButton(
                icon: Icon(_expanded ? Icons.expand_less : Icons.expand_more),
                onPressed: () {
                  setState(() {
                    _expanded = !_expanded;
                  });
                },
              ),
            ),
            if (_expanded)
              CellMeters(
                current: cellData.current.toInt(),
                temp: cellData.temp.toInt(),
                volt: cellData.volt.toInt(),
              ),
            Divider(),
            Padding(
              padding: const EdgeInsets.all(10.0),
              child: Text(
                'Historical Data',
                style: Theme.of(context).textTheme.headline6,
              ),
            ),
            Divider(),
            RefreshIndicator(
              onRefresh: () => providerData.getHistoryData(),
              child: Container(
                height: 500,
                child: Consumer<Cells>(
                  builder: (ctx, cells, _) => ListView.builder(
                    itemCount:
                        cells.getCellHistoryData(widget.cellIndex).length,
                    itemBuilder: (ctx, i) => Column(
                      children: [
                        Text(cells
                            .getCellHistoryData(widget.cellIndex)[i]
                            .dateTime),
                        Row(
                          children: [
                            Text('Tempreture: '),
                            Text(cells
                                .getCellHistoryData(widget.cellIndex)[i]
                                .temp
                                .toString()),
                          ],
                        ),
                        Row(
                          children: [
                            Text('Current: '),
                            Text(cells
                                .getCellHistoryData(widget.cellIndex)[i]
                                .current
                                .toString()),
                          ],
                        ),
                        Row(
                          children: [
                            Text('Voltage: '),
                            Text(cells
                                .getCellHistoryData(widget.cellIndex)[i]
                                .volt
                                .toString()),
                          ],
                        ),
                      ],
                    ),
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
