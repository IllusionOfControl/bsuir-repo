import 'package:flutter/material.dart';
import 'package:flutter_app_7/screens/note_create_screen.dart';
import 'package:flutter_bloc/flutter_bloc.dart';

import './screens/note_list_screen.dart';
import 'bloc/note_bloc.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MultiBlocProvider(
      providers: [
        BlocProvider(
          create: (context) => NoteBloc(),
          child: NoteListScreen(),
        ),
        BlocProvider(
          create: (context) => NoteBloc(),
          child: CreateNoteScreen(),
        ),
      ],
      child: MaterialApp(home: NoteListScreen()),
    );
  }
}
