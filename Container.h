#pragma once

#include "Vehicle.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Container
{
	class CompareByReg {
		public:
			bool operator() (shared_ptr<Vehicle> a, shared_ptr<Vehicle> b)
			{
				return a->getVehicleReg() < b->getVehicleReg();
			}
	};
	class CompareByCost {
		public:
			bool operator() (shared_ptr<Vehicle> a, shared_ptr<Vehicle> b)
			{
				return a->calculateCostPerDay() < b->calculateCostPerDay();
			}
	};

	public:
		Container();
		~Container();
		bool checkVehicleRegExists(string vehicleReg);
		bool checkVehicleRegFormat(string vehicleReg);
		void addVehicleEntry();
		void removeVehicleEntry();
		void removeFile(string fileName);
		void searchRegistration(string vehicleType, string vehicleReg);
		void searchVehicleCriteria(string vehicleType, string vehicleCriteria, int value);
		void chooseVehicle();
		void displayCarSearchMenu();
		void displayBikeSearchMenu();
		void displaySearchVehicles(string vehicleType, string vehicleReg);
		void displaySearchVehicles(string vehicleType, string vehicleCriteria, int value);
		void displayMenuVehicles();
		void writeContainerToDisk();
		void sortByRegistration();
		void sortByCostDay();
		void clearVehicleMap();
		void addItem(shared_ptr<Vehicle>);
		void removeItem(string vehicleReg);
		void shuffleItems();
		void displaySearchTitle();

	private:
		vector<shared_ptr<Vehicle>> allVehicles;
		map<int, shared_ptr<Vehicle>> vehicleMap;
		bool returnToMenu;
};

inline void Container::sortByRegistration() { sort(allVehicles.begin(), allVehicles.end(), CompareByReg()); }
inline void Container::sortByCostDay() { sort(allVehicles.begin(), allVehicles.end(), CompareByCost()); }
inline void Container::clearVehicleMap() { vehicleMap.clear(); }
inline void Container::addItem(shared_ptr<Vehicle> vehicle) { allVehicles.push_back(std::move(vehicle)); }
inline void Container::removeItem(string vehicleReg) { allVehicles.erase(remove_if(allVehicles.begin(), allVehicles.end(), [&vehicleReg](shared_ptr<Vehicle> reg) {return reg->getVehicleReg() == vehicleReg;}), allVehicles.end()); }
inline void Container::shuffleItems() { random_shuffle(allVehicles.begin(), allVehicles.end()); }

inline void Container::displaySearchTitle() {
	cout << "\n   Registration Number     Cost Per Day      Make      Model\n";
	cout << "   -------------------     ------------      ----      -----\n";
}

