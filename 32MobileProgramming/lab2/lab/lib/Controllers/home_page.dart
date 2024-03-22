import 'package:flutter/material.dart';
import 'package:lab/Controllers/add_note_page.dart';

class HomePage extends StatefulWidget {
  HomePage({super.key});

  final List<DateTime> thisWeek = getWeekDates();

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final GlobalKey<ScaffoldState> scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      key: scaffoldKey,
      appBar: _topBar(),
      body: _body(),
      bottomNavigationBar: _bottomBar(),
      endDrawer: _rightDrawer(),
      drawer: _leftDrawer(),
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
    return const Center(/* TODO: Items. */);
  }

  Widget _bottomBar() {
    return BottomAppBar(
        height: 200,
        child: Column(mainAxisAlignment: MainAxisAlignment.start, children: [
          IconButton(icon: const Icon(Icons.arrow_upward), onPressed: () {}),
          Row(
              mainAxisSize: MainAxisSize.max,
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Column(children: [
                  const Text("Mon"),
                  Text(widget.thisWeek[0].day.toString()),
                ]),
                Column(children: [
                  const Text("Tue"),
                  Text(widget.thisWeek[1].day.toString()),
                ]),
                Column(children: [
                  const Text("Wed"),
                  Text(widget.thisWeek[2].day.toString()),
                ]),
                Column(children: [
                  const Text("Thu"),
                  Text(widget.thisWeek[3].day.toString()),
                ]),
                Column(children: [
                  const Text("Fri"),
                  Text(widget.thisWeek[4].day.toString()),
                ]),
                Column(children: [
                  const Text("Sat"),
                  Text(widget.thisWeek[5].day.toString()),
                ]),
                Column(children: [
                  const Text("Sun"),
                  Text(widget.thisWeek[6].day.toString()),
                ]),
              ])
        ]));
  }

  Widget _rightDrawer() {
    return Drawer(
      child: ListView(
        padding: EdgeInsets.zero,
        children: [
          DrawerHeader(
            decoration: BoxDecoration(
              color: Theme.of(context).colorScheme.inversePrimary,
            ),
            child: const Text(
              'Drawer Header',
              style: TextStyle(
                color: Colors.white,
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
          ListTile(
            leading: const Icon(Icons.info),
            title: const Text('About'),
            onTap: () {
              // TODO: Open about.
              Navigator.pop(context);
            },
          ),
        ],
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
              color: Theme.of(context).colorScheme.inversePrimary,
            ),
            child: const Text(
              'Drawer Header',
              style: TextStyle(
                color: Colors.white,
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
            title: const Text('Archive'),
            onTap: () {
              // TODO: Open archive.
              Navigator.pop(context);
            },
          ),
          ListTile(
            leading: const Icon(Icons.delete),
            title: const Text('Deleted'),
            onTap: () {
              // TODO: Open deleted.
              Navigator.pop(context);
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
              // TODO: Open about.
              Navigator.pop(context);
            },
          ),
        ],
      ),
    );
  }

  Widget _addButton() {
    return FloatingActionButton(
      onPressed: () => Navigator.push(
          context, MaterialPageRoute(builder: (ctx) => AddNotePage())),
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
