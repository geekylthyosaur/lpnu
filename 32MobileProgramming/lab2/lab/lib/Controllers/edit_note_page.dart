import 'package:flutter/material.dart';
import 'package:flutter_material_color_picker/flutter_material_color_picker.dart';
import 'package:lab/Models/note.dart';

abstract class EditNoteResult {
  const EditNoteResult._();

  factory EditNoteResult.create(Note note) = EditNote;

  factory EditNoteResult.delete(Note note) = DeleteNote;
}

class EditNote extends EditNoteResult {
  final Note note;

  const EditNote(this.note) : super._();
}

class DeleteNote extends EditNoteResult {
  final Note note;

  const DeleteNote(this.note) : super._();
}

class EditNotePage extends StatefulWidget {
  final Note note;

  const EditNotePage({super.key, required this.note});

  @override
  State<EditNotePage> createState() => _EditNotePageState();
}

class _EditNotePageState extends State<EditNotePage> {
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
    Color primary = widget.note.colorScheme.primary;
    Color onPrimary = widget.note.colorScheme.onPrimary;

    return AppBar(
      backgroundColor: primary,
      centerTitle: true,
      toolbarHeight: 80,
      leading: BackButton(
          color: onPrimary,
          onPressed: () => Navigator.of(context).pop(EditNote(widget.note))),
      actions: [
        IconButton(
            onPressed: () {
              setState(() {
                widget.note.isArchived = !widget.note.isArchived;
              });
            },
            icon: Icon(
              widget.note.isArchived ? Icons.unarchive : Icons.archive,
              color: onPrimary,
            ))
      ],
    );
  }

  Widget _body() {
    TextEditingController titleCtrl = TextEditingController();
    titleCtrl.text = widget.note.title;
    TextEditingController contentCtrl = TextEditingController();
    contentCtrl.text = widget.note.content;

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
            controller: titleCtrl,
          ),
          TextField(
            cursorColor: Colors.black,
            minLines: 1,
            maxLines: 12,
            style: const TextStyle(fontSize: 20),
            decoration: const InputDecoration.collapsed(hintText: 'Note'),
            onChanged: (s) => widget.note.setContent(s),
            controller: contentCtrl,
          ),
        ],
      ),
    );
  }

  Widget _bottomBar() {
    Color primary = widget.note.colorScheme.primary;
    Color onPrimary = widget.note.colorScheme.onPrimary;

    return BottomAppBar(
      color: primary,
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: <Widget>[
          IconButton(
            icon: Icon(
              Icons.color_lens,
              color: onPrimary,
            ),
            onPressed: _colorPickerDialog,
          ),
          Text(
            "Last edited ${formatDateTimeRoughly(widget.note.lastEdited)}",
            style: TextStyle(color: onPrimary),
          ),
          PopupMenuButton(
            offset: const Offset(0, -70),
            icon: Icon(
              Icons.more_vert,
              color: onPrimary,
            ),
            itemBuilder: (context) => <PopupMenuEntry>[
              PopupMenuItem(
                value: "delete",
                onTap: () async {
                  if (await _confirmDeleteDialog()) {
                    widget.note.isDeleted = true;
                    if (context.mounted) {
                      Navigator.of(context).pop(DeleteNote(widget.note));
                    }
                  }
                },
                child: const Row(
                  children: [
                    Padding(
                      padding: EdgeInsets.only(right: 8.0),
                      child: Icon(Icons.delete),
                    ),
                    Text(
                      'Delete',
                      style: TextStyle(fontSize: 15),
                    ),
                  ],
                ),
              ),
            ],
          )
        ],
      ),
    );
  }

  void _colorPickerDialog() {
    showDialog(
        context: context,
        builder: (context) {
          return AlertDialog(
            title: const Text('Pick a color'),
            content: SingleChildScrollView(
              child: MaterialColorPicker(
                allowShades: false,
                colors: Colors.primaries,
                onMainColorChange: (ColorSwatch? c) {
                  if (c != null) {
                    setState(() {
                      widget.note.setColorScheme(c);
                    });
                  }
                },
                selectedColor: widget.note.colorScheme.primary,
              ),
            ),
            actions: <Widget>[
              ElevatedButton(
                child: const Text('Close'),
                onPressed: () {
                  Navigator.of(context).pop();
                },
              ),
            ],
          );
        });
  }

  Future<bool> _confirmDeleteDialog() async {
    final result = await showDialog<bool>(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: const Text('Delete note?'),
          content: const Text('Are you sure you want to delete this note?'),
          actions: <Widget>[
            TextButton(
              child: const Text('Cancel'),
              onPressed: () => Navigator.of(context).pop(false),
            ),
            ElevatedButton(
              child: const Text('Delete'),
              onPressed: () => Navigator.of(context).pop(true),
            ),
          ],
        );
      },
    );

    return result ?? false;
  }
}

String formatDateTimeRoughly(DateTime dateTime) {
  final now = DateTime.now();
  final difference = now.difference(dateTime);

  if (difference.inSeconds < 60) {
    return 'now';
  } else if (difference.inMinutes < 2) {
    return 'a minute ago';
  } else if (difference.inMinutes < 60) {
    return '${difference.inMinutes} minutes ago';
  } else if (difference.inHours < 2) {
    return 'an hour ago';
  } else if (difference.inHours < 24) {
    return '${difference.inHours} hours ago';
  } else if (difference.inDays < 2) {
    return 'yesterday';
  } else {
    return '${difference.inDays} days ago';
  }
}
