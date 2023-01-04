#define _CRT_SECURE_NO_WARNINGS

#include "Container.h"
#include "Definitions.h"
#include "Templates.h"
#include "Vehicle.h"
#include "Disk.h"

#include <fstream>
#include <regex>

Container::Container() { returnToMenu = false;}
Container::~Container() {}

bool Container::checkVehicleRegExists(string vehicleReg)
{
	vector<shared_ptr<Vehicle>>::iterator findVehicleReg = find_if(allVehicles.begin(), allVehicles.end(), [&vehicleReg](shared_ptr<Vehicle> reg) {return reg->getVehicleReg() == vehicleReg;});
	if (findVehicleReg != allVehicles.end())		//Lamda iterator used to check if the vehicle registration is already in the vector
		return true;
	else
		return false;
}

bool Container::checkVehicleRegFormat(string vehicleReg)
{
	regex checkReg("(^[A-Z]{2}[0-9]{2} [A-Z]{3}$)|(^[A-Z][0-9]{1,3} [A-Z]{3}$)|(^[A-Z]{3} [0-9]{1,3}[A-Z]$)|(^[0-9]{1,4} [A-Z]{1,2}$)|(^[0-9]{1,3} [A-Z]{1,3}$)|(^[A-Z]{1,2} [0-9]{1,4}$)|(^[A-Z]{1,3} [0-9]{1,3}$)");
	if (regex_match(vehicleReg, checkReg))	//Using regex to check if the number plate is using a valid UK format. I took the regex validation from https://www.regextester.com/97133 which heavily influenced my solution for checking vehicle registration formats
		return true;
	return false;
}

void Container::addVehicleEntry()
{
	ClearConsole;
	int option = 0;
	string vehicleReg, vehicleMake, vehicleModel;
	int vehicleAge{}, vehicleSeats{}, vehicleDoors{}, vehicleEngine{}, vehicleWheels{};

	do
	{
		try
		{
			cout << "Add vehicle";
			cout << "\n-----------\n\n";
			cout << "1) Car\n";
			cout << "2) Bike\n";
			cout << "9) Return to main menu\n\n";
			
			cout << "Please choose an option: ";
			cin >> option;
			cin.exceptions(ios_base::failbit);

			if (equalTo<int>(option, 1) || equalTo<int>(option, 2))
			{
				cout << "\nWhat is the vehicle registration: ";
				cin.ignore();
				getline(cin, vehicleReg);

				bool checkRegExists = checkVehicleRegExists(vehicleReg);	//Check if the registration is already an item in the container
				bool checkRegFormat = checkVehicleRegFormat(vehicleReg);	//Check if the registration is using the correct format

				if (equalTo<bool>(checkRegExists, true))
				{
					cout << "\nVehicle with the registration of (" << vehicleReg << ") already exists.";
					PressAnyKey;		//Definitions used from Definitions.h so we aren't consistently using the same lines of code
					cin.ignore();
					ClearConsole;
					continue;
				}
				if (equalTo<bool>(checkRegFormat, false))
				{
					cout << "\nInvalid registration format.";
					PressAnyKey;
					cin.ignore();
					ClearConsole;
					continue;
				}

				cout << "\nWhat is the vehicle make: ";
				cin >> vehicleMake;
				cout << "\nWhat is the vehicle model: ";
				cin >> vehicleModel;
				cout << "\nHow old is the vehicle in year(s) (e.g. 2015): ";
				cin >> vehicleAge;

				if (to_string(vehicleAge).length() < 4)	//Check if the vehicle age length is less than 4
				{
					cout << "\nVehicle age needs to be 4 digits long. For example: 2022";
					PressAnyKey;
					cin.ignore();
					cin.get();
					ClearConsole;
					continue;
				}
			}
			else 
			{
				ClearConsole;
				continue;
			}

			switch (option)
			{
			case 1:
			{
				cout << "\nHow many seats does the vehicle have: ";
				cin >> vehicleSeats;
				cout << "\nHow many doors does the vehicle have: ";
				cin >> vehicleDoors;
				addItem(shared_ptr<Vehicle>(new Car(vehicleReg, vehicleMake, vehicleModel, vehicleAge, vehicleSeats, vehicleDoors)));
				cout << "\n------------------------";
				cout << "\nSuccessfully Added Car!\n";
				cout << "\n" << vehicleReg << ": " << vehicleMake << " " << vehicleModel;
				cout << "\nVehicle Age: " << vehicleAge;
				cout << "\nNumber of Seats: " << vehicleSeats;
				cout << "\nNumber of Doors: " << vehicleDoors;
				cout << "\n------------------------";
				break;
			}
			case 2:
			{
				cout << "\nWhat is the engine size (Do not include CC): ";
				cin >> vehicleEngine;
				cout << "\nHow many wheels does the vehicle have (2 or 3): ";
				cin >> vehicleWheels;

				if (equalTo<int>(vehicleWheels, 2) || equalTo<int>(vehicleWheels, 3))	//Check if the number of wheels is equal to 2 or 3
				{
					addItem(shared_ptr<Vehicle>(new Bike(vehicleReg, vehicleMake, vehicleModel, vehicleAge, vehicleEngine, vehicleWheels)));
					cout << "\n-------------------------";
					cout << "\nSuccessfully Added Bike!\n";
					cout << "\n" << vehicleReg << ": " << vehicleMake << " " << vehicleModel;
					cout << "\nVehicle Age: " << vehicleAge;
					cout << "\nMax Engine Size: " << vehicleEngine;
					cout << "\nNumber of Wheels: " << vehicleWheels;
					cout << "\n------------------------";
					break;
				}
				else
				{
					cout << "\nBikes can only have 2 or 3 wheels.";
					PressAnyKey;
					cin.ignore();
					cin.get();
					ClearConsole;
					continue;
				}
			}
			case 9:
				break;
			}
		}
		catch(ios_base::failure)
		{
			cin.clear();
			NumericLimits;
			InvalidCharacters;
			PressAnyKey;
			cin.ignore();
			ClearConsole;
			continue;
		}

		cout << "\n\nWould you like to add another vehicle?\n\n";
		cout << "1) Add another vehicle\n";
		cout << "2) Return to main menu\n\n";
		cout << "Please choose an option: ";
		cin >> option;

		if (equalTo<int>(option, 1))
		{
			ClearConsole;
			continue;
		}
		else if (equalTo<int>(option, 2))
			break;
		break;

		ClearConsole;
	} while (notEqualTo<int>(option, 9));
}

