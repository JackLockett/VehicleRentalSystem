#pragma once

#include "Car.h"
#include "Bike.h"
#include "Vehicle.h"
#include "Container.h"
#include "RentalHistory.h"

#include <iostream>

using namespace std;

class Disk
{
	public:
		Disk();
		~Disk();

		void writeVehicleToDisk(shared_ptr<Vehicle> vehicle);
		void writeRentalToDisk(string vehicleReg, Rental* rentalHistory);
		int getNumberOfRentals(string vehicleReg);
		void readHistoricRentals(string vehicleReg, RentalHistory* rh);
		void readVehicles(const char* fileName, string vehicleType, Container* container);
		void readVehiclesFromDisk(Container* container);

	private:
		bool rentalTotal;
};

