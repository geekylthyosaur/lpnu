import 'package:flutter/material.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Views/note_preview_list.dart';

class DeletedNotesPage extends StatefulWidget {
  final List<Note> notes;

  const DeletedNotesPage({super.key, required this.notes});

  @override
  State<DeletedNotesPage> createState() => _DeletedNotesPageState();
}

class _DeletedNotesPageState extends State<DeletedNotesPage> {
  final GlobalKey<ScaffoldState> scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      key: scaffoldKey,
      appBar: _topBar(),
      body: _body(),
      resizeToAvoidBottomInset: false,
    );
  }

  PreferredSizeWidget _topBar() {
    return AppBar(
      backgroundColor: Theme.of(context).colorScheme.inversePrimary,
      centerTitle: true,
      toolbarHeight: 80,
      leading: IconButton(
        icon: const Icon(Icons.arrow_back),
        onPressed: () => Navigator.of(context).pop(widget.notes),
      ),
      title: const Text("Deleted"),
    );
  }

  Widget _body() {
    bool filter(e) => e.isDeleted;

    return NotePreviewList(
        notes: widget.notes, filter: filter, orElse: "Nothing is here.");
  }
}