void Container::removeFile(string fileName)
{
	char* cString = new char[fileName.length() + 1];	// +1 is used to accomate the \0 character
	strcpy(cString, fileName.c_str());
	remove(cString);
	delete[] cString;
}

void Container::removeVehicleEntry()
{
	ClearConsole;
	int option = 0; 
	string vehicleType, vehicleReg;

	do 
	{
		try 
		{
			cout << "Remove vehicle";
			cout << "\n--------------\n\n";

			cout << "1) Car\n";
			cout << "2) Bike\n";
			cout << "9) Return to main menu\n\n";

			cout << "Please choose an option: ";
			cin >> option;
			cin.exceptions(ios_base::failbit);

			if (equalTo<int>(option, 1) || equalTo<int>(option, 2))
			{
				cout << "\nWhat is the vehicle registration: ";
				cin.ignore();
				getline(cin, vehicleReg);

				if (equalTo<int>(option, 1))
					vehicleType = "Car";
				else if (equalTo<int>(option, 2))
					vehicleType = "Bike";

				vector<shared_ptr<Vehicle>>::iterator findVehicle = find_if(allVehicles.begin(), allVehicles.end(), [&](shared_ptr<Vehicle> vehicle) {return vehicle->getVehicleType() == vehicleType && vehicle->getVehicleReg() == vehicleReg;});
				if (findVehicle != allVehicles.end())
				{
					removeItem(vehicleReg);		//Remove item from the container if the iterator finds the vehicle

					switch (option)
					{
					case 1:
					{
						string vehicleFileName = "Vehicles/Cars/" + vehicleReg + ".csv\0";
						removeFile(vehicleFileName);	//Convert the file name to a cstring in order to delete it
						break;
					}
					case 2:
					{
						string vehicleFileName = "Vehicles/Bikes/" + vehicleReg + ".csv\0";
						removeFile(vehicleFileName);
						break;
					}
					case 9:
						break;
					}

					string rentalFileName = "Vehicles/Rentals/" + vehicleReg + ".csv\0";	// We also need to delete the vehicles rental history if it exists
					removeFile(rentalFileName);

					cout << "\nThe vehicle with the matching registration of (" << vehicleReg << ") has been removed.";
				}
				else
				{
					transform(vehicleType.begin(), vehicleType.end(), vehicleType.begin(), ::tolower);
					cout << "\nNo " << vehicleType << " matches that registration.\n";
					PressAnyKey;
					cin.ignore();
					ClearConsole;
					continue;
				}

			}
			else
			{
				ClearConsole;
				continue;
			}
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

		cout << "\n\nWould you like to remove another vehicle?\n\n";
		cout << "1) Remove another vehicle\n";
		cout << "2) Return to main menu\n\n";
		cout << "Please choose an option: ";
		cin >> option;

		if (equalTo<int>(option, 1))
		{
			ClearConsole;
			continue;
		}
		else if (equalTo<int>(option, 2))
			break;
		break;
		ClearConsole;
	}
	while (notEqualTo<int>(option, 9));
}

void Container::displayCarSearchMenu()
{
	ClearConsole;
	int option = 0, value = 0;
	string vehicleReg; 
	string vehicleType = "Car";
	returnToMenu = false;
	do
	{
		clearVehicleMap();	//Clear the STL Map in case it was previously used in a different search
		if (equalTo<bool>(returnToMenu, true))
			break;
		cout << "Search for a car by:\n";
		cout << "--------------------\n\n";
		cout << "1) Registration number\n";
		cout << "2) Number of seats\n";
		cout << "3) Number of doors\n";
		cout << "9) Return to main menu\n\n";

		cout << "Please choose an option: ";
		try
		{
			cin >> option;
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

		try
		{
			switch (option)
			{
			case 1:
				cout << "\nEnter registration number: ";
				cin.ignore();
				getline(cin, vehicleReg);
				searchRegistration(vehicleType, vehicleReg);
				break;
			case 2:
				cout << "\nEnter number of seats: ";
				cin >> value;
				searchVehicleCriteria(vehicleType, "Seats", value);
				break;
			case 3:
				cout << "\nEnter number of doors: ";
				cin >> value;
				searchVehicleCriteria(vehicleType, "Doors", value);
				break;
			}
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
		if (equalTo<int>(option, 1) || equalTo<int>(option, 2) || equalTo<int>(option, 3))
			chooseVehicle();
		ClearConsole;
	} while (notEqualTo<int>(option, 9));
}

void Container::displayBikeSearchMenu()
{
	ClearConsole;
	int option = 0, value = 0;
	string vehicleReg;
	string vehicleType = "Bike";
	returnToMenu = false;
	do
	{
		clearVehicleMap();
		if (equalTo<bool>(returnToMenu, true))
			break;
		cout << "Search for a bike by:\n";
		cout << "---------------------\n\n";
		cout << "1) Registration number\n";
		cout << "2) Max engine size\n";
		cout << "3) Two or three wheeler\n";
		cout << "9) Return to main menu\n\n";

		cout << "Please choose an option: ";
		try
		{
			cin >> option;
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

		try
		{
			switch (option)
			{
			case 1:
				cout << "\nEnter registration number: ";
				cin.ignore();
				getline(cin, vehicleReg);
				searchRegistration(vehicleType, vehicleReg);
				break;
			case 2:
				cout << "\nEnter max engine size: ";
				cin >> value;
				searchVehicleCriteria(vehicleType, "Engine", value);
				break;
			case 3:
				cout << "\nEnter number of wheels: ";
				cin >> value;
				searchVehicleCriteria(vehicleType, "Wheels", value);
				break;
			}
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
		if (equalTo<int>(option, 1) || equalTo<int>(option, 2) || equalTo<int>(option, 3))
			chooseVehicle();
		ClearConsole;
	} while (notEqualTo<int>(option, 9));
}

void Container::displaySearchVehicles(string vehicleType, string vehicleReg)	//Function overloading for the displaying of search items based on vehicle registration
{
	int menuItem = 0;
	for (int i = 0; i < allVehicles.size(); i++)
	{
		if (allVehicles[i]->getVehicleType() == vehicleType && allVehicles[i]->getVehicleReg() == vehicleReg)
		{
			menuItem++;
			cout << menuItem << ") ";
			cout << setw(24) << allVehicles[i]->getVehicleReg();
			cout << left << "\x9C" << setw(17) << allVehicles[i]->calculateCostPerDay();
			cout << left << setw(10) << allVehicles[i]->getVehicleMake();
			cout << left << allVehicles[i]->getVehicleModel() << "\n";

			vehicleMap.insert({ menuItem, allVehicles[i] });	//Insert vehicle into STL Map
		}
	}
}

void Container::displaySearchVehicles(string vehicleType, string vehicleCriteria, int value)	//Function overloading for the displaying of search items based on other vehicle criteria
{
	int menuItem = 0;

	for (int i = 0; i < allVehicles.size(); i++)
	{
		if (allVehicles[i]->getVehicleType() == vehicleType)
		{
			if (vehicleCriteria == "Seats" || vehicleCriteria == "Engine" ? allVehicles[i]->getVehicleSeatsOrEngine() == value : allVehicles[i]->getVehicleDoorsOrWheels() == value)
			{
				menuItem++;
				cout << menuItem << ") ";
				cout << setw(24) << allVehicles[i]->getVehicleReg();
				cout << left << "\x9C" << setw(17) << allVehicles[i]->calculateCostPerDay();
				cout << left << setw(10) << allVehicles[i]->getVehicleMake();
				cout << left << allVehicles[i]->getVehicleModel() << "\n";

				vehicleMap.insert({ menuItem, allVehicles[i] });
			}
		}
	}
}

void Container::searchRegistration(string vehicleType, string vehicleReg)
{
	vector<shared_ptr<Vehicle>>::iterator findVehicle = find_if(allVehicles.begin(), allVehicles.end(), [&](shared_ptr<Vehicle> vehicle) {return vehicle->getVehicleType() == vehicleType && vehicle->getVehicleReg() == vehicleReg;});

	if (findVehicle != allVehicles.end())
	{
		displaySearchTitle();
		displaySearchVehicles(vehicleType, vehicleReg);
	}
	else
	{
		transform(vehicleType.begin(), vehicleType.end(), vehicleType.begin(), ::tolower);
		cout << "\nNo " << vehicleType << " matches that registration.\n";
		PressAnyKey;
		cin.ignore();
	}
}

void Container::searchVehicleCriteria(string vehicleType, string vehicleCriteria, int value)	
{
	vector<shared_ptr<Vehicle>>::iterator findVehicle;

	if (vehicleCriteria == "Seats" || vehicleCriteria == "Engine")
	{
		findVehicle = find_if(allVehicles.begin(), allVehicles.end(), [&](shared_ptr<Vehicle> vehicle)
			{return vehicle->getVehicleType() == vehicleType && vehicle->getVehicleSeatsOrEngine() == value;});
	}
	else if (vehicleCriteria == "Doors" || vehicleCriteria == "Wheels") 
	{
		findVehicle = find_if(allVehicles.begin(), allVehicles.end(), [&](shared_ptr<Vehicle> vehicle)
			{return vehicle->getVehicleType() == vehicleType && vehicle->getVehicleDoorsOrWheels() == value;});
	}

	if (findVehicle != allVehicles.end())
	{
		displaySearchTitle();
		displaySearchVehicles(vehicleType, vehicleCriteria, value);
	}
	else
	{
		transform(vehicleType.begin(), vehicleType.end(), vehicleType.begin(), ::tolower);
		transform(vehicleCriteria.begin(), vehicleCriteria.end(), vehicleCriteria.begin(), ::tolower);
		cout << "\nNo " << vehicleType << " matches that value for the " << vehicleCriteria << ".\n";
		PressAnyKey;
		cin.ignore();
		cin.get();
	}
}

void Container::chooseVehicle()
{
	int option = 0;
	if (!vehicleMap.empty())
	{
		cout << "\n\nEnter number to choose vehicle or 0 to return to main menu: ";
		cin >> option;
		if (vehicleMap.count(option))
		{
			returnToMenu = true;
			RentalHistory* rentalHistory = new RentalHistory();
			rentalHistory->displayMenu(vehicleMap[option]);
			ClearConsole;
			delete rentalHistory;
		}
		else if (equalTo<int>(option, 0))
		{
			returnToMenu = true;
			return;
		}
		else
		{
			cout << "\nInvalid selection.";
			PressAnyKey;
			cin.ignore();
			cin.get();
			ClearConsole;
		}
	}
}

void Container::displayMenuVehicles()
{
    if (!allVehicles.empty()) 
	{
        cout << "\nRegistration Number     Cost Per Day     Vehicle Type\n";
        cout << "-------------------     ------------     ------------\n";

        for (int i = 0; i < allVehicles.size(); i++)
			allVehicles[i]->displayMenuVehicles();
    }
}

void Container::writeContainerToDisk()
{
	Disk* disk = new Disk();
	ofstream carFileNames; ofstream bikeFileNames;
	for (int i = 0; i < allVehicles.size(); i++) 
	{
		if (allVehicles[i]->getVehicleType() == "Car" && typeid(*allVehicles[i]) == typeid(Car))
			carFileNames.open("Vehicles/Car_Files.csv", ios::trunc);
		else if (allVehicles[i]->getVehicleType() == "Bike" && typeid(*allVehicles[i]) == typeid(Bike))
			bikeFileNames.open("Vehicles/Bike_Files.csv", ios::trunc);

		disk->writeVehicleToDisk(allVehicles[i]);
	}
	delete disk;
}
