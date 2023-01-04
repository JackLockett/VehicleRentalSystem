#define _CRT_SECURE_NO_WARNINGS

#include "Disk.h"
#include "Rental.h"
#include "Definitions.h"
#include "RentalHistory.h"

#include <iostream>

using namespace std;

Rental::Rental(string customerName, string customerAddress, string customerNumber, int rentalDays, double totalCost, string dayOfRental, string endOfRental) :
	customerName(customerName), customerAddress(customerAddress), customerNumber(customerNumber), rentalDays(rentalDays), totalCost(totalCost), dayOfRental(dayOfRental), endOfRental(endOfRental) {}

Rental::~Rental() {}

void Rental::displayHistoricRentals(int arrayIndex, int numberOfRentals)
{
	cout << setw(24) << "\nRental: ";
	cout << left << arrayIndex << " of " << setw(17) << numberOfRentals;
	cout << setw(24) << "\nDate From:";
	cout << left << setw(17) << dayOfRental;
	cout << setw(24) << "\nDate To:";
	cout << left << setw(17) << endOfRental;
	cout << setw(24) << "\nRental Days: ";
	cout << left << setw(17) << rentalDays;
	cout << setw(24) << "\nTotal Cost:";
	cout << left << "\x9C" << setw(17) << totalCost;
	cout << setw(24) << "\nCustomer Name: ";
	cout << left << setw(17) << customerName;
	cout << setw(24) << "\nCustomer Address: ";
	cout << left << setw(17) << customerAddress;
	cout << setw(24) << "\nCustomer Number: ";
	cout << left << setw(17) << customerNumber << "\n";
}

ostream& operator<<(ostream& output, const Rental* rhs)		//Overloading the ostream operator for writing to the rental to disk
{
	output << rhs->customerName << "," << rhs->customerAddress << "," << rhs->customerNumber << "," << rhs->rentalDays << "," << rhs->totalCost << "," << rhs->dayOfRental << "," << rhs->endOfRental;
	return output;
}
