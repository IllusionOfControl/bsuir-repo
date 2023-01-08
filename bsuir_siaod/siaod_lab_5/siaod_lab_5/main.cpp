#include <list>
#include <iostream>
#include <string>


const int NUMBER_MIN = 26000;
const int NUMBER_MAX = 77000;
const int BUCKETS = 10;
const int NUMBERS = 15;


class HashTable
{
	int _buckets;

	std::list<int>* _table;
public:
	HashTable(int V);

	void insertItem(int x);

	void deleteItem(int key);
	
	int findItem(int key);

	int hashFunction(int x) {
		return (x % _buckets);
	}

	void displayHash();
};


HashTable::HashTable(int b)
{
	this->_buckets = b;
	_table = new std::list<int>[_buckets];
}


void HashTable::insertItem(int key)
{
	int index = hashFunction(key);
	_table[index].push_back(key);
}


void HashTable::deleteItem(int key)
{
	int index = hashFunction(key);

	std::list<int>::iterator i;
	for (i = _table[index].begin();
		i != _table[index].end(); i++) {
		if (*i == key)
			break;
	}

	if (i != _table[index].end())
		_table[index].erase(i);
}

int HashTable::findItem(int key)
{
	int index = hashFunction(key);

	std::list<int>::iterator i;
	for (i = _table[index].begin();
		i != _table[index].end(); i++) {
		if (*i == key)
			break;
	}

	if (i != _table[index].end())
		return *i;
}


void HashTable::displayHash() {
	for (int i = 0; i < _buckets; i++) {
		std::cout << i;
		for (auto x : _table[i])
			std::cout << " --> " << x;
		std::cout << std::endl;
	}
}


int main()
{
	int* numbers = (int*)malloc(sizeof(int) * NUMBERS);

	for (int i = 0; i < NUMBERS; i++) {
		numbers[i] = NUMBER_MIN + (rand() % static_cast<int>(NUMBER_MAX - NUMBER_MIN + 1));
	}

	std::cout << "Array : [";
	for (int i = 0; i < NUMBERS; i++) {
		std::cout << "\n\t" << numbers[i];
	}
	std::cout << "\n]\n========================" << std::endl;


	HashTable h(BUCKETS);
	for (int i = 0; i < NUMBERS; i++) {
		h.insertItem(numbers[i]);
	}

	h.displayHash();
	std::cout << "========================" << std::endl;

	int key = numbers[5];
	int index = h.hashFunction(key);
	std::cout << "Find " << key << ":\n" << h.findItem(key) << "\t| Key:" << index << std::endl;
	std::cout << "========================" << std::endl;

	std::cout << "Delete " << key << std::endl;
	h.deleteItem(key);

	h.displayHash();
	std::cout << "========================" << std::endl;

	return 0;
}
