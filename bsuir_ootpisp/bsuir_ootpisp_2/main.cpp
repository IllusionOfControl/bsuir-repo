#include <string>
#include <iostream>

class Doctor {
public:
	virtual void ToHeal() = 0;
	virtual std::string ToString() = 0;
};


class Surgeon : public Doctor {
protected:
	std::string _sex, _firstname, _lastname;
public:
	Surgeon(std::string firstname, std::string lastname, std::string sex) :
	_firstname(firstname), _lastname(lastname), _sex(sex) {}

	virtual std::string ToString() override {
		return "Doctor " + _firstname + " " + _lastname;
	}
};


class Neurosurgeon : public Surgeon {
public:
	Neurosurgeon(std::string firstname, std::string lastname, std::string sex) : Surgeon(firstname, lastname, sex) {}

	void ToHeal() override {
		std::cout << "Cured!" << std::endl;
	}
};


void main() {
	Neurosurgeon doc =  Neurosurgeon("John", "Doe", "male");
	std::cout << doc.ToString() << std::endl;
	doc.ToHeal();
}