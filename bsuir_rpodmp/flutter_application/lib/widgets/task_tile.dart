import 'package:flutter/material.dart';

import '../models/task_model.dart';

class TaskTile extends StatefulWidget {
  final int index;
  final Task task;
  final Function(int) onDelete;
  final Function(Task) onChange;

  const TaskTile({
    required this.index,
    required this.task,
    required this.onDelete,
    required this.onChange,
  });

  @override
  _TaskTileState createState() => _TaskTileState();
}

class _TaskTileState extends State<TaskTile> {
  @override
  Widget build(BuildContext context) {
    return ListTile(
      title: Row(
        children: <Widget>[
          Checkbox(
            value: widget.task.isCompleted,
            onChanged: (value) {
              setState(() {
                widget.onChange(widget.task);
              });
            },
          ),
          Expanded(child: Text(widget.task.title)),
          IconButton(
            iconSize: 30,
            icon: const Icon(
              Icons.delete,
              color: Colors.red,
            ),
            alignment: Alignment.centerRight,
            onPressed: () {
              widget.onDelete(widget.index);
            },
          ),
        ],
      ),
    );
  }
}
