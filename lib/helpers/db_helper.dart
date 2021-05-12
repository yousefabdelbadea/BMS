import 'package:sqflite/sqflite.dart' as sql;
import 'package:path/path.dart' as path;

class DBHelper {
  static Future<sql.Database> database() async {
    final dbpath = await sql.getDatabasesPath();
    return await sql.openDatabase(
      path.join(dbpath, 'battery.db'),
      onCreate: (db, version) async {
        await db
            .execute('CREATE TABLE cells(id INTEGER PRIMARY KEY, state TEXT)');
        for (var i = 0; i < 6; i++) {
          await db.insert('cells', {'id': 1, 'state': 'Healthy'},
              conflictAlgorithm: sql.ConflictAlgorithm.replace);
        }
        await db.execute(
            'CREATE TABLE cells_data(id INTEGER NOT NULL, volt INTEGER, temp INTEGER, current INTEGER, time TEXT PRIMARY KEY,FOREIGN KEY (id) REFERENCES cells (id))');
      },
      version: 1,
    );
  }

  static Future<void> insert(String table, Map<String, dynamic> data) async {
    final db = await DBHelper.database();
    db.insert(table, data, conflictAlgorithm: sql.ConflictAlgorithm.replace);
  }

  static Future<List<Map<String, dynamic>>> getData(String table) async {
    final db = await DBHelper.database();
    return await db.query(table);
  }
}
