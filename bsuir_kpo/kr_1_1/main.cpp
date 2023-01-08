#include <string>
#include <map>
#include <set>
#include <iostream>
#include <vector>


enum class ShipType {
    CIVIL,
    SLOOP,
    DESTROYER,
    TORPEDO_BOMBER
};


class Ship {
private:
    std::string _name;
    float _fuelLevel;
    float _strengthLevel;
    ShipType _type;
public:
    Ship(std::string name, ShipType type) : _name(name), _fuelLevel(100.f), _strengthLevel(100.f), _type(type) {}

    void Sail() {}
    float Refuel(float fuelLevel) {}
    void Break() {}
};


class Weapon {
private:
    int _ammunitionStock;
    const float _damage;
    float _strengthLevel;
public:
    void Fire() {}
    void Repair() {}
    void Reload() {}
};


class MilitaryShip : public Ship {
private:
    std::vector<Weapon> _weapons;
    std::string _shipRank;
public:
    MilitaryShip(std::string name, ShipType type, std::string shipRank, std::vector<Weapon> weapons) : 
        Ship(name, type), _weapons(weapons), _shipRank(shipRank) {}

    void Fire() {};
    void RechargeAmmunition() {};
    void ScanArea() {};
};


class Port {
private:
    std::string _name;
    float _strengthLevel;
    bool _isActive;
    std::vector<Ship> _mooredShips;
public:
    Port(std::string name) : _name(name), _strengthLevel(100.0f), _isActive(true) {}

    virtual void SailAway(Ship ship) {}
    virtual void SailIn(Ship ship) {}
    virtual void UpdateStatus(bool isActive) {}
};


class MilitaryPort : Port {
private:
    std::vector<Ship> _mooredShips;
    std::vector<Weapon> _weapons;
public:
    void Fire() {}
    
    // overrided for warships only
    void SailAway(Ship ship) override {}
    void SailIn(Ship ship) override {}
    void UpdateStatus(bool isActive) override {}
};