#pragma once

#include <iostream>

using namespace std;

class Vehicle
{
	public:
		Vehicle(string vehicleType, string vehicleReg, string vehicleMake, string vehicleModel, int vehicleAge);
		~Vehicle();

		void displayMenuVehicles();
		void displaySearchVehicles();
		virtual int getVehicleSeatsOrEngine() const = 0;
		virtual int getVehicleDoorsOrWheels() const = 0;
		virtual double calculateCostPerDay() const = 0;

		string getVehicleReg() const;
		string getVehicleType() const;
		char* getVehicleMake() const;
		string getVehicleModel() const;
		int getVehicleAge() const;

	private:
		string vehicleType, vehicleReg, vehicleMake, vehicleModel;
		int vehicleAge;
		char* make;
	};

inline string Vehicle::getVehicleType() const { return vehicleType; }
inline string Vehicle::getVehicleReg() const { return vehicleReg; }
inline string Vehicle::getVehicleModel() const { return vehicleModel; }
inline int Vehicle::getVehicleAge() const { return vehicleAge; }

