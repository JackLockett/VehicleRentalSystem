#include "Disk.h"
#include "Container.h"
#include "Definitions.h"

#include <iostream>

using namespace std;

int main()
{
#ifdef _DEBUG
	_onexit(_CrtDumpMemoryLeaks);
#endif

	Disk* disk = new Disk();
	Container* container = new Container();

	int option=0; ClearConsole;

	do
	{
		cout << "Vehicle Rental System\n";
		cout << "---------------------\n";

		for (static bool firstRun = true; firstRun; firstRun = false)
			disk->readVehiclesFromDisk(container);

		container->displayMenuVehicles();

		cout << "\n\n1) Add vehicle\n";
		cout << "2) Remove vehicle\n";
		cout << "3) Search for car\n";
		cout << "4) Search for bike\n";
		cout << "5) Sort vehicles by registration number\n";
		cout << "6) Sort by cost per day\n";
		cout << "9) Exit\n\n";

		cout << "\nPlease choose an option: ";

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
		switch (option)
		{
			case 1: container->addVehicleEntry(); break;
			case 2: container->removeVehicleEntry(); break;
			case 3: container->displayCarSearchMenu(); break;
			case 4: container->displayBikeSearchMenu(); break;
			case 5: container->sortByRegistration(); break;
			case 6: container->sortByCostDay(); break;
			case 9: container->writeContainerToDisk(); break;
		}
		ClearConsole;
	} while (option != 9);

	delete container;
	delete disk;

	return 0;
}

