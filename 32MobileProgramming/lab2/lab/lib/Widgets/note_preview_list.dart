import 'package:collection/collection.dart';
import 'package:flutter/material.dart';
import 'package:lab/Pages/edit_note.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Widgets/note_preview.dart';

class NotePreviewList extends StatefulWidget {
  final List<Note> notes;
  final bool Function(Note) filter;
  final Comparator<Note>? comparator;
  final String orElse;

  const NotePreviewList(
      {super.key,
      required this.notes,
      required this.filter,
      this.comparator,
      required this.orElse});

  @override
  State<StatefulWidget> createState() => _NotePreviewListState();
}

class _NotePreviewListState extends State<NotePreviewList> {
  final GlobalKey<ScaffoldState> scaffoldKey = GlobalKey<ScaffoldState>();
  late List<Note> notes;
  late bool Function(Note) filter;
  late Comparator<Note> comparator;

  @override
  void initState() {
    notes = widget.notes;
    filter = widget.filter;
    comparator = widget.comparator ??
        (a, b) => a.lastEdited.compareTo(b.lastEdited) * (-1);
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    if (notes.where(filter).isEmpty) {
      return Center(child: Text(widget.orElse));
    }

    var iter = notes.where(filter).sorted(comparator).map((note) => Padding(
          padding: const EdgeInsets.only(bottom: 8),
          child: NotePreview(
            note: note,
            onPress: () async {
              await _onPress(note);
            },
          ),
        ));

    return ListView.builder(
      padding: const EdgeInsets.all(10),
      shrinkWrap: true,
      itemBuilder: (context, n) => iter.elementAtOrNull(n),
    );
  }

  Future<void> _onPress(Note note) async {
    Note result = await Navigator.push(
      context,
      MaterialPageRoute(builder: (ctx) => EditNotePage(note: note)),
    );
    if (!result.isEmpty()) {
      if (notes.any((note) => note.id == result.id)) {
        await DatabaseHelper.instance.updateNote(result);
        setState(() {
          int index = notes.indexWhere((note) => note.id == result.id);
          if (index != -1) {
            notes[index] = result;
          }
        });
      } else {
        await DatabaseHelper.instance.insertNote(result);
        setState(() {
          notes.add(result);
        });
      }
    } else {
      if (notes.any((note) => note.id == result.id)) {
        await DatabaseHelper.instance.deleteNote(result);
        setState(() {
          notes.removeWhere((note) => note.id == result.id);
        });
      }
    }
  }
}
