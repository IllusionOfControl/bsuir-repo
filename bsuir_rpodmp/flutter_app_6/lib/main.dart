import 'package:flutter/material.dart';
import 'package:flutter_app_6/quotes.dart';
import 'package:flutter_app_6/storage.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: QuoteListScreen(),
    );
  }
}

class QuoteListScreen extends StatefulWidget {
  @override
  _QuoteListScreenState createState() => _QuoteListScreenState();
}

class _QuoteListScreenState extends State<QuoteListScreen> {
  List<Quote> quotes = [];

  void _addNewQuote() async {
    setState(() {
      final quoteService = QuoteService();
      quoteService.fetchQuote().then((newQuote) {
        quotes.add(newQuote);
        QuoteLocalStorageSharedPreferences.saveQuote(newQuote);
        QuoteLocalStorageFileSystem.saveQuote(newQuote);
        QuoteLocalStorageSQLite.saveQuote(newQuote);
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Quote List'),
      ),
      body: ListView.builder(
        itemCount: quotes.length,
        itemBuilder: (context, index) {
          return ListTile(
            title: Text(quotes[index].content),
            subtitle: Text(quotes[index].author),
          );
        },
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          _addNewQuote();
        },
        child: Icon(Icons.add),
      ),
    );
  }
}