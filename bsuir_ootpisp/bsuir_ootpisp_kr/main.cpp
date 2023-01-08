#include <math.h>
#include <iostream>

using namespace std;


class Location {
public:
	double x, y;

	Location() : x(0), y(0) { }
	// Копирующий конструктор
	Location(const Location& obj) : x(obj.x), y(obj.y) { }
	// Параметрический конструктор
	Location(double xx, double yy) : x(xx), y(yy) { }
};
// Класс реализует ограничивающую область на плоскости
class Clip {
public:
	Location min;
	// Левая нижняя граница
	Location max;
	// Правая верхняя граница
	// Дефолтный конструктор
	Clip() : min(), max() { }
	// Копирующий конструктор
	Clip(const Clip& obj) : min(obj.min), max(obj.max) { }
	// Параметрический конструктор
	Clip(double xn, double yn, double xk, double yk) {
		if (xn < xk) { min.x = xn; max.x = xk; }
		else { min.x = xk; max.x = xn; }
		if (yn < yk) { min.y = yn; max.y = yk; }
		else { min.y = yk; max.y = yn; }
	}
		// Вычисление ширины области
	double sizeX() const { return (max.x - min.x); }
	// Вычисление высоты области
	double sizeY() const { return (max.y - min.y); }
};
/* Класс реализует геометрические константы и функции проверки
(базовый статический класс для всех примитивов)
*/
class Geometry {
public:
	static const double pi;
	// число рі
	static const double pi2;
	// число рі
	static const double extent; // предельный размер
	// Проверка и корректировка значения координаты
	static double accurateExtent(double value)
	{
		return ((value < -extent) ? -extent : (value > extent) ? extent : value);
	}
};


const double Geometry::pi = 3.14159265358979323846;
const double Geometry::pi2 = 6.28318530717958647693;
const double Geometry::extent = 1E6;
// число рі
// число pi*2
// предельный размер
/* Реализует гесметрический примитив на плоскости
(родитель для точки и базовый для фигуры) */
class Primitive : public Geometry {
private:
	bool visible;
	// Видимость
	unsigned char color;
	// Цвет (0…255)
public:
	// Получение цвета примитива
	int getColor() const { return int(color); }
	// Установка цвета примитива
	void setColor(int tint)
	{
		color = unsigned char((tint < 0) ? 0 : (tint > 255) ? 255 : tint);
	}
	// Проверка видимости примитива
	bool isVisible() const { return visible; }
	// Отображение примитива (видим)
	void setShow() { visible = true; }
	// Скрытие примитива (невидим)
	void setHide() { visible = false; }
	// Дефолтный конструктор
	Primitive() : visible(false), color(0) { }
	// Копирующий конструктор
	Primitive(const Primitive& obj) : visible(obj.visible), color(obj.color) {}
};
// Класс реализует цветну точку на плоскости (родитель для фигуры)
class Point : public Primitive, public Location {
public:
	// Дефолтный конструктор
	Point() : Primitive(), Location() { }
	// Копирующий конструктор
	Point(const Point& obj) : Primitive (obj), Location (obj) { }
	// Параметрический конструктор
	Point(double xx, double yy, int tint) {
		setX(xx);
		setShow();
		setY(yy);
		setColor(tint);
	}

	// Получение X-координаты
	double getX() const { return x; }
	// Получение Y-координаты
	double getY() const { return y; }
	// Получение позиции
	Location getPosition() const { return Location(x, y); }
	// Установка Х-координаты
	virtual void setX(double xx) { x = accurateExtent(xx); }
	// Установка Y-координаты
	virtual void setY(double yy) { y = accurateExtent(yy); }
	// Вычисление ограничивающей области
	virtual Clip getClipBox() const { return Clip(x, y, x, y); }
	};
		/// Класс реализует фигуру "окружность" (наследник для точки)
class Figure : public Point {
private:
	double radius;
	double alpha;
	// Радиус (центр в родителе)
public:
	// Дефолтный конструктор
	Figure() : Point(), radius(0) { }
	// Копирующий конструктор
	Figure(const Figure& obj) : Point(obj), radius(obj.radius) { }
	// Параметрический конструктор
	Figure(double xc, double yc, double rd, int tint) {
		setColor(tint);
		setShow();
		setRadius(rd);
		// Установка общих свойств
		// Установка своих свойств
		setX(xc);
		setY(yc);
	}
	// Установка свойств родителя
	// Получение радиуса
	double getRadius() const {
		return radius;
	}

	// Установка свойств родителя
	// Получение угла сегмента
	double getAlpha() const {
		return alpha;
	}

	// Установка радиуса
	void setRadius(double r) {
		// Вычисление периметра
		// Вычисление площади
		radius = ((r < 0) ? -r : r);
	}

	void setAlpha(double a) {
		// Вычисление периметра
		// Вычисление площади
		alpha = ((a < 0) ? -a : a);
	}

	double getHordeLength() const {
		
		double rad = (pi * alpha) / 180.0;
		return (2 * radius * sin(rad / 2.0));
	}

