#define _CRT_SECURE_NO_WARNINGS

#include "RentalHistory.h"
#include "Rental.h"
#include "Disk.h"
#include "Templates.h"
#include "Definitions.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

RentalHistory::RentalHistory()
{
	rentalHistory = nullptr;
	historicRentals = true;
	heapArraySize = 0;
	numberOfRentals = -1;	// Set the number of rentals as -1 to accomodate the 0 in the heap array index
}

RentalHistory::~RentalHistory()
{
	for (int i = 0; i < heapArraySize; i++)
		delete rentalHistory[i];

	free(rentalHistory);
	rentalHistory = nullptr;
}

void RentalHistory::resizeHeapArray()
{
	increaseArraySize();
																									
	Rental** rentalHistoryResized = (Rental**)realloc(rentalHistory, sizeof(Rental) * heapArraySize + 1);	//I have a temporary copy of rentalHistory for keeping track of the array
	if (rentalHistoryResized == nullptr)																	
		free(rentalHistory);  //I can use free on the rentalHistory if realloc fails
	if (rentalHistoryResized != nullptr)
		rentalHistory = rentalHistoryResized;
}

void RentalHistory::addNewRental(Rental* rental)
{
	resizeHeapArray();
	increaseNumberOfRentals();

	if (rentalHistory[numberOfRentals] != nullptr)
		rentalHistory[numberOfRentals] = rental;
}

void RentalHistory::displayMenu(shared_ptr<Vehicle> vehicle)
{
	Disk* disk = new Disk();
	int menuOption = 0; int rentalsFromDisk = 0; ClearConsole;

	string vehicleReg = vehicle->getVehicleReg();
	string vehicleMake = vehicle->getVehicleMake();
	string vehicleModel = vehicle->getVehicleModel();
	double cost = vehicle->calculateCostPerDay();

	string title = vehicleReg + ": " + vehicleMake + " " + vehicleModel + "\n";
	string titleLength(title.size() - 1, '-');

	rentalHistory = (Rental**)malloc(sizeof(Rental) * heapArraySize);	//Request heap memory to store a Rental Item structure 

	do
	{
		if (equalTo<bool>(historicRentals, true)) 
		{
			disk->readHistoricRentals(vehicleReg, this);
			historicRentals = false;
		}

		cout << title;
		cout << titleLength;

		cout << setw(24) << "\nCost Per Day:";
		cout << left << "\x9C" << setw(17) << cost;

		cout << setw(24) << "\nTotal Rental Income:";
		cout << left << "\x9C" << setw(17) << setw(17) << calculateTotalIncome();

		cout << setw(24) << "\nTotal Days Rented:";
		cout << left << setw(17) << calculateTotalDays();

		cout << "\n\n1) Rent Vehicle\n";
		cout << "2) View historic rentals\n";
		cout << "9) Return to main menu\n\n";

		cout << "Please choose an option: ";
		try 
		{
			cin >> menuOption;
			cin.exceptions(ios_base::failbit);
		}
		catch (ios_base::failure)
		{
			cin.clear();
			NumericLimits;
			InvalidCharacters;
			PressAnyKey;
			cin.ignore();
			ClearConsole;
			continue;
		}

		switch (menuOption)
		{
		case 1:
			rentVehicle(vehicleReg, vehicleMake, vehicleModel, cost);
			break;
		case 2:
			if (equalTo<int>(heapArraySize, 0)) {
				cout << "\nThis vehicle has no rental history.";
				cout << "\nYou can create a rental record by using the rent vehicle option.";
				cout << "\n\nPress any key to continue...";
				cin.ignore();
				cin.get();
			}
			else
				viewHistoricRentals(vehicleReg, vehicleMake, vehicleModel);
			break;
		case 9:
			if (notEqualTo<int>(heapArraySize, 0))
				prepareToWriteRentals(vehicleReg);
			break;
		}
		ClearConsole;
	} while (notEqualTo<int>(menuOption, 9));
	delete disk;
}

void RentalHistory::viewHistoricRentals(string vehicleReg, string vehicleMake, string vehicleModel)
{
	Disk* disk = new Disk();
	int menuOption=0, arrayIndex = numberOfRentals; ClearConsole;

	string title = vehicleReg + ": " + vehicleMake + " " + vehicleModel + " Rental History" + "\n";
	string titleLength(title.size() - 1, '-');

	do
	{
		cout << title;
		cout << titleLength;

		rentalHistory[arrayIndex]->displayHistoricRentals(arrayIndex, numberOfRentals);

		cout << "\n1) View the previous record\n";
		cout << "2) View the next record\n";
		cout << "9) Return to vehicle information screen\n\n";

		cout << "Please choose an option: ";
		cin >> menuOption;

		switch (menuOption)
		{
		case 1:
			if (greaterThan<int>(arrayIndex, 0))
				arrayIndex--;
			break;
		case 2:
			if (lessThan<int>(arrayIndex, numberOfRentals))
				arrayIndex++;
			break;
		}
		ClearConsole;
	} while (notEqualTo<int>(menuOption, 9));
	delete disk;
}

