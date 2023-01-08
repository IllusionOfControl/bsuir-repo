#include <string>
#include <iostream>
#include <vector>


class Factory {
protected:
    std::string _factoryName;
    std::string _location;
public:
    Factory(std::string factoryName, std::string location)
                : _factoryName(factoryName), _location(location) {}
    virtual ~Factory() {}

    virtual float calculateOutput(float resourceUnit) = 0;
    virtual void print() = 0;
};


class ChemicalFactory : Factory {
private:
    const float _resourceUtilizationRate = 1.0f;
public:
    ChemicalFactory(std::string factoryName, std::string location, float resourceUtilizationRate)
        : _resourceUtilizationRate(resourceUtilizationRate), Factory(factoryName, location) {}

    ~ChemicalFactory() {}

    float calculateOutput(float resourceIn) override {
        return resourceIn * _resourceUtilizationRate;
    }

    void print() {
        std::cout << "\nFactory name: " << _factoryName;
        std::cout << "\nLocation: " << _location;
        std::cout << "\nResource utilization rate: " << _resourceUtilizationRate;
        std::cout << "\n=================================\n";
    }
};


enum class ConcreteType
{
    CEMENTE_CONCRETE,
    LIME_CONCRETE,
    GYPSUM_CONCRETE
};


std::string getStringConcreteType(ConcreteType type) {
    switch (type) {
        case ConcreteType::CEMENTE_CONCRETE:    return "CEMENTE_CONCRETE";
        case ConcreteType::LIME_CONCRETE:       return "LIME_CONCRETE";
        case ConcreteType::GYPSUM_CONCRETE:     return "GYPSUM_CONCRETE";
        default:                                return "";
    };
}


class ConcreteFactory : protected Factory {
protected:
    const ConcreteType _outputConcreteType;
public:
    ConcreteFactory(std::string factoryName, std::string location, ConcreteType type)
        : _outputConcreteType(type), Factory(factoryName, location) {}

    ~ConcreteFactory() {}

    float calculateOutput(float resourceIn) override {
        return resourceIn;
    }

    void print() {
        std::cout << "\nFactory name: " << _factoryName;
        std::cout << "\nLocation: " << _location;
        std::cout << "\nConcrete type: " << getStringConcreteType(_outputConcreteType);
        std::cout << "\n=================================\n";
    }
};


class MobileConcreteFactory : ConcreteFactory {
public:
    MobileConcreteFactory(std::string factoryName, std::string location, ConcreteType type)
        : ConcreteFactory(factoryName, location, type) {}

    ~MobileConcreteFactory() {}

    void setLocation(std::string location) {
        _location = location;
    }
};


int main() {
    Factory** factories = (Factory**)malloc(sizeof(void*) * 10);
    factories[0] = (Factory*) new MobileConcreteFactory("Moblice Concrete Fabric", "Germany, Keln", ConcreteType::CEMENTE_CONCRETE);
    factories[1] = (Factory*) new ConcreteFactory("Concrete Fabric", "Russia, Moscow", ConcreteType::LIME_CONCRETE);
    factories[2] = (Factory*) new ChemicalFactory("BAYERN", "Germany, Leverkusen", 0.9f);
    
    factories[0]->print();
    factories[1]->print();
    factories[2]->print();

    free(factories[0]);
    free(factories[1]);
    free(factories[2]);
    free(factories);
    return 0;
}