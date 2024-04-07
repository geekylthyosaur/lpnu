import 'package:flutter/material.dart';

void snackBar(BuildContext context, String msg, {int durationSec = 1}) {
  ScaffoldMessenger.of(context).showSnackBar(
    SnackBar(
      content: Text(msg),
      duration: Duration(seconds: durationSec),
    ),
  );
}
