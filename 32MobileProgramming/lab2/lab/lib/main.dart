import 'package:flutter/material.dart';

void main() {
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
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  void _incrementCounter() {
    setState(() {
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        leading: IconButton(icon: const Icon(Icons.menu), onPressed: () {}),
        centerTitle: true,
        toolbarHeight: 80,
        actions: [
          IconButton(icon: const Icon(Icons.person), onPressed: () {}),
        ],
      ),
      body: Center(
        child: Scrollbar(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.start,
            children: <Widget>[
            Row(mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Column(children: [
                  IconButton(icon: const Icon(Icons.arrow_upward), onPressed: () {}),
                ]),
                Column(children: [
                  IconButton(icon: const Icon(Icons.arrow_upward), onPressed: () {}),
                ]),
              ])
            ],
        ))
      ),
      bottomNavigationBar: BottomAppBar(
        height: 200,
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          children: [
            IconButton(icon: const Icon(Icons.arrow_upward), onPressed: () {}),
            const Row(mainAxisSize: MainAxisSize.max,
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                // Dates
            ],)
          ],)
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: const Icon(Icons.add),
      ),
    );
  }
}
