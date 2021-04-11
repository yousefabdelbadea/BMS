import 'package:sqflite/sqflite.dart' as sql;
import 'package:path/path.dart' as path;

class DBHelper {
  static Future<void> insert(String table, Map<String, dynamic> data) async {
    final dBPath = await sql.getDatabasesPath();
    final cellsDB = await sql.openDatabase(path.join(dBPath, 'Cells.db'),
        onCreate: (db, version) {
      return db
          .execute('CREATE TABLE cells(id INTEGER PRIMARY KEY, state TEXT)');
    }, version: 1);
    /* final cellsDataDB = await sql.openDatabase(path.join(dBPath, 'Cells_data.db'),
        onCreate: (db, version) {
      return db
          .execute('CREATE TABLE cells_data(id , state TEXT)');
    },version: 1); */
  }
}
