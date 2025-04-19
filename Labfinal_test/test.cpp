#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
public:
    virtual ~Vehicle() = default;
    virtual void drive() const = 0;
};

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


class VehicleFactory
{
public:
    enum VehicleType
    {
        CAR,
        BIKE,
        TRUCK
    };

    Vehicle* createVehicle(VehicleType type)
    {
        switch (type)
        {
        case CAR:
            return new Car();
        case BIKE:
            return new Bike();
        case TRUCK:
            return new Truck();
        default:
            throw invalid_argument("Unknown vehicle type");
        }
    }
};

class VehicleFactoryTest : public ::testing::Test {
protected:
    VehicleFactory factory;

    void TearDown() override {
   
    }
};

TEST_F(VehicleFactoryTest, CreateCar) {
   
    testing::internal::CaptureStdout();

    Vehicle* car = factory.createVehicle(VehicleFactory::CAR);
    car->drive();


    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("I am driving a car"), string::npos);

    delete car;
}


TEST_F(VehicleFactoryTest, CreateBike) {
    testing::internal::CaptureStdout();

    Vehicle* bike = factory.createVehicle(VehicleFactory::BIKE);
    bike->drive();

    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("I am riding a bike"), string::npos);

    delete bike;
}
TEST_F(VehicleFactoryTest, CreateTruck) {
    testing::internal::CaptureStdout();

    Vehicle* truck = factory.createVehicle(VehicleFactory::TRUCK);
    truck->drive();

    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Drive this truck"), string::npos);

    delete truck;
}

TEST_F(VehicleFactoryTest, CreateAllVehicles) {
    Vehicle* car = factory.createVehicle(VehicleFactory::CAR);
    Vehicle* bike = factory.createVehicle(VehicleFactory::BIKE);
    Vehicle* truck = factory.createVehicle(VehicleFactory::TRUCK);

    EXPECT_NE(dynamic_cast<Car*>(car), nullptr);
    EXPECT_NE(dynamic_cast<Bike*>(bike), nullptr);
    EXPECT_NE(dynamic_cast<Truck*>(truck), nullptr);

    delete car;
    delete bike;
    delete truck;
}


TEST_F(VehicleFactoryTest, InvalidVehicleType) {
   
    EXPECT_THROW(factory.createVehicle(static_cast<VehicleFactory::VehicleType>(999)), invalid_argument);
}