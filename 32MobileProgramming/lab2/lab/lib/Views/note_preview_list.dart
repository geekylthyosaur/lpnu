import 'package:flutter/material.dart';
import 'package:lab/Controllers/edit_note_page.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Views/note_preview.dart';

class NotePreviewList extends StatefulWidget {
  final List<Note> notes;
  final bool Function(Note) filter;
  final String orElse;

  const NotePreviewList(
      {super.key,
      required this.notes,
      required this.filter,
      required this.orElse});

  @override
  State<StatefulWidget> createState() => _NotePreviewListState();
}

class _NotePreviewListState extends State<NotePreviewList> {
  final GlobalKey<ScaffoldState> scaffoldKey = GlobalKey<ScaffoldState>();
  late List<Note> notes;
  late bool Function(Note) filter;

  @override
  void initState() {
    notes = widget.notes;
    filter = widget.filter;
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    if (notes.where(filter).isEmpty) {
      return Center(child: Text(widget.orElse));
    }

    return SingleChildScrollView(
      padding: const EdgeInsets.all(8.0),
      child: Column(
        children: notes
            .where(filter)
            .map((note) => Padding(
                  padding: const EdgeInsets.only(bottom: 8.0),
                  child: NotePreview(
                    note: note,
                    onPress: () async {
                      Note result = await Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (ctx) => EditNotePage(note: note)),
                      );
                      setState(() {});
                    },
                  ),
                ))
            .toList(),
      ),
    );
  }
}
