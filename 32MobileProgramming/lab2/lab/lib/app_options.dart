import 'package:flutter/material.dart';

class AppOptions {
  static final ValueNotifier<ThemeMode> themeMode =
      ValueNotifier(ThemeMode.light);
}
