import 'package:flutter/material.dart';
import 'package:lab/app_options.dart';
import 'package:settings_ui/settings_ui.dart';

class OptionsPage extends StatefulWidget {
  const OptionsPage({super.key});

  @override
  State<OptionsPage> createState() => _OptionsPageState();
}

class _OptionsPageState extends State<OptionsPage> {
  final GlobalKey<ScaffoldState> scaffoldKey = GlobalKey<ScaffoldState>();
  var enableDarkMode = AppOptions.themeMode.value == ThemeMode.dark;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      key: scaffoldKey,
      appBar: _topBar(),
      body: _body(),
    );
  }

  PreferredSizeWidget _topBar() {
    return AppBar(
      backgroundColor: Theme.of(context).colorScheme.inversePrimary,
      toolbarHeight: 80,
      title: const Text("Options"),
      centerTitle: true,
    );
  }

  Widget _body() {
    return SettingsList(
      sections: [
        SettingsSection(
          title: const Text('View'),
          tiles: <SettingsTile>[
            SettingsTile.switchTile(
              onToggle: (value) {
                setState(() {
                  enableDarkMode = value;
                  AppOptions.themeMode.value =
                      value ? ThemeMode.dark : ThemeMode.light;
                });
              },
              initialValue: enableDarkMode,
              leading: const Icon(Icons.dark_mode),
              title: const Text('Enable dark theme'),
            ),
          ],
        ),
      ],
    );
  }
}
