#define _CRT_SECURE_NO_WARNINGS

#include "Vehicle.h"

#include <iostream>
#include <iomanip>

Vehicle::Vehicle(string vehicleType, string vehicleReg, string vehicleMake, string vehicleModel, int vehicleAge)
	: vehicleType(vehicleType), vehicleReg(vehicleReg), vehicleMake(vehicleMake), vehicleModel(vehicleModel), vehicleAge(vehicleAge)
{
	make = (char*)malloc(sizeof(char) * vehicleMake.length() + 1);		//+1 to the length to accomodate the \0 character
}

Vehicle::~Vehicle()
{
	free(make);
	make = nullptr;
}

void Vehicle::displayMenuVehicles() 
{
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << left << setw(24) << vehicleReg;
	cout << left << "\x9C" << setw(16) << calculateCostPerDay();
	cout << left << vehicleType << "\n";
}

void Vehicle::displaySearchVehicles()
{
	cout << setw(24) << vehicleReg;
	cout << left << "\x9C" << setw(17) << calculateCostPerDay();
	cout << left << setw(10) << vehicleMake;
	cout << left << vehicleModel << "\n";
}

char* Vehicle::getVehicleMake() const
{
	strcpy(make, vehicleMake.c_str());		//Copy the vehicle make into the c string
	return make;
}
