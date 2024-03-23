import 'package:flutter/material.dart';
import 'package:lab/Models/note.dart';

class NotePreview extends StatefulWidget {
  final Note note;
  final VoidCallback onPress;

  const NotePreview({super.key, required this.note, required this.onPress});

  @override
  State<StatefulWidget> createState() => _NotePreviewState();
}

class _NotePreviewState extends State<NotePreview> {
  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: widget.onPress,
      child: Container(
        width: double.infinity,
        constraints: const BoxConstraints(
          maxHeight: 200,
        ),
        decoration: BoxDecoration(
          color: widget.note.colorScheme.secondary,
          borderRadius: const BorderRadius.all(Radius.circular(24)),
        ),
        padding: const EdgeInsets.all(16),
        child: FittedBox(
          fit: BoxFit.scaleDown,
          alignment: Alignment.topLeft,
          child: SizedBox(
            width: MediaQuery.of(context).size.width - 16,
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              mainAxisSize: MainAxisSize.min,
              children: <Widget>[
                if (widget.note.title.isNotEmpty && widget.note.content.isEmpty)
                  _title(),
                if (widget.note.content.isNotEmpty && widget.note.title.isEmpty)
                  _content(),
                if (widget.note.title.isNotEmpty &&
                    widget.note.content.isNotEmpty) ...[
                  _title(),
                  const SizedBox(
                    height: 8,
                  ),
                  _content(),
                ],
              ],
            ),
          ),
        ),
      ),
    );
  }

  Widget _title() {
    return Text(
      widget.note.title,
      style: TextStyle(
        fontSize: fontSize(widget.note.title.length),
        fontWeight: FontWeight.bold,
        color: widget.note.colorScheme.onPrimary,
      ),
      overflow: TextOverflow.ellipsis,
      maxLines: 4,
    );
  }

  Widget _content() {
    return Text(
      widget.note.content,
      style: TextStyle(
        fontSize: fontSize(widget.note.content.length) / 1.5,
        color: widget.note.colorScheme.onPrimary,
      ),
      overflow: TextOverflow.fade,
      maxLines: 4,
    );
  }
}

double fontSize(int len) {
  if (len < 25) {
    return 32;
  } else if (len < 50) {
    return 24;
  } else {
    return 20;
  }
}
