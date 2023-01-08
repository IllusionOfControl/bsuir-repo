#include <iostream>
#include <math.h>
#include <string>

class Triangle {
private:
	float _side_a;
	float _side_b;

public:
	Triangle(float side_a, float side_b) : _side_a(side_a), _side_b(side_b) {}

	void IncreaseSideA(float percent) {
		_side_a = _side_a * percent + _side_a;
	}

	void IncreaseSideB(float percent) {
		_side_b = _side_b * percent + _side_b;
	}

	float GetSideA() {
		return _side_a;
	}

	float GetSideB() {
		return _side_b;
	}

	float CalculateHalfMeter() {
		return _side_a + _side_b + CalculateHypotenuse();
	}

	float CalculateRadius() {
		return CalculateHypotenuse() / 2;
	}

	float CalculateHypotenuse() {
		return hypotf(_side_a, _side_b);
	}

	std::string ToString() {
		return "Triangle [" + std::to_string(_side_a) + " x " + std::to_string(_side_b) + "]";
	}
};


int main() {
	float side_a, side_b;
	std::cout << "Enter side_a" << std::endl;
	std::cin >> side_a;

	std::cout << "Enter side_b" << std::endl;
	std::cin >> side_b;

	Triangle t = Triangle(side_a, side_b);

	std::cout << "Calculate radius:" << std::endl;
	std::cout << t.CalculateRadius() << std::endl;

	std::cout << "Calculate half-meter:" << std::endl;
	std::cout << t.CalculateHalfMeter() << std::endl;

	std::cout << "To string:" << std::endl;
	std::cout << t.ToString() << std::endl;

	std::cout << "Increase sides by 20%:" << std::endl;
	t.IncreaseSideA(0.2);
	t.IncreaseSideB(0.2);

	std::cout << "To string:" << std::endl;
	std::cout << t.ToString() << std::endl;
}