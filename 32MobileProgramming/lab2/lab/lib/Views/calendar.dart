import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'package:lab/Models/note.dart';
import 'package:lab/Views/upcoming_notes_list.dart';

class Calendar extends StatefulWidget {
  final int len;
  final List<Note> notes;

  const Calendar({super.key, required this.notes, required this.len});

  @override
  State<Calendar> createState() => _CalendarState();
}

class _CalendarState extends State<Calendar> {
  @override
  Widget build(BuildContext context) {
    return _calendar(widget.len);
  }

  Widget _calendar(int len) {
    final days = ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun'];

    return Padding(
        padding: const EdgeInsets.symmetric(vertical: 8),
        child: Column(children: [
          if (len == 5)
            Center(
                child: Text(
              DateFormat('dd MMMM, yyyy').format(DateTime.now()),
              style: const TextStyle(fontSize: 32, fontWeight: FontWeight.bold),
            )),
          const SizedBox(height: 8),
          Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: List.generate(
                  7,
                  (idx) => Column(children: [
                        _dayCell(days[idx]),
                        const SizedBox(height: 8),
                        ...getNextWeekdays(
                                getCurrentWeekDates()[idx], idx + 1, len)
                            .map((date) => Column(children: [
                                  _dateCell(date, widget.notes),
                                  const SizedBox(height: 8)
                                ]))
                      ]))),
          if (len == 5) UpcomingNotesList(notes: widget.notes),
        ]));
  }

  Widget _dayCell(String day) {
    return Text(day);
  }

  Widget _dateCell(DateTime date, List<Note> notes) {
    List<Note> todayNotes = notes.where((note) {
      return note.alarm != null &&
          note.alarm!.day == date.day &&
          note.alarm!.month == date.month &&
          note.alarm!.year == date.year;
    }).toList();

    todayNotes =
        todayNotes.sublist(0, todayNotes.length > 2 ? 2 : todayNotes.length);

    List<Widget> indicators = todayNotes.map((note) {
      return Container(
        width: 8,
        height: 8,
        margin: const EdgeInsets.only(right: 4, left: 4),
        decoration: BoxDecoration(
          color: note.colorScheme.primary,
          shape: BoxShape.circle,
        ),
      );
    }).toList();

    return Container(
      height: 50,
      width: 50,
      padding: const EdgeInsets.symmetric(vertical: 8, horizontal: 8),
      decoration: BoxDecoration(
        color: DateTime.now().day == date.day &&
                DateTime.now().month == date.month &&
                DateTime.now().year == date.year
            ? Theme.of(context).colorScheme.inversePrimary
            : Theme.of(context).colorScheme.primaryContainer,
        borderRadius: BorderRadius.circular(10),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.center,
        children: [
          Text(
            date.day.toString(),
            style: TextStyle(
              color: Theme.of(context).colorScheme.onPrimaryContainer,
            ),
            textAlign: TextAlign.center,
          ),
          SizedBox(height: 4),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: indicators,
          ),
        ],
      ),
    );
  }
}

List<DateTime> getNextWeekdays(DateTime startDate, int weekday, int len) {
  List<DateTime> weekdays = [];
  DateTime date = startDate;
  while (weekdays.length < len) {
    if (date.weekday == weekday) {
      weekdays.add(date);
      date = date.add(const Duration(days: 7));
    } else {
      date = date.add(const Duration(days: 1));
    }
  }
  return weekdays;
}

List<DateTime> getCurrentWeekDates() {
  final now = DateTime.now();
  final currentWeekday = now.weekday;
  final startOfWeek = now.subtract(Duration(days: currentWeekday - 1));
  return List.generate(7, (index) => startOfWeek.add(Duration(days: index)));
}
