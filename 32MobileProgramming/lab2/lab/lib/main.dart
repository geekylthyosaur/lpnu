import 'package:flutter/material.dart';
import 'package:lab/Pages/home.dart';
import 'package:lab/Services/firebase_auth.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Auth.init();

  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Lab',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const HomePage(),
    );
  }
}
