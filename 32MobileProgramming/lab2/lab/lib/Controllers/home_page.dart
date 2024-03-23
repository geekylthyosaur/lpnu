import 'package:flutter/material.dart';
import 'package:lab/Controllers/archived_notes_page.dart';
import 'package:lab/Controllers/deleted_notes_page.dart';
import 'package:lab/Controllers/edit_note_page.dart';
import 'package:lab/Models/note.dart';
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
  double bottomBarHeight = 170;

  @override
  void initState() {
    _loadNotes();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
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

  void _loadNotes() async {
    notes = [];
  }

  PreferredSizeWidget _topBar() {
    return AppBar(
      backgroundColor: Theme.of(context).colorScheme.inversePrimary,
      centerTitle: true,
      toolbarHeight: 80,
      leading: IconButton(
          icon: const Icon(Icons.menu),
          onPressed: () {
            _closeCalendar();
            scaffoldKey.currentState?.openDrawer();
          }),
      actions: [
        IconButton(
            icon: const Icon(Icons.person),
            onPressed: () {
              _closeCalendar();
              scaffoldKey.currentState?.openEndDrawer();
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
              child: SingleChildScrollView(
                child: Column(
                    mainAxisAlignment: MainAxisAlignment.start,
                    children: [
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
                    ]),
              ),
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
            onTap: () {
              // TODO: Open sync.
              Navigator.pop(context);
            },
          ),
          ListTile(
            leading: const Icon(Icons.logout),
            title: const Text('Log out'),
            onTap: () {
              // TODO: Open log out.
              Navigator.pop(context);
            },
          ),
          ListTile(
            leading: const Icon(Icons.privacy_tip),
            title: const Text('Privacy'),
            onTap: () {
              // TODO: Open privacy.
              Navigator.pop(context);
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
          setState(() {
            notes.add(result);
          });
        } else if (mounted) {
          snackBar(context, 'Discarded');
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
      bottomBarHeight = 170;
    });
  }

  bool _isCalendarOpen() {
    return bottomBarHeight == 700;
  }
}
