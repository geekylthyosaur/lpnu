import 'dart:math';

import 'package:flutter/material.dart';

class Note {
  Color color =
      Colors.primaries.elementAt(Random().nextInt(Colors.primaries.length));
  String title = "";
  String content = "";

  Note();

  void setTitle(String s) {
    title = s;
  }

  void setContent(String s) {
    content = s;
  }
}
