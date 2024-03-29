import 'package:collection/collection.dart';
import 'package:flutter/material.dart';
import 'package:lab/Controllers/edit_note_page.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Views/note_preview.dart';

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
    comparator = widget.comparator ?? (a, b) => a.id.compareTo(b.id);
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    if (notes.where(filter).isEmpty) {
      return Center(child: Text(widget.orElse));
    }

    return SingleChildScrollView(
      padding: const EdgeInsets.all(8),
      child: Column(
        children: notes
            .where(filter)
            .sorted(comparator)
            .map((note) => Padding(
                  padding: const EdgeInsets.only(bottom: 8),
                  child: NotePreview(
                    note: note,
                    onPress: () async {
                      Note result = await Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (ctx) => EditNotePage(note: note)),
                      );
                      if (!result.isEmpty()) {
                        if (notes.any((note) => note.id == result.id)) {
                          await DatabaseHelper.instance.updateNote(result);
                          setState(() {
                            int index = notes
                                .indexWhere((note) => note.id == result.id);
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
                    },
                  ),
                ))
            .toList(),
      ),
    );
  }
}
