abstract class PerimeterCalculation {
  double calculatePerimeter();
}

abstract class AreaCalculation {
  double calculateArea();
}

abstract class Shape implements PerimeterCalculation, AreaCalculation {
}

abstract class Shape3D implements Shape {
  double calculateVolume();

  // Function with named parameters
  void translate({double dx = 0.0, double dy = 0.0, double dz = 0.0}) {
    print("Implementation for translating in 3D space");
  }

  // Function with optional parameters
  void rotate(double angle, [double axisX = 0.0, double axisY = 0.0, double axisZ = 1.0]) {
    print("// Implementation for rotating in 3D space");
  }

  // Function with required parameters
  void scale(double scaleX, double scaleY, double scaleZ) {
    print("// Implementation for scaling in 3D space");
  }
}


mixin PrintDetailsMixin implements PerimeterCalculation, AreaCalculation {
  void printArea() {
    print('Area: ${calculateArea()}');
  }

  void printPerimeter() {
    print('Perimeter: ${calculatePerimeter()}');
  }
}