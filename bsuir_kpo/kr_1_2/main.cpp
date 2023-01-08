#include <iostream>
#include <math.h>
#include <string>

#define PI 3.1415926
#define TO_RADIANS(x) x * PI / 180.0f
#define TO_DEGREES(x) x * 180.0f / PI 


class Parallelogram {
private:
	float _sideA;
	float _sideB;
	float _bigDiagonal;
public:
	Parallelogram(float sideA, float sideB, float diagonal) 
		: _sideA(sideA), _sideB(sideB), _bigDiagonal(diagonal) {}

	void IncreaseSides(float multA, float multB) {
		float betaAngle = CalculateBetaAngle();
		_sideA *= multA;
		_sideB *= multB;
		_bigDiagonal = sqrtf(powf(_sideA, 2) + powf(_sideB, 2) - 2.0f * cosf(betaAngle) * _sideA * _sideB);
	}

	float CalculateSideA() {
		return _sideA;
	}

	float CalculateSideB() {
		return _sideB;
	}

	float CalculateBigDiagonal() {
		return _bigDiagonal;
	}

	float CalculateAlphaAngle() {
		return 180.0f - CalculateBetaAngle();
	}

	float CalculateBetaAngle() {
		return acosf(TO_RADIANS((powf(_sideA, 2) + powf(_sideB, 2) - powf(_bigDiagonal, 2)) / (2 * _sideA * _sideB)));
	}

	float CalculateGammaAngle() {
		return 180.0f - CalculateAlphaAngle() / 2.0f - CalculateBetaAngle() / 2.0f;
	}

	float CalculateSmallDiagonal() {
		return sqrtf(2.0f * powf(_sideA, 2) + 2.0f * powf(_sideB, 2) - powf(_bigDiagonal, 2));
	}

	float CalculatePerimeter() {
		return 2 * _sideA + 2 *_sideB;
	}

	float CalculateHeight() {
		return CalculateSquare() / _sideB;
	}

	float CalculateSquare() {
		return _sideA * _sideB * sinf(CalculateBetaAngle());
	}

	std::string ToString() {
		return "Parallelogram [" + std::to_string(_sideA) + " x " + std::to_string(_sideB) + " x "+ std::to_string(_bigDiagonal) +"]";
	}
};


// 10 x 18 x 21

int main() {
	float side_a, side_b, side_diagonal;
	std::cout << "Enter side_a" << std::endl;
	std::cin >> side_a;

	std::cout << "Enter side_b" << std::endl;
	std::cin >> side_b;

	std::cout << "Enter diagoanl" << std::endl;
	std::cin >> side_diagonal;

	Parallelogram t = Parallelogram(side_a, side_b, side_diagonal);

	std::cout << "Calculate side A:" << std::endl;
	std::cout << t.CalculateSideA() << std::endl;

	std::cout << "Calculate side B:" << std::endl;
	std::cout << t.CalculateSideB() << std::endl;

	std::cout << "Calculate big diagonal:" << std::endl;
	std::cout << t.CalculateBigDiagonal() << std::endl;

	std::cout << "Calculate side small diagonal:" << std::endl;
	std::cout << t.CalculateSmallDiagonal() << std::endl;

	std::cout << "Calculate perimeter:" << std::endl;
	std::cout << t.CalculatePerimeter() << std::endl;

	std::cout << "Calculate square:" << std::endl;
	std::cout << t.CalculateSquare() << std::endl;

	std::cout << "Calculate height:" << std::endl;
	std::cout << t.CalculateHeight() << std::endl;

	std::cout << "To string:" << std::endl;
	std::cout << t.ToString() << std::endl;

	t.IncreaseSides(2.0f, 2.0f);

	std::cout << "To string:" << std::endl;
	std::cout << t.ToString() << std::endl;
}