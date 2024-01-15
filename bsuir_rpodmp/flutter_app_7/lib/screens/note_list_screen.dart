import 'package:flutter/material.dart';
import 'package:flutter_bloc/flutter_bloc.dart';

import '../bloc/note_bloc.dart';
import '../models/note.dart';
import '../screens/note_create_screen.dart';
import '../screens/note_detail_screen.dart';

class NoteListScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    final NoteBloc noteBloc = BlocProvider.of<NoteBloc>(context);

    return Scaffold(
        appBar: AppBar(
          title: const Text('Note List'),
        ),
        body: BlocBuilder<NoteBloc, NoteState>(
          builder: (context, state) {
            if (state is NotesLoaded) {
              return ListView.builder(
                itemCount: state.notes.length,
                itemBuilder: (context, index) {
                  return ListTile(
                    title: Text(state.notes[index].title),
                    subtitle: Text(
                      'Last edited: ${state.notes[index].date.toString()}',
                    ),
                    onTap: () {
                      Navigator.of(context).push(
                        MaterialPageRoute(
                          builder: (context) =>
                              NoteDetailScreen(note: state.notes[index]),
                        ),
                      );
                    },
                  );
                },
              );
            } else {
              return const Center(child: CircularProgressIndicator());
            }
          },
        ),
        //
        floatingActionButton: FloatingActionButton(
          onPressed: () {
            // final newNote = Note(
            //   title: 'test',
            //   content: 'test',
            //   date: DateTime.now(),
            // );
            // BlocProvider.of<NoteBloc>(context).add(AddNoteEvent(note: newNote));
            // print("add note");
            noteBloc.add(OpenAddNoteUiEvent(context));
            // Navigator.of(context).push(
            //     MaterialPageRoute(builder: (context) => CreateNoteScreen()));
          },
          child: const Icon(Icons.add),
        ),
      );
  }
}
