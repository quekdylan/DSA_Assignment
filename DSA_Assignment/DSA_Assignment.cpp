// DSA_Assignment.cpp 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
#include "Dictionary.h"
#include"List.h"

//Methods
void displayMenu();


int main() {
	//Import 
	Dictionary stationCodes;
	Dictionary stationNames;
	List stationList;
	ifstream infile("Stations.csv");
	string line;
	string station_code, station;
	while (getline(infile, line)){
		char delimiter = ',';
		for (int i = 0; i < 2; i++){
			size_t pos = line.find(delimiter);
			string token = line.substr(0, pos);
			if(i == 0){
				station_code = token;
			}
			if(i ==1){
				station = token;
				stationNames.add(station, station_code);
				stationCodes.add(station_code, station);
			}
			line.erase(0, pos + 1);
		}
	}

	int choice = 1;
	while (true) {
		displayMenu();
		cin >> choice;

		if (choice == 1) {
			stationCodes.print();
			continue;
		}
		// Display station information for a given station name
		if (choice == 2) {							
			cout << "Please enter station name: ";
			string input;
			cin >> input; 
			cout << stationNames.get(input);
			continue;
		}

		if (choice == 3) {
			cout << "Please enter station name that you would like to add" << endl;
			string name;
			cin >> name;
			//string
			//stations.add(input);

		}

		// Find and display a route and its price, given the source and destination stations
		if (choice == 4) {
			cout << "Please enter source station name" << endl;
			string source;
			cin >> source;
			cout << "Please enter destination station name" << endl;
			string dest;
			cin >> dest;

		}

		if (choice == 0) {
			break;
		}
		else {
			cout << "Invalid option. Please try again." << endl;
		}
	}

	//chat
	//

}

void displayMenu()
{
	cout << endl;
	cout << "MRT Hub \n";
	cout << "--------------------------------\n";
	cout << "[1] Display stations\n";
	cout << "[2] Search station \n";
	cout << "[3] Add station \n";
	cout << "[4] Find Route \n";
	cout << "[0] Exit \n";
	cout << "--------------------------------\n";
	cout << "Enter option : ";
}