void RentalHistory::rentVehicle(string vehicleReg, string vehicleMake, string vehicleModel, double cost)
{
	ClearConsole;

	string title = vehicleReg + ": " + vehicleMake + " " + vehicleModel + " - Rent Vehicle" + "\n";
	string titleLength(title.size() - 1, '-');

	string customerName, customerAddress, customerNumber;
	int rentalDays = {};

	while (true)
	{
		cout << title;
		cout << titleLength;
		cout << "\n\nWhat is the your full name: ";
		cin.ignore();
		getline(cin, customerName);

		cout << "\nWhat is the your address: ";
		getline(cin, customerAddress);

		cout << "\nWhat is your phone number: ";
		getline(cin, customerNumber);

		if (customerNumber.length() < 11) {
			cout << "\nPhone number needs to be 11 digits long without a space. For example: 01234567890.";
			PressAnyKey;
			cin.get();
			ClearConsole;
			continue;
		}

		cout << "\nHow many days would you like to rent the vehicle: ";

		try
		{
			cin >> rentalDays;
			if (lessThan<int>(rentalDays, 1)) {
				cout << "\nRental days can't be less than 1.";
				PressAnyKey;
				cin.ignore();
				cin.get();
				ClearConsole;
				continue;
			}
			cin.exceptions(ios_base::failbit);
			break;
		}
		catch (ios_base::failure)
		{
			cin.clear();
			NumericLimits;
			InvalidCharacters;
			PressAnyKey;
			cin.ignore();
			ClearConsole;
		}

	}

	double totalCost = cost * rentalDays;
	string dayOfRental = getCurrentDate();
	string endOfRental = getEndDate(rentalDays);

	Rental* newRental = new Rental(customerName, customerAddress, customerNumber, rentalDays, totalCost, dayOfRental, endOfRental);
	addNewRental(newRental);
}

string findDateSuffix(int currentDay)
{
	string dateSuffix;

	if (equalTo<int>(currentDay, 11) || equalTo<int>(currentDay, 12) || equalTo<int>(currentDay, 13))
	{
		dateSuffix = "th";
		return dateSuffix;
	}

	switch (currentDay % 10)
	{
		case 1:
			dateSuffix = "st"; break;
		case 2:
			dateSuffix = "nd"; break;
		case 3:
			dateSuffix = "rd"; break;
		default:
			dateSuffix = "th"; break;
	}

	return dateSuffix;
}

string RentalHistory::getDateString(tm* timeData)
{
	ostringstream oStringStream;
	int currentDay = timeData->tm_mday;
	string ordinals = findDateSuffix(currentDay);		//Add suffixes to the end of the days
	oStringStream << currentDay << ordinals << " " << put_time(timeData, "%B %Y");
	string dateString = oStringStream.str();
	return dateString;
}

string RentalHistory::getCurrentDate()
{
	time_t calendarTime = time(nullptr);
	tm* timeData = localtime(&calendarTime);

	string dateString = getDateString(timeData);
	return dateString;
}

string RentalHistory::getEndDate(int rentalDays)
{
	time_t calendarTime = time(nullptr);
	tm* timeData = localtime(&calendarTime);
	timeData->tm_mday += rentalDays;		//Add the number of rental days onto the current day
	time_t timeLater = mktime(timeData);

	string dateString = getDateString(timeData);
	return dateString;
}

const double RentalHistory::calculateTotalIncome()
{
	double totalIncome = 0;
	for (int i = 0; i < heapArraySize; i++)
		totalIncome += rentalHistory[i]->getTotalCost();
	return totalIncome;
}

const int RentalHistory::calculateTotalDays()
{
	int rentalDays = 0;
	for (int i = 0; i < heapArraySize; i++)
		rentalDays += rentalHistory[i]->getRentalDays();
	return rentalDays;
}

void RentalHistory::prepareToWriteRentals(string vehicleReg)
{
	ofstream rentalFile;
	rentalFile.open("Vehicles/Rentals/" + vehicleReg + ".csv", ios::trunc);
	Disk* disk = new Disk();
	if (notEqualTo<int>(heapArraySize, 0))
		for (int i = 0; i < heapArraySize; i++)
			disk->writeRentalToDisk(vehicleReg, rentalHistory[i]);
	delete disk;
}