import 'dart:async';
import 'package:bloc/bloc.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_app_7/screens/note_create_screen.dart';
import '../models/note.dart';

part 'note_event.dart';
part 'note_state.dart';

class NoteBloc extends Bloc<NoteEvent, NoteState> {
  List<Note> notes = [];

  NoteBloc() : super(NotesLoaded(notes: [])) {
    on<AddNoteEvent>(_addEventHandler);
    on<OpenAddNoteUiEvent>(_openAddEventHandler);
  }

  Future<void> _addEventHandler(AddNoteEvent e, Emitter emit) async {
    notes.add(e.note);
    emit(NotesLoaded(notes: notes));
  }
  Future<void> _openAddEventHandler(OpenAddNoteUiEvent e, Emitter emit) async {
    Navigator.push(
        e.context, MaterialPageRoute(builder: (context) => CreateNoteScreen()));
  }
}
