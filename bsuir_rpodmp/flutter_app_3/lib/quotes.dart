import 'dart:convert';
import 'package:http/http.dart' as http;

class Quote {
  final String content;
  final String author;

  Quote({required this.content, required this.author});

  factory Quote.fromJson(Map<String?, dynamic> json) {
    return Quote(
      content: json['content'],
      author: json['author'],
    );
  }
}

class QuoteService {
  static const String apiUrl = 'https://api.quotable.io/random';

  Future<Quote> fetchQuote() async {
    try {
      final response = await http.get(Uri.parse(apiUrl));

      if (response.statusCode == 200) {
        final Map<String?, dynamic> data = json.decode(response.body);
        return Quote.fromJson(data);
      } else {
        throw Exception('Failed to load quote');
      }
    } catch (e) {
      throw Exception('Error: $e');
    }
  }
}
