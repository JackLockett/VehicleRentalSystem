#pragma once

#include "Vehicle.h"

using namespace std;

class Bike : public Vehicle
{
	public:
		Bike(string vehicleReg, string vehicleMake, string vehicleModel, int vehicleAge, int vehicleEngine, int vehicleWheels);
		~Bike();

		virtual double calculateCostPerDay() const override;
		virtual int getVehicleSeatsOrEngine() const override;
		virtual int getVehicleDoorsOrWheels() const override;
		friend ostream& operator<<(ostream& output, const Bike* rhs);

	private:
		int vehicleEngine, vehicleWheels;
};

inline int Bike::getVehicleSeatsOrEngine() const { return vehicleEngine; }
inline int Bike::getVehicleDoorsOrWheels() const { return vehicleWheels; }

