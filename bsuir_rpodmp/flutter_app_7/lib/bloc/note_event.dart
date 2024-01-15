part of 'note_bloc.dart';

abstract class NoteEvent {
  const NoteEvent();
}

class AddNoteEvent extends NoteEvent {
  final Note note;

  AddNoteEvent({required this.note});

  @override
  List<Object> get props => [note];
}

class UpdateEvent extends NoteEvent {
  final Note note;

  UpdateEvent({required this.note});

  @override
  List<Object> get props => [note];
}

class DeleteEvent extends NoteEvent {
  final Note note;

  DeleteEvent({required this.note});

  @override
  List<Object> get props => [note];
}

class OpenAddNoteUiEvent extends NoteEvent {
  BuildContext context;
  OpenAddNoteUiEvent(this.context);
}
