import 'package:flutter/material.dart';
import 'package:flutter_material_color_picker/flutter_material_color_picker.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Views/bool_dialog.dart';
import 'package:lab/Views/snack_bar.dart';

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
          onPressed: () => Navigator.of(context).pop(widget.note)),
      actions: !widget.note.isDeleted
          ? [
              IconButton(
                  onPressed: () async {
                    snackBar(context,
                        widget.note.isArchived ? 'Unarchived' : 'Archived');
                    setState(() {
                      widget.note.isArchived = !widget.note.isArchived;
                    });
                    await DatabaseHelper.instance.updateNote(widget.note);
                  },
                  icon: Icon(
                    widget.note.isArchived ? Icons.unarchive : Icons.archive,
                    color: onPrimary,
                  ))
            ]
          : [],
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
            autofocus: false,
            cursorColor: Colors.black,
            minLines: 1,
            maxLines: 4,
            style: const TextStyle(fontSize: 36),
            decoration: const InputDecoration.collapsed(hintText: 'Title'),
            onChanged: (s) => widget.note.setTitle(s),
            controller: titleCtrl,
          ),
          const Divider(
            color: Colors.transparent,
            height: 20,
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

    return Padding(
      // padding: MediaQuery.of(context).viewInsets,
      padding: EdgeInsets.zero,
      child: BottomAppBar(
        color: primary,
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: <Widget>[
            _insertCustom(),
            _colorPickerDialog(),
            Text(
              "Last edited ${formatDateTimeRoughly(widget.note.lastEdited)}",
              style: TextStyle(color: onPrimary),
            ),
            _datePicker(),
            _moreMenu(),
          ],
        ),
      ),
    );
  }

  Widget _insertCustom() {
    Color onPrimary = widget.note.colorScheme.onPrimary;

    return IconButton(
        onPressed: () {}, icon: Icon(Icons.add_box_outlined, color: onPrimary));
  }

  IconButton _colorPickerDialog() {
    Color primary = widget.note.colorScheme.primary;
    Color onPrimary = widget.note.colorScheme.onPrimary;

    return IconButton(
      icon: Icon(
        Icons.color_lens,
        color: onPrimary,
      ),
      onPressed: () => {
        showDialog(
            context: context,
            builder: (context) {
              return Theme(
                data: Theme.of(context).copyWith(
                  colorScheme: widget.note.colorScheme,
                ),
                child: AlertDialog(
                  title: const Text('Pick a color'),
                  content: SingleChildScrollView(
                    child: MaterialColorPicker(
                      allowShades: false,
                      colors: Colors.primaries,
                      onMainColorChange: (ColorSwatch? c) async {
                        if (c != null) {
                          setState(() {
                            widget.note.setColorScheme(c);
                            Navigator.of(context).pop();
                            _colorPickerDialog().onPressed!();
                          });
                          await DatabaseHelper.instance.updateNote(widget.note);
                        }
                      },
                      selectedColor: primary,
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
                ),
              );
            })
      },
    );
  }

  Widget _datePicker() {
    Color onPrimary = widget.note.colorScheme.onPrimary;

    return IconButton(
      onPressed: () async {
        final result = await showDatePicker(
          builder: (context, child) {
            return Theme(
              data: Theme.of(context).copyWith(
                colorScheme: widget.note.colorScheme,
              ),
              child: child!,
            );
          },
          context: context,
          firstDate: DateTime.now(),
          lastDate: DateTime.now().add(const Duration(days: 10000)),
          initialDate: widget.note.alarm,
          cancelText: widget.note.alarm != null ? 'Remove' : 'Cancel',
        );
        widget.note.alarm = result;
        await DatabaseHelper.instance.updateNote(widget.note);
      },
      icon: const Icon(Icons.alarm),
      color: onPrimary,
    );
  }

  Widget _moreMenu() {
    Color onPrimary = widget.note.colorScheme.onPrimary;

    return PopupMenuButton(
      offset: const Offset(0, -70),
      icon: Icon(
        Icons.more_vert,
        color: onPrimary,
      ),
      itemBuilder: (context) => <PopupMenuEntry>[
        widget.note.isDeleted
            ? _restoreMenuEntry(context)
            : _deleteMenuEntry(context),
      ],
    );
  }

  PopupMenuEntry _deleteMenuEntry(BuildContext context) {
    confirmDeleteDialog() => boolDialog(context, 'Delete note?',
        'Are you sure you want to delete this note?', 'Delete', 'Cancel');
    msg() => snackBar(context, 'Deleted');

    return PopupMenuItem(
      value: "delete",
      onTap: () async {
        if (await confirmDeleteDialog()) {
          widget.note.isDeleted = true;
          await DatabaseHelper.instance.updateNote(widget.note);
          if (context.mounted) {
            Navigator.of(context).pop(widget.note);
            msg();
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
    );
  }

  PopupMenuEntry _restoreMenuEntry(BuildContext context) {
    confirmRestoreDialog() => boolDialog(context, 'Restore note?',
        'Are you sure you want to restore this note?', 'Restore', 'Cancel');
    msg() => snackBar(context, 'Restored');

    return PopupMenuItem(
      value: "restore",
      onTap: () async {
        if (await confirmRestoreDialog()) {
          widget.note.isDeleted = false;
          widget.note.isArchived = false;
          await DatabaseHelper.instance.updateNote(widget.note);
          if (context.mounted) {
            Navigator.of(context).pop(widget.note);
            msg();
          }
        }
      },
      child: const Row(
        children: [
          Padding(
            padding: EdgeInsets.only(right: 8.0),
            child: Icon(Icons.restore),
          ),
          Text(
            'Restore',
            style: TextStyle(fontSize: 15),
          ),
        ],
      ),
    );
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
