import 'package:flutter/material.dart';
import 'package:lab/Pages/archived_notes.dart';
import 'package:lab/Pages/deleted_notes.dart';
import 'package:lab/Pages/edit_note.dart';
import 'package:lab/Pages/privacy.dart';
import 'package:lab/Pages/options.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Services/firebase_auth.dart';
import 'package:lab/Services/google_calendar.dart';
import 'package:lab/Widgets/calendar.dart';
import 'package:lab/Widgets/note_preview_list.dart';
import 'package:lab/Widgets/snack_bar.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final GlobalKey<ScaffoldState> scaffoldKey = GlobalKey<ScaffoldState>();
  late List<Note> notes;
  bool isLoading = true;

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
      return const LinearProgressIndicator();
    }

    return Scaffold(
      key: scaffoldKey,
      appBar: _topBar(),
      body: _body(),
      bottomNavigationBar: _bottomBar(),
      drawer: _leftDrawer(),
      endDrawer: Auth.isLoggedIn ? _rightDrawer() : null,
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
            scaffoldKey.currentState?.openDrawer();
          }),
      actions: [
        IconButton(
            icon: Auth.userIcon,
            onPressed: () async {
              if (Auth.isLoggedIn) {
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
    void openFullCalendar() => showModalBottomSheet<void>(
          context: context,
          isScrollControlled: true,
          builder: (BuildContext context) {
            return Calendar.full(context, notes);
          },
        );

    return GestureDetector(
        onVerticalDragUpdate: (details) {
          if (details.delta.dy < 0) {
            openFullCalendar();
          }
        },
        child: BottomAppBar(
            height: 190,
            child:
                Column(mainAxisAlignment: MainAxisAlignment.start, children: [
              IconButton(
                  icon: const Icon(Icons.arrow_upward),
                  onPressed: () => openFullCalendar()),
              Calendar.preview(notes),
            ])));
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
              'Lab',
              style: TextStyle(
                color: Theme.of(context).colorScheme.onSecondary,
                fontSize: 24,
              ),
            ),
          ),
          ListTile(
            leading: const Icon(Icons.settings),
            title: const Text('Settings'),
            onTap: () async {
              Navigator.pop(context);
              await Navigator.of(context).push(
                  MaterialPageRoute(builder: (ctx) => const OptionsPage()));
              setState(() {});
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
          if (false)
            ListTile(
              leading: const Icon(Icons.help),
              title: const Text('Help'),
              onTap: () async {
                // TODO: Open Help.
                Navigator.pop(context);
                await DatabaseHelper.instance.deleteAllNotes();
                setState(() {
                  notes.clear();
                });
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
              Auth.userName!,
              style: TextStyle(
                color: Theme.of(context).colorScheme.onSecondary,
                fontSize: 24,
              ),
            ),
          ),
          if (false)
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
              Navigator.pop(context);
              Navigator.of(context).push(
                  MaterialPageRoute(builder: (ctx) => const PrivacyPage()));
            },
          ),
        ],
      ),
    );
  }

  Widget _addButton() {
    return FloatingActionButton(
      onPressed: () async {
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
}
