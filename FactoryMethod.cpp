#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Base Product class
class Vehicle
{
public:
    virtual ~Vehicle() = default;
    virtual void drive() const = 0;
};

// Concrete Products
class Car : public Vehicle
{
public:
    void drive() const override
    {
        cout << "I am driving a car. Start it...." << endl;
    }
};

class Bike : public Vehicle
{
public:
    void drive() const override
    {
        cout << "I am riding a bike..." << endl;
    }
};

class Truck : public Vehicle
{
public:
    void drive() const override
    {
        cout << "Drive this truck...." << endl;
    }
};

// Factory class
class VehicleFactory
{
public:
    enum VehicleType
    {
        CAR,
        BIKE,
        TRUCK
    };

    unique_ptr<Vehicle> createVehicle(VehicleType type)
    {
        switch (type)
        {
        case CAR:
            return make_unique<Car>();
        case BIKE:
            return make_unique<Bike>();
        case TRUCK:
            return make_unique<Truck>();
        default:
            throw invalid_argument("Unknown vehicle type");
        }
    }
};

int main()
{
    VehicleFactory factory;

    auto car = factory.createVehicle(VehicleFactory::CAR);
    auto bike = factory.createVehicle(VehicleFactory::BIKE);
    auto truck = factory.createVehicle(VehicleFactory::TRUCK);
    cout << "Testing vehicles:" << endl;
    car->drive();
    bike->drive();
    truck->drive();

    return 0;
}