	// TODO
	double getLength() const { 
		double rad = (pi * alpha) / 180.0;
		return getHordeLength() + radius * rad;
	}

	// TODO
	double getSquare() const { 
		double rad = (pi * alpha) / 180.0;
		return 0.5 * radius * radius * (rad - sin(rad)); 
	}

	// Установка Х-координаты центра (перегрузка)
	virtual void setX(double xx)
	{
		x = (((xx - radius) < -extent) ? (-extent + radius) :
			((xx + radius) > +extent) ? (+extent - radius) : xx);
	}

	// Установка Y-координаты центра (перегрузка)
	virtual void setY(double yy)
	{
		y = (((yy - radius) < -extent) ? (-extent + radius) :
			((yy + radius) > +extent) ? (+extent - radius) : yy);
	};

	// Вычисление ограничивающей области (перегрузка)
	virtual Clip getClipBox() const
	{
		return Clip(x - radius, y - radius, x + radius, y + radius);
	}
};


/* Реализует отображение ошибки
*/
void ErrorValue() {
	std::cin.clear();
	std::cin.sync();
	std::cout << "Ошибка: некорректное значение" << endl;
}


/* Реализует консольный интерфейс для изменения свойств фигуры*/
void ModifyFigure(Figure& Fig) {
	char ch = 'P';
	// Команда меню
	do {
		double value;
		// Обработка команд меню
		switch (ch) {
		case 'P':
		case 'p':
			// Печать всех свойств фигуры
			std::cout << std::endl << "Свойства фигуры:"
				<< std::endl << "Центр = (" << Fig.getX() << ";" << Fig.getY() << ")"
				<< std::endl << "Радиус = " << Fig.getRadius()
				<< std::endl << "Длинна хорды = " << Fig.getHordeLength()
				<< std::endl << "Угол = " << Fig.getAlpha()
				<< std::endl << "Площадь = " << Fig.getSquare()
				<< std::endl << "Периметр = " << Fig.getLength()
				<< std::endl << "Видимость = " << ((Fig.isVisible()) ? "On" : "Off")
				<< std::endl << "Номер цвета = " << Fig.getColor() << std::endl;
			{
				Clip area = Fig.getClipBox();
				std::cout << "Область = (" << area.min.x << ";" << area.min.y
					<< ") - (" << area.max.x << ";" << area.max.y << ")" << std::endl
					<< "Размер = [" << area.sizeX() << "x" << area.sizeY() << "]"
					<< std::endl;
			}
			break;
		case 'X':
		case 'x':
			//Установка Х - координаты(свойство родителя)
			std::cout << std::endl << "Введите X-координату:>";
			std::cin >> value;
			if (!std::cin.fail()) Fig.setX(value);
			else ErrorValue();
			break;
		case 'Y':
		case 'y':
			// Установка Y-координаты (свойство родителя)
			std::cout << std::endl << "Введите Y-координату:>";
			std::cin >> value;
			if (!std::cin.fail()) Fig.setY(value);
			else ErrorValue();
			break;
			// Установка радиуса (свое свойство)
		case 'R':
		case 'r':
			std::cout << std::endl << "Введите радиус [R > 0]:>";
			std::cin >> value;
			if (!std::cin.fail()) Fig.setRadius(value);
			else ErrorValue();
			break;
		case 'A':
		case 'a':
			std::cout << std::endl << "Введите угол alpha [a > 0]:>";
			std::cin >> value;
			if (!std::cin.fail()) Fig.setAlpha(value);
			else ErrorValue();
			break;
		case 'T':
		case 't':
			// Установка цвета (базовое свойство)
			int tint;
			std::cout << std::endl << "Введите цвет [0…255]:>";
			std::cin >> tint;
			if (!std::cin.fail()) Fig.setColor(tint);
			else ErrorValue();
			break;

		case 'V':
			// Переключение видимости (базовое свойство)
		case 'v':
			cout << endl << "Видимость [N-on|F-off]:>";
			cin >> ch;
			if (ch = 'N' || ch == 'n') Fig.setShow();
			else if (ch = 'F' || ch == 'f') Fig.setHide();
			else ErrorValue();
			break;
		default: cout << "Ошибка: некорректная операция" << endl;
		}
		// Отображение консольного меню
		cout << endl << " (T) Изменить цвет"
			<< endl << " (R) Изменить радиус"
			<< endl << " (V) Изменить видимость"
			<< endl << " (X) Изменить Х-координату"
			<< endl << " (Y) Изменить Y-координату"
			<< endl << " (A) Изменить угол alpha"
			<< endl << " (P) Печатать все свойства"
			<< endl << " (Q) Выход";
		cout << endl << "Выберите пункт:>";
		cin >> ch;
	} while (ch != 'Q' && ch != 'q');
}
// Главная функция
void main() {
	// Переключить вывод сообщений на русском языке
	setlocale(LC_ALL, "Russian");
	cout << "Работа 3";
	auto* figure = new Figure(1, 1, 1, 255);
	ModifyFigure(*figure);
}