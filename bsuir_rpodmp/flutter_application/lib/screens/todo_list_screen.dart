import 'dart:io';
import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:path_provider/path_provider.dart';

import '../models/task_model.dart';
import '../widgets/task_tile.dart';

class TodoListScreen extends StatefulWidget {
  const TodoListScreen({super.key});

  @override
  _TodoListScreenState createState() => _TodoListScreenState();
}

class _TodoListScreenState extends State<TodoListScreen> {
  List<Task> tasks = [];

  void _handleTaskChange(Task task) {
    setState(() {
      task.isCompleted = !task.isCompleted;
    });
  }

  void _handleTaskDelete(int index) {
    setState(() {
      tasks.removeAt(index);
      saveTasks();
    });
  }

  void _handleTaskCreate(String newTaskTitle) {
    setState(() {
      tasks.add(Task(title: newTaskTitle));
      saveTasks();
    });
  }

  Future<void> loadTasks() async {
    try {
      final file = await getLocalFile();
      if (file.existsSync()) {
        final String contents = await file.readAsString();
        final List<dynamic> data = json.decode(contents);
        setState(() {
          tasks = data.map((taskData) => Task.fromJson(taskData)).toList();
        });
      }
    } catch (e) {
      print("Error loading tasks: $e");
    }
  }

  Future<void> saveTasks() async {
    try {
      final file = await getLocalFile();
      final List<Map<String, dynamic>> data =
          tasks.map((task) => task.toJson()).toList();
      await file.writeAsString(json.encode(data));
    } catch (e) {
      print("Error saving tasks: $e");
    }
  }

  Future<File> getLocalFile() async {
    final directory = await getApplicationDocumentsDirectory();
    return File('${directory.path}/tasks.json');
  }

  @override
  void initState() {
    super.initState();
    loadTasks();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Todo List'),
      ),
      body: tasks.isEmpty
          ? const Center(
              child: Text('List is empty'),
            )
          : ListView.builder(
              itemCount: tasks.length,
              itemBuilder: (context, index) {
                return TaskTile(
                  index: index,
                  task: tasks[index],
                  onDelete: _handleTaskDelete,
                  onChange: _handleTaskChange,
                );
              },
            ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          showDialog(
            context: context,
            builder: (BuildContext context) {
              String newTaskTitle = '';

              return AlertDialog(
                title: const Text('Add Task'),
                content: TextField(
                  onChanged: (value) {
                    newTaskTitle = value;
                  },
                ),
                actions: [
                  ElevatedButton(
                    onPressed: () {
                      _handleTaskCreate(newTaskTitle);
                      Navigator.pop(context);
                    },
                    child: const Text('Add'),
                  ),
                ],
              );
            },
          );
        },
        child: const Icon(Icons.add),
      ),
    );
  }
}
