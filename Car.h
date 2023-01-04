#pragma once

#include "Vehicle.h"

using namespace std;

class Car : public Vehicle
{
	public:
		Car(string vehicleReg, string vehicleMake, string vehicleModel, int vehicleAge, int vehicleSeats, int vehicleDoors);
		~Car();

		virtual double calculateCostPerDay() const override;
		virtual int getVehicleSeatsOrEngine() const override;
		virtual int getVehicleDoorsOrWheels() const override;
		friend ostream& operator<<(ostream& output, const Car* rhs);

	private:
		int vehicleSeats, vehicleDoors;
};

inline int Car::getVehicleSeatsOrEngine() const { return vehicleSeats; }
inline int Car::getVehicleDoorsOrWheels() const { return vehicleDoors; }

