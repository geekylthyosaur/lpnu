import 'package:flutter/material.dart';
import 'package:lab/Controllers/archived_notes_page.dart';
import 'package:lab/Controllers/deleted_notes_page.dart';
import 'package:lab/Controllers/edit_note_page.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Views/note_preview_list.dart';

class HomePage extends StatefulWidget {
  HomePage({super.key});

  final List<DateTime> thisWeek = getWeekDates();

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final GlobalKey<ScaffoldState> scaffoldKey = GlobalKey<ScaffoldState>();
  late List<Note> notes;

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
          onPressed: () => scaffoldKey.currentState?.openDrawer()),
      actions: [
        IconButton(
            icon: const Icon(Icons.person),
            onPressed: () => scaffoldKey.currentState?.openEndDrawer()),
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
    return BottomAppBar(
      height: 160,
      child: SizedBox(
        child: Column(mainAxisAlignment: MainAxisAlignment.start, children: [
          IconButton(icon: const Icon(Icons.arrow_upward), onPressed: () {}),
          Padding(
            padding: const EdgeInsets.symmetric(vertical: 8),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: widget.thisWeek.asMap().entries.map((entry) {
                int idx = entry.key;
                DateTime day = entry.value;
                List<String> weekdays = [
                  "Mon",
                  "Tue",
                  "Wed",
                  "Thu",
                  "Fri",
                  "Sat",
                  "Sun"
                ];
                return Column(mainAxisSize: MainAxisSize.min, children: [
                  Text(
                    weekdays[idx],
                    style: TextStyle(
                        color:
                            Theme.of(context).colorScheme.onSecondaryContainer),
                    textAlign: TextAlign.center,
                  ),
                  Container(
                    padding:
                        const EdgeInsets.symmetric(vertical: 8, horizontal: 12),
                    margin: const EdgeInsets.only(top: 4),
                    decoration: BoxDecoration(
                      color: Theme.of(context).colorScheme.primaryContainer,
                      borderRadius: BorderRadius.circular(10),
                      border: DateTime.now().day == day.day &&
                              DateTime.now().month == day.month &&
                              DateTime.now().year == day.year
                          ? Border.all(
                              color: Theme.of(context).colorScheme.outline,
                              width: 4)
                          : null,
                    ),
                    child: Text(
                      day.day.toString(),
                      style: TextStyle(
                          color:
                              Theme.of(context).colorScheme.onPrimaryContainer),
                      textAlign: TextAlign.center,
                    ),
                  ),
                ]);
              }).toList(),
            ),
          ),
        ]),
      ),
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
        Note result = await Navigator.push(
          context,
          MaterialPageRoute(builder: (ctx) => EditNotePage(note: Note())),
        );
        if (!result.isEmpty()) {
          setState(() {
            notes.add(result);
          });
        }
      },
      child: const Icon(Icons.add),
    );
  }
}

List<DateTime> getWeekDates() {
  final now = DateTime.now();
  final sunday = now.subtract(Duration(days: now.weekday - DateTime.monday));

  List<DateTime> weekDates = [];
  for (int i = 0; i < 7; i++) {
    weekDates.add(sunday.add(Duration(days: i)));
  }

  return weekDates;
}
