#pragma once

#include <iostream>
#include <iomanip>

using namespace std;

class Rental
{
	public:
		Rental(string customerName, string customerAddress, string customerNumber, int rentalDays, double totalCost, string dayOfRental, string endOfRental);
		~Rental();

		void displayHistoricRentals(int arrayIndex, int numberOfRentals);
		const int getRentalDays();
		const double getTotalCost();
		const string getDayOfRental();
		const string getEndOfRental();
		friend ostream& operator<<(ostream& output, const Rental* rhs);

	private:
		string customerName, customerAddress, customerNumber, dayOfRental, endOfRental;
		int rentalDays = 0;
		double totalCost = 0;
};

inline const int Rental::getRentalDays() { return rentalDays; }
inline const double Rental::getTotalCost() { return totalCost; }
inline const string Rental::getDayOfRental() { return dayOfRental; }
inline const string Rental::getEndOfRental() { return endOfRental; }

