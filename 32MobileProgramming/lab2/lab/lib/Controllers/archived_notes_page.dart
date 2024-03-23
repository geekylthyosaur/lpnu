import 'package:flutter/material.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Views/note_preview_list.dart';

class ArchivedNotesPage extends StatefulWidget {
  final List<Note> notes;

  const ArchivedNotesPage({super.key, required this.notes});

  @override
  State<ArchivedNotesPage> createState() => _ArchivedNotesPageState();
}

class _ArchivedNotesPageState extends State<ArchivedNotesPage> {
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
      title: const Text("Archived"),
    );
  }

  Widget _body() {
    filter(e) => e.isArchived && !e.isDeleted;

    return NotePreviewList(
        notes: widget.notes, filter: filter, orElse: "Nothing is here.");
  }
}
