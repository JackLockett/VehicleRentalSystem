#define _CRT_SECURE_NO_WARNINGS

#include "Car.h"

Car::Car(string vehicleReg, string vehicleMake, string vehicleModel, int vehicleAge, int vehicleSeats, int vehicleDoors)
	: Vehicle("Car", vehicleReg, vehicleMake, vehicleModel, vehicleAge), vehicleSeats(vehicleSeats), vehicleDoors(vehicleDoors) {}

Car::~Car(){}

double Car::calculateCostPerDay() const
{
	time_t calendarTime = time(nullptr);
	tm* timeData = localtime(&calendarTime);
	int year = timeData->tm_year + 1900;	//Get the current year
	int vehicleAge = year - getVehicleAge();	//Subtract the current year from the vehicle age to find out how old it is

	double costPerDay = 2500 - (vehicleAge * 150) - (vehicleDoors * 200);
	double costPerDayPounds = costPerDay / 100;	//Convert the cost per day from pence to pounds
	if (costPerDayPounds < 10)
		return 10;	//If the cost per day in pounds is less than 10 then we must cap it at 10
	else
		return costPerDayPounds;
}

ostream& operator<<(ostream& output, const Car* rhs)	//Overloading the ostream operator for writing to the bike to disk
{
	output << rhs->getVehicleType() << "," << rhs->getVehicleReg() << "," << rhs->getVehicleMake() << "," << rhs->getVehicleModel() << "," << rhs->getVehicleAge() << "," << rhs->vehicleSeats << "," << rhs->vehicleDoors;
	return output;
}
