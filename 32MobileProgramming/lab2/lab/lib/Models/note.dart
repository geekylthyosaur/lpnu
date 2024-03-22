import 'dart:math';

import 'package:flutter/material.dart';
import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';

class Note {
  int? id;
  ColorScheme colorScheme = ColorScheme.fromSwatch(
      primarySwatch: Colors.primaries
          .elementAt(Random().nextInt(Colors.primaries.length)));
  String title = "";
  String content = "";
  DateTime lastEdited = DateTime.now();
  bool isArchived = false;
  bool isDeleted = false;

  Note({
    this.id,
    ColorScheme? colorScheme,
    this.title = "",
    this.content = "",
    DateTime? lastEdited,
    this.isArchived = false,
    this.isDeleted = false,
  }) {
    this.lastEdited = lastEdited ?? DateTime.now();
    this.colorScheme = ColorScheme.fromSwatch(
        primarySwatch: Colors.primaries
            .elementAt(Random().nextInt(Colors.primaries.length)));
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

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'colorScheme': colorScheme.primary.value,
      'title': title,
      'content': content,
      'lastEdited': lastEdited.toIso8601String(),
      'isArchived': isArchived ? 1 : 0,
      'isDeleted': isDeleted ? 1 : 0,
    };
  }

  static Note fromMap(Map<String, dynamic> map) {
    return Note(
      id: map['id'],
      colorScheme: ColorScheme.fromSwatch(
          primarySwatch: Colors.primaries
              .firstWhere((e) => e == Color(map['colorScheme']))),
      title: map['title'],
      content: map['content'],
      lastEdited: DateTime.parse(map['lastEdited']),
      isArchived: map['isArchived'] == 1,
      isDeleted: map['isDeleted'] == 1,
    );
  }

  void persist() {
    () async {
      return await DatabaseHelper.addNote(this);
    };
  }

  static Future<List<Note>> all() {
    return DatabaseHelper.getNotes();
  }
}

class DatabaseHelper {
  static final DatabaseHelper instance = DatabaseHelper._init();

  static Database? _database;

  DatabaseHelper._init();

  Future<Database> get database async {
    if (_database != null) return _database!;

    _database = await _initDB('notes.db');
    return _database!;
  }

  Future<Database> _initDB(String filePath) async {
    final dbPath = await getDatabasesPath();
    final path = join(dbPath, filePath);

    return await openDatabase(path, version: 1, onCreate: _createDB);
  }

  Future _createDB(Database db, int version) async {
    await db.execute('''
      CREATE TABLE notes(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        colorScheme TEXT NOT NULL,
        title TEXT NOT NULL,
        content TEXT NOT NULL,
        lastEdited TEXT NOT NULL,
        isArchived INTEGER NOT NULL,
        isDeleted INTEGER NOT NULL
      )
    ''');
  }

  static Future<int> addNote(Note note) async {
    final db = await instance.database;
    final id = await db.insert('notes', note.toMap());
    return id;
  }

  static Future<List<Note>> getNotes() async {
    final db = await instance.database;
    final maps = await db.query(
      'notes',
      where: 'isArchived = ? AND isDeleted = ?',
      whereArgs: [0, 0],
    );
    return List.generate(maps.length, (i) {
      return Note.fromMap(maps[i]);
    });
  }

  static Future<Note?> getNote(int id) async {
    final db = await instance.database;
    final maps = await db.query(
      'notes',
      where: 'id = ?',
      whereArgs: [id],
      limit: 1,
    );
    if (maps.isNotEmpty) {
      return Note.fromMap(maps.first);
    }
    return null;
  }

  static Future<List<Note>> getDeletedNotes() async {
    final db = await instance.database;
    final maps = await db.query(
      'notes',
      where: 'isDeleted = ?',
      whereArgs: [1],
    );
    return List.generate(maps.length, (i) {
      return Note.fromMap(maps[i]);
    });
  }

  static Future<List<Note>> getArchivedNotes() async {
    final db = await instance.database;
    final maps = await db.query(
      'notes',
      where: 'isArchived = ? AND isDeleted = ?',
      whereArgs: [1, 0],
    );
    return List.generate(maps.length, (i) {
      return Note.fromMap(maps[i]);
    });
  }

  static Future<int> deleteNote(int id) async {
    final db = await instance.database;
    return await db.update(
      'notes',
      {'isDeleted': 1},
      where: 'id = ?',
      whereArgs: [id],
    );
  }

  static Future<int> archiveNote(int id) async {
    final db = await instance.database;
    return await db.update(
      'notes',
      {'isArchived': 1},
      where: 'id = ?',
      whereArgs: [id],
    );
  }
}
