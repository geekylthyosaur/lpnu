import 'package:flutter/material.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Views/note_preview_list.dart';

class UpcomingNotesList extends StatefulWidget {
  final List<Note> notes;

  const UpcomingNotesList({super.key, required this.notes});

  @override
  State<UpcomingNotesList> createState() => _UpcomingNotesListState();
}

class _UpcomingNotesListState extends State<UpcomingNotesList> {
  @override
  Widget build(BuildContext context) {
    filter(e) => e.alarm != null;
    int comparator(a, b) => a.alarm.compareTo(b.alarm);

    return Column(
      children: [
        const SizedBox(height: 8),
        const Text(
          'Upcoming',
          style: TextStyle(fontSize: 24, fontWeight: FontWeight.w500),
        ),
        const SizedBox(height: 8),
        NotePreviewList(
            notes: widget.notes,
            filter: filter,
            comparator: comparator,
            orElse: "Nothing is here."),
      ],
    );
  }
}
