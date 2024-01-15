import 'dart:math';

import 'package:flutter_app_2/mixins.dart';

class Square extends Shape {
  double side;

  Square(this.side);

  // Именнованный конструктор и полями
  Square.fromWidthAndHeight({required double width, required double height})
      : side = width == height
            ? width
            : throw ArgumentError('Width and height must be equal');

  // Getter для стороны
  double get getSide => side;

  // Setter для стороны
  set setSide(double newSide) {
    if (newSide > 0) {
      side = newSide;
    } else {
      throw ArgumentError('Side must be greater than 0');
    }
  }

  @override
  double calculateArea() {
    if (side == 0) throw IntegerDivisionByZeroException();
    return side * side;
  }

  @override
  double calculatePerimeter() {
    return side * 4;
  }
}

class Rectangle extends Shape {
  double height;
  double width;

  Rectangle(this.height, this.width);

  // Getter для высоты
  double get getWidth => width;

  // Getter для ширины
  double get getHeight => height;

  // Setter для высоты
  set setWidth(double newWidth) {
    if (newWidth > 0) {
      width = newWidth;
    } else {
      throw ArgumentError('Width must be greater than 0');
    }
  }

  // Setter для ширины
  set setHeight(double newHeight) {
    if (newHeight > 0) {
      height = newHeight;
    } else {
      throw ArgumentError('Height must be greater than 0');
    }
  }

  @override
  double calculateArea() {
    return height * width;
  }

  @override
  double calculatePerimeter() {
    return height * 2 + width * 2;
  }
}

class Circle extends Shape {
  double radius;

  Circle(this.radius);

  @override
  double calculateArea() {
    return pi * radius * radius;
  }

  @override
  double calculatePerimeter() {
    return 2 * pi * radius;
  }
}

class Cube extends Shape3D {
  double side;

  Cube(this.side);

  @override
  double calculateVolume() {
    return side * side * side;
  }

  @override
  double calculateArea() {
    return 6 * side * side;
  }

  @override
  double calculatePerimeter() {
    return 12 * side;
  }
}

class Sphere extends Shape3D {
  double radius;

  Sphere(this.radius);

  @override
  double calculateVolume() {
    return (4 / 3) * pi * pow(radius, 3);
  }

  // Статическое поле
  static const double piValue = 3.14159;

  // Статическая функция
  static double calculateDiameter(double radius) {
    return 2 * radius;
  }


  @override
  double calculateArea() {
    return 4 * pi * pow(radius, 2);
  }

  @override
  double calculatePerimeter() {
    throw UnsupportedError('Perimeter is not applicable for a sphere.');
  }
}
