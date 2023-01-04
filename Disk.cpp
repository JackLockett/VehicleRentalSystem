#include "RentalHistory.h"
#include "Container.h"
#include "Rental.h"
#include "Disk.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Disk::Disk() 
{ 
	rentalTotal = true;
}

Disk::~Disk() {}

void Disk::writeVehicleToDisk(shared_ptr<Vehicle> vehicle)
{
	ofstream uniqueVehicleFile; ofstream carFileNames; ofstream bikeFileNames;
	if (vehicle->getVehicleType() == "Car")
	{
		uniqueVehicleFile.open("Vehicles/" + vehicle->getVehicleType() + "s/" + vehicle->getVehicleReg() + ".csv", ios::out | ios::trunc);
		shared_ptr<Car> CarDetails = dynamic_pointer_cast<Car>(vehicle);		//This is used to convert the shared_ptr type from the pointer on the vehicle base class to the pointer on the car derived class
		uniqueVehicleFile << CarDetails << "\n";
		uniqueVehicleFile.close();

		carFileNames.open("Vehicles/Car_Files.csv", ios::app);
		carFileNames << vehicle->getVehicleReg() << ".csv" << "\n";
	}
	else if (vehicle->getVehicleType() == "Bike") 
	{
		uniqueVehicleFile.open("Vehicles/" + vehicle->getVehicleType() + "s/" + vehicle->getVehicleReg() + ".csv", ios::out | ios::trunc);
		shared_ptr<Bike> BikeDetails = dynamic_pointer_cast<Bike>(vehicle);		//This is used to convert the shared_ptr type from the pointer on the vehicle base class to the pointer on the bike derived class
		uniqueVehicleFile << BikeDetails << "\n";
		uniqueVehicleFile.close();

		bikeFileNames.open("Vehicles/Bike_Files.csv", ios::app);
		bikeFileNames << vehicle->getVehicleReg() << ".csv" << "\n";
	}
	uniqueVehicleFile.close();
	carFileNames.close();
	bikeFileNames.close();
}

void Disk::writeRentalToDisk(string vehicleReg, Rental* rentalHistory)
{
	ofstream rentalFile("Vehicles/Rentals/" + vehicleReg + ".csv", ios::app);
	rentalFile << rentalHistory << "\n";
	rentalFile.close();
}

int Disk::getNumberOfRentals(string vehicleReg)
{
	ifstream rentalFile;
	string fileLine;

	int rentalNumber = 0;

	rentalFile.open("Vehicles/Rentals/" + vehicleReg + ".csv");
	while (getline(rentalFile, fileLine))
		rentalNumber++;
	return rentalNumber;
}

void Disk::readHistoricRentals(string vehicleReg, RentalHistory* rentalHistory)
{
	ifstream rentalFile("Vehicles/Rentals/" + vehicleReg + ".csv");
	string fileLine;

	int rentalDays = 0;
	float totalCost = 0;
	string customerName, customerAddress, customerNumber, dayOfRental, endOfRental;

	if (rentalFile.good())
	{
		while (getline(rentalFile, fileLine))
		{
			stringstream inputString(fileLine);

			getline(inputString, customerName, ',');
			getline(inputString, customerAddress, ',');
			getline(inputString, customerNumber, ',');
			getline(inputString, fileLine, ','); rentalDays = stoi(fileLine);
			getline(inputString, fileLine, ','); totalCost = stof(fileLine);
			getline(inputString, dayOfRental, ',');
			getline(inputString, endOfRental, ',');

			Rental* diskRental = new Rental(customerName, customerAddress, customerNumber, rentalDays, totalCost, dayOfRental, endOfRental);	//Add pointer to vector from disk
			rentalHistory->addNewRental(diskRental);
		}
	}
}

void Disk::readVehicles(const char* fileName, string vehicleType, Container* container)
{
	ifstream vehicleFileNames(fileName);
	string fileLine;
	if (vehicleFileNames.is_open())
	{
		while (getline(vehicleFileNames, fileLine))
		{
			ifstream uniqueVehicleFile;
			uniqueVehicleFile.open("Vehicles/" + vehicleType + "/" + fileLine);
			while (getline(uniqueVehicleFile, fileLine))
			{
				stringstream inputString(fileLine);
				string vehicleType, vehicleReg, vehicleMake, vehicleModel;
				int vehicleAge = {}, vehicleSeats = {}, vehicleDoors = {}, vehicleEngine = {}, vehicleWheels = {};

				getline(inputString, vehicleType, ',');
				getline(inputString, vehicleReg, ',');
				getline(inputString, vehicleMake, ',');
				getline(inputString, vehicleModel, ',');
				getline(inputString, fileLine, ','); vehicleAge = stoi(fileLine);	//Convert from string to integer 

				getline(inputString, fileLine, ',');
				if (vehicleType == "Car")
					vehicleSeats = stoi(fileLine);		
				else if (vehicleType == "Bike")
					vehicleEngine = stoi(fileLine);

				getline(inputString, fileLine, ',');
				if (vehicleType == "Car")
					vehicleDoors = stoi(fileLine);
				else if (vehicleType == "Bike")
					vehicleWheels = stoi(fileLine);

				if (vehicleType == "Car")
					container->addItem(shared_ptr<Vehicle>(new Car(vehicleReg, vehicleMake, vehicleModel, vehicleAge, vehicleSeats, vehicleDoors)));		//Add smart pointer to vector from disk
				else if (vehicleType == "Bike")
					container->addItem(shared_ptr<Vehicle>(new Bike(vehicleReg, vehicleMake, vehicleModel, vehicleAge, vehicleEngine, vehicleWheels)));

				container->shuffleItems();
			}
			uniqueVehicleFile.close();
		}
	}
	vehicleFileNames.close();
}

void Disk::readVehiclesFromDisk(Container* container)
{
	readVehicles("Vehicles/Car_Files.csv", "Cars", container);
	readVehicles("Vehicles/Bike_Files.csv", "Bikes", container);
}
