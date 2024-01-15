part of 'note_bloc.dart';

abstract class NoteState {
  const NoteState();
}

class NotesLoaded extends NoteState {
  final List<Note> notes;

  NotesLoaded({required this.notes});

  @override
  List<Object> get props => [notes];
}
