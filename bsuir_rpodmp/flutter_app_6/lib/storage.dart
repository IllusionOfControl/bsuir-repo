import 'dart:convert';
import 'dart:io';

import 'package:flutter_app_6/quotes.dart';
import 'package:path/path.dart';
import 'package:path_provider/path_provider.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:sqflite/sqflite.dart';

class QuoteLocalStorageSharedPreferences {
  static const String key = 'quote';

  // Save quote to SharedPreferences
  static Future<void> saveQuote(Quote quote) async {
    final prefs = await SharedPreferences.getInstance();
    prefs.setString(key, jsonEncode(quote.toJson()));
  }

  // Retrieve quote from SharedPreferences
  static Future<Quote?> getQuote() async {
    final prefs = await SharedPreferences.getInstance();
    final quoteJson = prefs.getString(key);
    if (quoteJson != null) {
      return Quote.fromJson(jsonDecode(quoteJson));
    }
    return null;
  }
}

class QuoteLocalStorageFileSystem {
  static const String fileName = 'quote.json';

  // Save quote to file system
  static Future<void> saveQuote(Quote quote) async {
    final directory = await getApplicationDocumentsDirectory();
    final file = File(directory.path + fileName);
    await file.writeAsString(jsonEncode(quote.toJson()));
  }

  // Retrieve quote from file system
  static Future<Quote?> getQuote() async {
    try {
      final directory = await getApplicationDocumentsDirectory();
      final file = File(directory.path + fileName);
      if (await file.exists()) {
        final quoteJson = await file.readAsString();
        return Quote.fromJson(jsonDecode(quoteJson));
      }
    } catch (e) {
      print('Error reading file: $e');
    }
    return null;
  }
}

class QuoteLocalStorageSQLite {
  static const String tableName = 'quotes';
  static const String columnId = 'id';
  static const String columnContent = 'content';
  static const String columnAuthor = 'author';

  static Future<Database> _openDatabase() async {
    final databasePath = await getDatabasesPath();
    final path = join(databasePath, 'quotes_database.db');

    return openDatabase(path, version: 1,
        onCreate: (Database db, int version) async {
      await db.execute('''
        CREATE TABLE $tableName (
          $columnId INTEGER PRIMARY KEY AUTOINCREMENT,
          $columnContent TEXT,
          $columnAuthor TEXT
        )
      ''');
    });
  }

  // Save quote to SQLite database
  static Future<void> saveQuote(Quote quote) async {
    final Database db = await _openDatabase();
    await db.insert(tableName, quote.toJson());
  }

  // Retrieve quote from SQLite database
  static Future<Quote?> getQuote() async {
    final Database db = await _openDatabase();
    final List<Map<String, dynamic>> results = await db.query(
      tableName,
      orderBy: '$columnId DESC',
      limit: 1,
    );

    if (results.isNotEmpty) {
      return Quote.fromJson(results.first);
    }

    return null;
  }
}
