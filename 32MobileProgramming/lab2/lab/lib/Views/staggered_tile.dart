import 'package:flutter/material.dart';
import 'package:lab/Models/note.dart';

class StaggeredTile extends StatefulWidget {
  final Note note;
  final VoidCallback onPress;

  const StaggeredTile({super.key, required this.note, required this.onPress});

  @override
  State<StatefulWidget> createState() => _StaggeredTileState();
}

class _StaggeredTileState extends State<StaggeredTile> {
  late Note note;

  @override
  void initState() {
    note = widget.note;
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: widget.onPress,
      child: Container(
        decoration: BoxDecoration(
            color: note.colorScheme.secondary,
            borderRadius: const BorderRadius.all(Radius.circular(8))),
        padding: const EdgeInsets.all(8),
        child: Text(note.title.isEmpty ? note.content : note.title),
      ),
    );
  }
}
