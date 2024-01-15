import 'package:uuid/uuid.dart';

class Note {
  final String id;
  final String title;
  final String content;
  final DateTime date;

  Note({
    required this.title,
    required this.content,
    required this.date,
  }) : id = Uuid().v4();
}
