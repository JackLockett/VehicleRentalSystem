#include "Bike.h"

Bike::Bike(string vehicleReg, string vehicleMake, string vehicleModel, int vehicleAge, int vehicleEngine, int vehicleWheels)
	: Vehicle("Bike", vehicleReg, vehicleMake, vehicleModel, vehicleAge), vehicleEngine(vehicleEngine), vehicleWheels(vehicleWheels) {}

Bike::~Bike() {}

double Bike::calculateCostPerDay() const
{
	double costPerDay = (1500 + vehicleEngine) - (vehicleEngine % 100);
	double costPerDayPounds = costPerDay / 100;	//Convert the cost per day from pence to pounds

	if (costPerDayPounds < 10)
		costPerDayPounds = 10;	//If the cost per day in pounds is less than 10 then we must cap it at 10
	return costPerDayPounds;
}

ostream& operator<<(ostream& output, const Bike* rhs)	//Overloading the ostream operator for writing to the bike to disk
{
	output << rhs->getVehicleType() << "," << rhs->getVehicleReg() << "," << rhs->getVehicleMake() << "," << rhs->getVehicleModel() << "," << rhs->getVehicleAge() << "," << rhs->vehicleEngine << "," << rhs->vehicleWheels;
	return output;
}