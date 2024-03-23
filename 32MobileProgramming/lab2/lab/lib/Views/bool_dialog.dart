import 'package:flutter/material.dart';

Future<bool> boolDialog(BuildContext context, String title, String content,
    String yes, String no) async {
  final result = await showDialog<bool>(
    context: context,
    builder: (context) {
      return AlertDialog(
        title: Text(title),
        content: Text(content),
        actions: <Widget>[
          TextButton(
            child: Text(no),
            onPressed: () => Navigator.of(context).pop(false),
          ),
          ElevatedButton(
            child: Text(yes),
            onPressed: () => Navigator.of(context).pop(true),
          ),
        ],
      );
    },
  );

  return result ?? false;
}
