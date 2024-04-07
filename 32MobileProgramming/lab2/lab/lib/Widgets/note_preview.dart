import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
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
          minHeight: 10,
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
                if (widget.note.title.isEmpty && widget.note.content.isEmpty)
                  const SizedBox(
                    height: 8,
                  ),
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
                if (widget.note.alarm != null &&
                    widget.note.alarm!.compareTo(DateTime.now()) > 0) ...[
                  const SizedBox(
                    height: 8,
                  ),
                  Row(
                    mainAxisSize: MainAxisSize.min,
                    children: <Widget>[
                      if (widget.note.isArchived)
                        Icon(
                          Icons.archive_outlined,
                          color: widget.note.colorScheme.onPrimary,
                          size: 24,
                        ),
                      Icon(
                        Icons.alarm,
                        color: widget.note.colorScheme.onPrimary,
                        size: 24,
                      ),
                      const SizedBox(width: 4),
                      Text(
                        DateFormat('EEE dd MMMM').format(widget.note.alarm!),
                        style: TextStyle(
                          color: widget.note.colorScheme.onPrimary,
                          fontSize: 16,
                        ),
                      ),
                    ],
                  )
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
