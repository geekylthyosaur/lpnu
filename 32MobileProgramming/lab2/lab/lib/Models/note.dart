import 'dart:async';
import 'dart:math';

import 'package:flutter/material.dart';
import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';

class Note {
  late int id;
  String? googleId;
  ColorScheme colorScheme = ColorScheme.fromSwatch(
      primarySwatch: Colors.primaries
          .elementAt(Random().nextInt(Colors.primaries.length)));
  String title = "";
  String content = "";
  DateTime lastEdited = DateTime.now();
  DateTime? alarm;
  bool isArchived = false;
  bool isDeleted = false;

  Note({
    int? id,
    this.googleId,
    ColorScheme? colorScheme,
    this.title = "",
    this.content = "",
    DateTime? lastEdited,
    this.alarm,
    this.isArchived = false,
    this.isDeleted = false,
  }) {
    this.id = id ?? 0;
    this.lastEdited = lastEdited ?? DateTime.now();
    this.colorScheme = colorScheme ??
        ColorScheme.fromSwatch(
            primarySwatch: Colors.primaries
                .elementAt(Random().nextInt(Colors.primaries.length)));
  }

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'googleId': googleId,
      'title': title,
      'content': content,
      'lastEdited': lastEdited.toString(),
      'colorScheme': colorScheme.primary.value,
      'alarm': alarm?.toString(),
      'isArchived': isArchived ? 1 : 0,
      'isDeleted': isDeleted ? 1 : 0,
    };
  }

  static Note fromMap(Map<String, dynamic> map) {
    return Note(
      id: map['id'],
      googleId: map['googleId'],
      title: map['title'],
      content: map['content'],
      lastEdited: DateTime.parse(map['lastEdited']),
      colorScheme: ColorScheme.fromSwatch(
          primarySwatch: Colors.primaries
              .firstWhere((e) => e.value == map['colorScheme'])),
      alarm: map['alarm'] != null ? DateTime.parse(map['alarm']) : null,
      isArchived: map['isArchived'] == 1,
      isDeleted: map['isDeleted'] == 1,
    );
  }

  bool isEmpty() {
    return title.isEmpty && content.isEmpty;
  }

  void setColorScheme(Color c) {
    colorScheme = ColorScheme.fromSwatch(
        primarySwatch: Colors.primaries.firstWhere((e) => e == c));
  }

  void setTitle(String s) {
    title = s;
    lastEdited = DateTime.now();
  }

  void setContent(String s) {
    content = s;
    lastEdited = DateTime.now();
  }
}

class DatabaseHelper {
  static Database? _database;
  static final DatabaseHelper instance = DatabaseHelper._instance();

  DatabaseHelper._instance();

  Future<Database> get database async {
    if (_database != null) return _database!;
    _database = await _initDb();
    return _database!;
  }

  Future<Database> _initDb() async {
    String path = join(await getDatabasesPath(), 'database.db');
    return await openDatabase(path, version: 1, onCreate: _onCreate);
  }

  Future _onCreate(Database db, int version) async {
    await db.execute('''
      CREATE TABLE notes(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        googleId TEXT,
        title TEXT,
        content TEXT,
        lastEdited TEXT,
        colorScheme INTEGER,
        alarm TEXT,
        isArchived INTEGER,
        isDeleted INTEGER
      )
    ''');
  }

  Future<int> insertNote(Note note) async {
    Database db = await database;
    var table = await db.rawQuery('SELECT MAX(id) as max_id FROM notes');
    int currentMaxId = table.first["max_id"] as int? ?? 0;
    note.id = currentMaxId + 1;
    return await db.insert('notes', note.toMap());
  }

  Future<void> insertNotes(List<Note> notes) async {
    Database db = await database;
    Batch batch = db.batch();
    var table = await db.rawQuery('SELECT MAX(id) as max_id FROM notes');
    int currentMaxId = table.first["max_id"] as int? ?? 0;
    for (Note note in notes) {
      note.id = ++currentMaxId;
      batch.insert('notes', note.toMap());
    }
    await batch.commit();
  }

  Future<List<Note>> fetchNotes() async {
    Database db = await database;
    List<Map<String, dynamic>> notes = await db.query('notes');
    return notes.map((e) => Note.fromMap(e)).toList();
  }

  Future<Note?> fetchNote(Note note) async {
    Database db = await database;
    List<Map<String, dynamic>> maps =
        await db.query('notes', where: 'id = ?', whereArgs: [note.id]);

    if (maps.isNotEmpty) {
      return Note.fromMap(maps.first);
    }
    return null;
  }

  Future<int> updateNote(Note note) async {
    Database db = await database;
    return await db.update(
      'notes',
      note.toMap(),
      where: 'id = ?',
      whereArgs: [note.id],
    );
  }

  Future<int> deleteNote(Note note) async {
    Database db = await database;
    return await db.delete(
      'notes',
      where: 'id = ?',
      whereArgs: [note.id],
    );
  }

  Future<int> deleteDeletedNotes() async {
    Database db = await database;
    return await db.delete('notes', where: 'isDeleted = ?', whereArgs: [1]);
  }

  Future<int> deleteAllNotes() async {
    Database db = await database;
    return await db.delete('notes');
  }
}
