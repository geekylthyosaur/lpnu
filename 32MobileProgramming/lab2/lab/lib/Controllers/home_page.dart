import 'package:flutter/material.dart';
import 'package:lab/Controllers/archived_notes_page.dart';
import 'package:lab/Controllers/deleted_notes_page.dart';
import 'package:lab/Controllers/edit_note_page.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Services/firebase_auth.dart';
import 'package:lab/Services/google_calendar.dart';
import 'package:lab/Views/calendar.dart';
import 'package:lab/Views/note_preview_list.dart';
import 'package:lab/Views/snack_bar.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final GlobalKey<ScaffoldState> scaffoldKey = GlobalKey<ScaffoldState>();
  late List<Note> notes;
  bool isLoading = true;
  double bottomBarHeight = 185;

  @override
  void initState() {
    super.initState();
    DatabaseHelper.instance.fetchNotes().then((result) {
      setState(() {
        notes = result;
        isLoading = false;
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    if (isLoading) {
      return const CircularProgressIndicator();
    }

    return Scaffold(
      key: scaffoldKey,
      appBar: _topBar(),
      body: _body(),
      bottomNavigationBar: _bottomBar(),
      drawer: _leftDrawer(),
      endDrawer: _rightDrawer(),
      floatingActionButton: _addButton(),
      resizeToAvoidBottomInset: false,
    );
  }

  PreferredSizeWidget _topBar() {
    return AppBar(
      backgroundColor: Theme.of(context).colorScheme.inversePrimary,
      centerTitle: true,
      toolbarHeight: 80,
      leading: IconButton(
          icon: const Icon(
            Icons.menu,
            size: 25,
          ),
          onPressed: () {
            _closeCalendar();
            scaffoldKey.currentState?.openDrawer();
          }),
      actions: [
        IconButton(
            icon: Auth.userIcon(),
            onPressed: () async {
              if (Auth.isLoggedIn) {
                _closeCalendar();
                scaffoldKey.currentState?.openEndDrawer();
              } else {
                try {
                  await Auth.signInWithGoogle();
                  setState(() {});
                } catch (e) {
                  if (mounted) {
                    snackBar(context, e.toString(), durationSec: 10);
                  }
                }
              }
            }),
      ],
    );
  }

  Widget _body() {
    filter(e) => !e.isArchived && !e.isDeleted;

    return NotePreviewList(
        notes: notes,
        filter: filter,
        orElse: "Press the button to create a note.");
  }

  Widget _bottomBar() {
    Widget inner =
        Column(mainAxisAlignment: MainAxisAlignment.start, children: [
      _isCalendarOpen()
          ? IconButton(
              icon: const Icon(Icons.arrow_downward),
              onPressed: () {
                _closeCalendar();
              })
          : IconButton(
              icon: const Icon(Icons.arrow_upward),
              onPressed: () {
                _openCalendar();
              }),
      _isCalendarOpen()
          ? Calendar(notes: notes, len: 5)
          : Calendar(notes: notes, len: 1),
    ]);

    return AnimatedContainer(
      decoration: BoxDecoration(
        boxShadow: [
          BoxShadow(spreadRadius: -5, blurRadius: _isCalendarOpen() ? 40 : 0),
        ],
      ),
      duration: const Duration(milliseconds: 250),
      height: bottomBarHeight,
      child: ClipRRect(
          borderRadius: BorderRadius.only(
            topLeft: Radius.circular(_isCalendarOpen() ? 20.0 : 0),
            topRight: Radius.circular(_isCalendarOpen() ? 20.0 : 0),
          ),
          child: BottomAppBar(
            child: SizedBox(
              height: bottomBarHeight,
              child: _isCalendarOpen()
                  ? SingleChildScrollView(
                      child: inner,
                    )
                  : inner,
            ),
          )),
    );
  }

  Widget _leftDrawer() {
    return Drawer(
      child: ListView(
        padding: EdgeInsets.zero,
        children: [
          DrawerHeader(
            decoration: BoxDecoration(
              color: Theme.of(context).colorScheme.secondary,
            ),
            child: Text(
              'Drawer Header',
              style: TextStyle(
                color: Theme.of(context).colorScheme.onSecondary,
                fontSize: 24,
              ),
            ),
          ),
          ListTile(
            leading: const Icon(Icons.settings),
            title: const Text('Settings'),
            onTap: () {
              // TODO: Open settings.
              Navigator.pop(context);
            },
          ),
          ListTile(
            leading: const Icon(Icons.archive),
            title: const Text('Archived'),
            onTap: () async {
              Navigator.pop(context);
              await Navigator.push(
                context,
                MaterialPageRoute(
                    builder: (ctx) => ArchivedNotesPage(notes: notes)),
              );
              // Trigger redraw.
              setState(() {});
            },
          ),
          ListTile(
            leading: const Icon(Icons.delete),
            title: const Text('Deleted'),
            onTap: () async {
              Navigator.pop(context);
              await Navigator.push(
                context,
                MaterialPageRoute(
                    builder: (ctx) => DeletedNotesPage(notes: notes)),
              );
              // Trigger redraw.
              setState(() {});
            },
          ),
          ListTile(
            leading: const Icon(Icons.help),
            title: const Text('Help'),
            onTap: () {
              // TODO: Open Help.
              Navigator.pop(context);
            },
          ),
          ListTile(
            leading: const Icon(Icons.info),
            title: const Text('About'),
            onTap: () {
              Navigator.pop(context);
              showAboutDialog(context: context);
            },
          ),
        ],
      ),
    );
  }

  Widget _rightDrawer() {
    return Drawer(
      child: ListView(
        padding: EdgeInsets.zero,
        children: [
          DrawerHeader(
            decoration: BoxDecoration(
              color: Theme.of(context).colorScheme.secondary,
            ),
            child: Text(
              'Drawer Header',
              style: TextStyle(
                color: Theme.of(context).colorScheme.onSecondary,
                fontSize: 24,
              ),
            ),
          ),
          ListTile(
            leading: const Icon(Icons.account_box),
            title: const Text('Account'),
            onTap: () {
              // TODO: Open account.
              Navigator.pop(context);
            },
          ),
          ListTile(
            leading: const Icon(Icons.sync),
            title: const Text('Sync'),
            onTap: () async {
              Navigator.pop(context);
              try {
                List<Note> result = (await GoogleCalendar.load())
                    .where((gn) => !notes.any((n) => gn.googleId == n.googleId))
                    .toList();
                await DatabaseHelper.instance.insertNotes(result);
                setState(() {
                  notes.addAll(result);
                });
              } catch (e) {
                if (mounted) {
                  snackBar(context, e.toString(), durationSec: 10);
                }
              }
            },
          ),
          ListTile(
            leading: const Icon(Icons.logout),
            title: const Text('Log out'),
            onTap: () async {
              try {
                await Auth.signOutFromGoogle();
                setState(() {});
              } catch (e) {
                if (mounted) {
                  snackBar(context, e.toString(), durationSec: 10);
                }
              }
              if (mounted) {
                Navigator.pop(context);
              }
            },
          ),
          ListTile(
            leading: const Icon(Icons.privacy_tip),
            title: const Text('Privacy'),
            onTap: () async {
              // TODO: Open privacy.
              Navigator.pop(context);
              await DatabaseHelper.instance.deleteAllNotes();
              setState(() {
                notes.clear();
              });
            },
          ),
        ],
      ),
    );
  }

  Widget _addButton() {
    return FloatingActionButton(
      onPressed: () async {
        _closeCalendar();
        Note result = await Navigator.push(
          context,
          MaterialPageRoute(builder: (ctx) => EditNotePage(note: Note())),
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
      },
      child: const Icon(Icons.add),
    );
  }

  void _openCalendar() {
    setState(() {
      bottomBarHeight = 700;
    });
  }

  void _closeCalendar() {
    setState(() {
      bottomBarHeight = 185;
    });
  }

  bool _isCalendarOpen() {
    return bottomBarHeight == 700;
  }
}
