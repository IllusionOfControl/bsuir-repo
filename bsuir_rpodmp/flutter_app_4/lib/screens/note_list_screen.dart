import 'package:flutter/material.dart';

import '../models/note.dart';
import '../screens/note_create_screen.dart';
import '../screens/note_detail_screen.dart';

class NoteListScreen extends StatefulWidget {
  @override
  _NoteListScreen createState() => _NoteListScreen();
}

class _NoteListScreen extends State<NoteListScreen> {
  final List<Note> notes = [
    Note(
      title: 'Note 1',
      content: 'Content of Note 1',
      date: DateTime.now(),
    ),
  ];

  void _handleNoteCreate(
      String newNoteTitle, String newNoteContent, DateTime newNoteDate) {
    setState(() {
      notes.add(Note(
          title: newNoteTitle, content: newNoteContent, date: newNoteDate));
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Note List'),
      ),
      body: ListView.builder(
        itemCount: notes.length,
        itemBuilder: (context, index) {
          return ListTile(
            title: Text(notes[index].title),
            subtitle: Text(
              'Last edited: ${notes[index].date.toString()}',
            ),
            onTap: () {
              Navigator.push(
                context,
                MaterialPageRoute(
                  builder: (context) => NoteDetailScreen(note: notes[index]),
                ),
              );
            },
          );
        },
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.push(
              context,
              MaterialPageRoute(
                  builder: (context) => CreateNoteScreen(_handleNoteCreate)));
        },
        child: const Icon(Icons.add),
      ),
    );
  }
}
