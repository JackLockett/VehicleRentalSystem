#pragma once

#include "Rental.h"
#include "Vehicle.h"

#include <iostream>

using namespace std;

class RentalHistory
{
	public:
		RentalHistory();
		~RentalHistory();

		void resizeHeapArray();
		void addNewRental(Rental* rental);
		void displayMenu(shared_ptr<Vehicle> vehicle);
		void viewHistoricRentals(string vehicleReg, string vehicleMake, string vehicleModel);
		void rentVehicle(string vehicleReg, string vehicleMake, string vehicleModel, double cost);
		void prepareToWriteRentals(string vehicleReg);

		string getDateString(tm* timeData);
		string getCurrentDate();
		string getEndDate(int rentalDays);
		const double calculateTotalIncome();
		const int calculateTotalDays();

		void increaseArraySize();
		void increaseNumberOfRentals();

	private:
		bool historicRentals;
		int heapArraySize;
		int numberOfRentals;
		Rental** rentalHistory;
};

inline void RentalHistory::increaseArraySize() { heapArraySize += 1; }
inline void RentalHistory::increaseNumberOfRentals() { numberOfRentals += 1; }