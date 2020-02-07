// DSA_Assignment.cpp 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
#include "Dictionary.h"
#include "StationDictionary.h"
//Methods
void displayMenu();

int main() {

	//Startup
	Dictionary stationCodes;
	Dictionary stationNames;
	StationDictionary stations;

	ifstream infile("Stations.csv");
	string line, station_code, station, distance;

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
				stationCodes.add(station_code, station + " (" + station_code + ") ");
			}
			line.erase(0, pos + 1);
		}
	}

	ifstream infile2("Routes.csv");
	string prevLine = "none";
	while (getline(infile2, line)) {
		if (prevLine == "none") {
			prevLine = line;
		}
		else {
			char delimiter = ',';
			while (true) {
				size_t pos1 = prevLine.find(delimiter);
				size_t pos2 = line.find(delimiter);
				string station_code = prevLine.substr(0, pos1);
				//if last station
				if (pos1 > 9999) {
					break;
				}
				int distance = stoi(line.substr(0, pos2));
				stations.addStation(station_code, distance);
				prevLine.erase(0, pos1 + 1);
				line.erase(0, pos2 + 1);
			}
			prevLine = "none";
		}
	}
	
	//////////////////////////////////////////////////////////////////////////

	int choice = 1;
	while (true) {
		displayMenu();
		cin >> choice;

		if (choice == 1) {
			stationCodes.printCodes();
			cout << "Please enter the train line you would like to display: ";
			string input;
			cin >> input;
			string output;
			cout << "The stations for " << input << "are: " << stationCodes.getline(input);

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
			stationNames.print();
			cout << "Please enter station name that you would like to add: ";
			string name;
			cin >> name;
			cout << "Please enter the station code: ";
			string code;
			cin >> code;
			stationNames.add(code, name);
			stationNames.print();
			continue;

		}

		// Find and display a route and its price, given the source and destination stations
		if (choice == 4) {
			cout << "Please enter source station code: ";
			string source;
			cin >> source;
			cout << "Please enter destination station code: ";
			string dest;
			cin >> dest;
			string line = source.substr(0, 2);
			

			/*
				1. get station line
				2. find interchanges in line
				3. for each interchange in line, jump to next line
				4. if line == dest line, add route to list
				5. calculate price
			*/
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
