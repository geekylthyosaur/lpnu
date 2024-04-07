import 'package:flutter/material.dart';

class PrivacyPage extends StatefulWidget {
  const PrivacyPage({super.key});

  @override
  State<PrivacyPage> createState() => _PrivacyPageState();
}

class _PrivacyPageState extends State<PrivacyPage> {
  final GlobalKey<ScaffoldState> scaffoldKey = GlobalKey<ScaffoldState>();

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
    );
  }

  Widget _body() {
    return const Padding(
        padding: EdgeInsets.all(40),
        child: Center(
          child: Text(
              """Lab App is committed to respecting and protecting your data and privacy. We will never compromise on that commitment.

        Information from your device that is collected is done so routinely as part of the Firebase and Firebase Analytics development platform. This data does not contain information that can directly identify you, but it does contain information unique to your device such as your regional location or device id. Specific device location or location history is not collected. For more information on these services refer to the privacy policies below.

        This information will never be sold or shared publicly but is only used in the Firebase development console to track how the app is being used for the sole purpose of understanding and improving the service.

        For more information, contact developers of Lab."""),
        ));
  }
}
