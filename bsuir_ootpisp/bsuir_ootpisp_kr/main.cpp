#include <math.h>
#include <iostream>

using namespace std;


class Location {
public:
	double x, y;

	Location() : x(0), y(0) { }
	// ���������� �����������
	Location(const Location& obj) : x(obj.x), y(obj.y) { }
	// ��������������� �����������
	Location(double xx, double yy) : x(xx), y(yy) { }
};
// ����� ��������� �������������� ������� �� ���������
class Clip {
public:
	Location min;
	// ����� ������ �������
	Location max;
	// ������ ������� �������
	// ��������� �����������
	Clip() : min(), max() { }
	// ���������� �����������
	Clip(const Clip& obj) : min(obj.min), max(obj.max) { }
	// ��������������� �����������
	Clip(double xn, double yn, double xk, double yk) {
		if (xn < xk) { min.x = xn; max.x = xk; }
		else { min.x = xk; max.x = xn; }
		if (yn < yk) { min.y = yn; max.y = yk; }
		else { min.y = yk; max.y = yn; }
	}
		// ���������� ������ �������
	double sizeX() const { return (max.x - min.x); }
	// ���������� ������ �������
	double sizeY() const { return (max.y - min.y); }
};
/* ����� ��������� �������������� ��������� � ������� ��������
(������� ����������� ����� ��� ���� ����������)
*/
class Geometry {
public:
	static const double pi;
	// ����� �
	static const double pi2;
	// ����� �
	static const double extent; // ���������� ������
	// �������� � ������������� �������� ����������
	static double accurateExtent(double value)
	{
		return ((value < -extent) ? -extent : (value > extent) ? extent : value);
	}
};


const double Geometry::pi = 3.14159265358979323846;
const double Geometry::pi2 = 6.28318530717958647693;
const double Geometry::extent = 1E6;
// ����� �
// ����� pi*2
// ���������� ������
/* ��������� �������������� �������� �� ���������
(�������� ��� ����� � ������� ��� ������) */
class Primitive : public Geometry {
private:
	bool visible;
	// ���������
	unsigned char color;
	// ���� (0�255)
public:
	// ��������� ����� ���������
	int getColor() const { return int(color); }
	// ��������� ����� ���������
	void setColor(int tint)
	{
		color = unsigned char((tint < 0) ? 0 : (tint > 255) ? 255 : tint);
	}
	// �������� ��������� ���������
	bool isVisible() const { return visible; }
	// ����������� ��������� (�����)
	void setShow() { visible = true; }
	// ������� ��������� (�������)
	void setHide() { visible = false; }
	// ��������� �����������
	Primitive() : visible(false), color(0) { }
	// ���������� �����������
	Primitive(const Primitive& obj) : visible(obj.visible), color(obj.color) {}
};
// ����� ��������� ������ ����� �� ��������� (�������� ��� ������)
class Point : public Primitive, public Location {
public:
	// ��������� �����������
	Point() : Primitive(), Location() { }
	// ���������� �����������
	Point(const Point& obj) : Primitive (obj), Location (obj) { }
	// ��������������� �����������
	Point(double xx, double yy, int tint) {
		setX(xx);
		setShow();
		setY(yy);
		setColor(tint);
	}

	// ��������� X-����������
	double getX() const { return x; }
	// ��������� Y-����������
	double getY() const { return y; }
	// ��������� �������
	Location getPosition() const { return Location(x, y); }
	// ��������� �-����������
	virtual void setX(double xx) { x = accurateExtent(xx); }
	// ��������� Y-����������
	virtual void setY(double yy) { y = accurateExtent(yy); }
	// ���������� �������������� �������
	virtual Clip getClipBox() const { return Clip(x, y, x, y); }
	};
		/// ����� ��������� ������ "����������" (��������� ��� �����)
class Figure : public Point {
private:
	double radius;
	double alpha;
	// ������ (����� � ��������)
public:
	// ��������� �����������
	Figure() : Point(), radius(0) { }
	// ���������� �����������
	Figure(const Figure& obj) : Point(obj), radius(obj.radius) { }
	// ��������������� �����������
	Figure(double xc, double yc, double rd, int tint) {
		setColor(tint);
		setShow();
		setRadius(rd);
		// ��������� ����� �������
		// ��������� ����� �������
		setX(xc);
		setY(yc);
	}
	// ��������� ������� ��������
	// ��������� �������
	double getRadius() const {
		return radius;
	}

	// ��������� ������� ��������
	// ��������� ���� ��������
	double getAlpha() const {
		return alpha;
	}

	// ��������� �������
	void setRadius(double r) {
		// ���������� ���������
		// ���������� �������
		radius = ((r < 0) ? -r : r);
	}

