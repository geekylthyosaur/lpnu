import 'package:flutter/material.dart';

class Calendar extends StatefulWidget {
  final int len;

  const Calendar({super.key, required this.len});

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
        child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: List.generate(
                7,
                (idx) => Column(children: [
                      _dayCell(days[idx]),
                      const SizedBox(height: 8),
                      ...getNextWeekdays(
                              getCurrentWeekDates()[idx], idx + 1, len)
                          .map((date) => Column(children: [
                                _dateCell(date),
                                const SizedBox(height: 8)
                              ]))
                    ]))));
  }

  Widget _dayCell(String day) {
    return Text(day);
  }

  Widget _dateCell(DateTime date) {
    return Container(
      padding: const EdgeInsets.symmetric(vertical: 8, horizontal: 8),
      width: 40,
      decoration: BoxDecoration(
        color: DateTime.now().day == date.day &&
                DateTime.now().month == date.month &&
                DateTime.now().year == date.year
            ? Theme.of(context).colorScheme.inversePrimary
            : Theme.of(context).colorScheme.primaryContainer,
        borderRadius: BorderRadius.circular(10),
      ),
      child: Text(
        date.day.toString(),
        style:
            TextStyle(color: Theme.of(context).colorScheme.onPrimaryContainer),
        textAlign: TextAlign.center,
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
