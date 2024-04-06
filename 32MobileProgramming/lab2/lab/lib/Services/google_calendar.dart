import 'package:googleapis/calendar/v3.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Services/firebase_auth.dart';

class GoogleCalendar {
  static Future<List<Note>> load() async {
    await Auth.signInWithGoogle();
    final httpClient = HttpClient();

    final events = await CalendarApi(httpClient).events.list("primary");

    if (events.items == null) {
      return [];
    }

    List<Note> notes = events.items!.map((event) {
      return Note(
        googleId: event.id,
        title: event.summary ?? "",
        content: event.description ?? "",
        lastEdited: event.updated ?? DateTime.now(),
        alarm: event.start?.dateTime,
      );
    }).toList();

    return notes;
  }
}