	void setAlpha(double a) {
		// ���������� ���������
		// ���������� �������
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

	// ��������� �-���������� ������ (����������)
	virtual void setX(double xx)
	{
		x = (((xx - radius) < -extent) ? (-extent + radius) :
			((xx + radius) > +extent) ? (+extent - radius) : xx);
	}

	// ��������� Y-���������� ������ (����������)
	virtual void setY(double yy)
	{
		y = (((yy - radius) < -extent) ? (-extent + radius) :
			((yy + radius) > +extent) ? (+extent - radius) : yy);
	};

	// ���������� �������������� ������� (����������)
	virtual Clip getClipBox() const
	{
		return Clip(x - radius, y - radius, x + radius, y + radius);
	}
};


/* ��������� ����������� ������
*/
void ErrorValue() {
	std::cin.clear();
	std::cin.sync();
	std::cout << "������: ������������ ��������" << endl;
}


/* ��������� ���������� ��������� ��� ��������� ������� ������*/
void ModifyFigure(Figure& Fig) {
	char ch = 'P';
	// ������� ����
	do {
		double value;
		// ��������� ������ ����
		switch (ch) {
		case 'P':
		case 'p':
			// ������ ���� ������� ������
			std::cout << std::endl << "�������� ������:"
				<< std::endl << "����� = (" << Fig.getX() << ";" << Fig.getY() << ")"
				<< std::endl << "������ = " << Fig.getRadius()
				<< std::endl << "������ ����� = " << Fig.getHordeLength()
				<< std::endl << "���� = " << Fig.getAlpha()
				<< std::endl << "������� = " << Fig.getSquare()
				<< std::endl << "�������� = " << Fig.getLength()
				<< std::endl << "��������� = " << ((Fig.isVisible()) ? "On" : "Off")
				<< std::endl << "����� ����� = " << Fig.getColor() << std::endl;
			{
				Clip area = Fig.getClipBox();
				std::cout << "������� = (" << area.min.x << ";" << area.min.y
					<< ") - (" << area.max.x << ";" << area.max.y << ")" << std::endl
					<< "������ = [" << area.sizeX() << "x" << area.sizeY() << "]"
					<< std::endl;
			}
			break;
		case 'X':
		case 'x':
			//��������� � - ����������(�������� ��������)
			std::cout << std::endl << "������� X-����������:>";
			std::cin >> value;
			if (!std::cin.fail()) Fig.setX(value);
			else ErrorValue();
			break;
		case 'Y':
		case 'y':
			// ��������� Y-���������� (�������� ��������)
			std::cout << std::endl << "������� Y-����������:>";
			std::cin >> value;
			if (!std::cin.fail()) Fig.setY(value);
			else ErrorValue();
			break;
			// ��������� ������� (���� ��������)
		case 'R':
		case 'r':
			std::cout << std::endl << "������� ������ [R > 0]:>";
			std::cin >> value;
			if (!std::cin.fail()) Fig.setRadius(value);
			else ErrorValue();
			break;
		case 'A':
		case 'a':
			std::cout << std::endl << "������� ���� alpha [a > 0]:>";
			std::cin >> value;
			if (!std::cin.fail()) Fig.setAlpha(value);
			else ErrorValue();
			break;
		case 'T':
		case 't':
			// ��������� ����� (������� ��������)
			int tint;
			std::cout << std::endl << "������� ���� [0�255]:>";
			std::cin >> tint;
			if (!std::cin.fail()) Fig.setColor(tint);
			else ErrorValue();
			break;

		case 'V':
			// ������������ ��������� (������� ��������)
		case 'v':
			cout << endl << "��������� [N-on|F-off]:>";
			cin >> ch;
			if (ch = 'N' || ch == 'n') Fig.setShow();
			else if (ch = 'F' || ch == 'f') Fig.setHide();
			else ErrorValue();
			break;
		default: cout << "������: ������������ ��������" << endl;
		}
		// ����������� ����������� ����
		cout << endl << " (T) �������� ����"
			<< endl << " (R) �������� ������"
			<< endl << " (V) �������� ���������"
			<< endl << " (X) �������� �-����������"
			<< endl << " (Y) �������� Y-����������"
			<< endl << " (A) �������� ���� alpha"
			<< endl << " (P) �������� ��� ��������"
			<< endl << " (Q) �����";
		cout << endl << "�������� �����:>";
		cin >> ch;
	} while (ch != 'Q' && ch != 'q');
}
// ������� �������
void main() {
	// ����������� ����� ��������� �� ������� �����
	setlocale(LC_ALL, "Russian");
	cout << "������ 3";
	auto* figure = new Figure(1, 1, 1, 255);
	ModifyFigure(*figure);
}