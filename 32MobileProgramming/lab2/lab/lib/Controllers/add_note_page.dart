import 'package:flutter/material.dart';
import 'package:lab/Models/note.dart';

class AddNotePage extends StatefulWidget {
  final Note note = Note();

  AddNotePage({super.key});

  @override
  State<AddNotePage> createState() => _AddNotePageState();
}

class _AddNotePageState extends State<AddNotePage> {
  final GlobalKey<ScaffoldState> scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      key: scaffoldKey,
      appBar: _topBar(),
      body: _body(),
      bottomNavigationBar: _bottomBar(),
    );
  }

  PreferredSizeWidget _topBar() {
    Color invertColor(Color color) =>
        color.computeLuminance() > 0.5 ? Colors.black : Colors.white;

    return AppBar(
        backgroundColor: widget.note.color,
        centerTitle: true,
        toolbarHeight: 80,
        leading: BackButton(color: invertColor(widget.note.color)));
  }

  Widget _body() {
    return Container(
      padding: const EdgeInsets.only(left: 16, right: 16, top: 12),
      child: Column(
        children: [
          TextField(
            autofocus: true,
            cursorColor: Colors.black,
            minLines: 1,
            maxLines: 4,
            style: const TextStyle(fontSize: 36),
            decoration: const InputDecoration.collapsed(hintText: 'Title'),
            onChanged: (s) => widget.note.setTitle(s),
          ),
          TextField(
            cursorColor: Colors.black,
            minLines: 1,
            maxLines: 12,
            style: const TextStyle(fontSize: 20),
            decoration: const InputDecoration.collapsed(hintText: 'Note'),
            onChanged: (s) => widget.note.setContent(s),
          ),
        ],
      ),
    );
  }

  Widget _bottomBar() {
    return BottomNavigationBar(items: const [
      BottomNavigationBarItem(icon: Icon(Icons.account_box), label: "asd"),
      BottomNavigationBarItem(icon: Icon(Icons.account_box), label: "asd")
    ]);
  }
}
