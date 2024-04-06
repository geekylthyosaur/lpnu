import 'package:googleapis/calendar/v3.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Services/firebase_auth.dart';

class GoogleCalendar {
  static Future<dynamic> load() async {
    await Auth.signInWithGoogle();
    final httpClient = HttpClient();

    final events = await CalendarApi(httpClient).events.list("primary");

    List<Note> notes = [];
    events.items?.forEach((event) {
      Note note = Note(
        title: event.summary ?? "",
        content: event.description ?? "",
        lastEdited: event.updated ?? DateTime.now(),
      );
      notes.add(note);
    });

    return notes;
  }
}
