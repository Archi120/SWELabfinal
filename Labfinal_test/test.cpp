#include "pch.h"
#include <iostream>
#include <string>
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

// Factory class - using raw pointers instead of unique_ptr
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

// Test fixture
class VehicleFactoryTest : public ::testing::Test {
protected:
    VehicleFactory factory;

    void TearDown() override {
        // Clean up any resources if needed
    }
};

// Test creating a Car
TEST_F(VehicleFactoryTest, CreateCar) {
    // Redirect cout to capture output
    testing::internal::CaptureStdout();

    Vehicle* car = factory.createVehicle(VehicleFactory::CAR);
    car->drive();

    // Get the output
    string output = testing::internal::GetCapturedStdout();

    // Check the output contains the expected message
    EXPECT_NE(output.find("I am driving a car"), string::npos);

    delete car;
}

// Test creating a Bike
TEST_F(VehicleFactoryTest, CreateBike) {
    testing::internal::CaptureStdout();

    Vehicle* bike = factory.createVehicle(VehicleFactory::BIKE);
    bike->drive();

    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("I am riding a bike"), string::npos);

    delete bike;
}

// Test creating a Truck
TEST_F(VehicleFactoryTest, CreateTruck) {
    testing::internal::CaptureStdout();

    Vehicle* truck = factory.createVehicle(VehicleFactory::TRUCK);
    truck->drive();

    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Drive this truck"), string::npos);

    delete truck;
}

// Test all vehicle types
TEST_F(VehicleFactoryTest, CreateAllVehicles) {
    Vehicle* car = factory.createVehicle(VehicleFactory::CAR);
    Vehicle* bike = factory.createVehicle(VehicleFactory::BIKE);
    Vehicle* truck = factory.createVehicle(VehicleFactory::TRUCK);

    // Verify each object is of the correct type using dynamic_cast
    EXPECT_NE(dynamic_cast<Car*>(car), nullptr);
    EXPECT_NE(dynamic_cast<Bike*>(bike), nullptr);
    EXPECT_NE(dynamic_cast<Truck*>(truck), nullptr);

    delete car;
    delete bike;
    delete truck;
}

// Test invalid vehicle type
TEST_F(VehicleFactoryTest, InvalidVehicleType) {
    // This test verifies that an exception is thrown for an invalid type
    // Note: This requires casting to an int since we can't directly pass an invalid enum value
    EXPECT_THROW(factory.createVehicle(static_cast<VehicleFactory::VehicleType>(999)), invalid_argument);
}