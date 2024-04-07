import 'package:flutter/material.dart';
import 'package:lab/Pages/home.dart';
import 'package:lab/Services/firebase_auth.dart';
import 'package:lab/app_options.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Auth.init();

  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return ValueListenableBuilder<ThemeMode>(
        valueListenable: AppOptions.themeMode,
        builder: (context, themeMode, _) {
          return MaterialApp(
            title: 'Lab',
            theme: ThemeData(
              brightness: Brightness.light,
              useMaterial3: true,
            ),
            darkTheme: ThemeData(
              brightness: Brightness.dark,
              useMaterial3: true,
            ),
            themeMode: AppOptions.themeMode.value,
            debugShowCheckedModeBanner: false,
            home: const HomePage(),
          );
        });
  }
}
