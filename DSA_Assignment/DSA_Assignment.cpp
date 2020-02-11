	// Done by Dylan (S10186935) and Dong Han (S10189943)

	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <string>
	using namespace std;
	#include "Dictionary.h"
	#include "LinesList.h"
	//Methods
	void displayMenu();

	int main() {

		//Startup
		Dictionary stationCodes;
		Dictionary stationNames;
		LinesList stations;

		//Station Excel File
		ifstream infile("Stations.csv");
		string line;
		string station_code, station;
		while (getline(infile, line)) {
			char delimiter = ',';
			for (int i = 0; i < 2; i++) {
				size_t pos = line.find(delimiter);
				string token = line.substr(0, pos);
				if (i == 0) {
					station_code = token;
				}
				if (i == 1) {
					station = token;
					stationNames.add(station, station_code);
					stationCodes.add(station_code, station);
				}
				line.erase(0, pos + 1);
			}
		}

		//Routes Excel File
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
					string station = stationCodes.get(station_code);
			
					//if last station
					if (pos1 > 9999) {
						stations.addStation(station, station_code, NULL);
						break;
					}
					int distance = stoi(line.substr(0, pos2));
					stations.addStation(station, station_code, distance);
					prevLine.erase(0, pos1 + 1);
					line.erase(0, pos2 + 1);
				}
				prevLine = "none";
			}
		}
	

		//Interchange
		stations.addInterchanges("Interchanges.csv");

		//cout << stations.print();
	
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
				cout << "The stations for " << input << " are: \n" << stationCodes.getline(input);

				continue;
			}
			// Display station information for a given station name
			if (choice == 2) {			
				string input;
				cout << "Please enter station name: ";
				cin.ignore(); 
				getline(cin, input);
				string stationCode = stationNames.get(input);
				if (stationCode == "") {
					cout << "[Error] Station not found";
					continue;
				}
				cout << stations.displayStation(stationCode);
				continue;
			}

			if (choice == 3) {
				//stationCodes.print();
				cout << "Please enter station name that you would like to add: ";
				string name; 
				cin.ignore(); 
				getline(cin, name);

				cout << "Please enter the station code: ";
				string code;
				cin >> code;

				cout << "Please enter the first distance: ";
				int firstDistance;
				cin >> firstDistance;

				cout << "Please enter the second distance: ";
				int secondDistance;
				cin >> secondDistance;

				if ((stationCodes.add(code, name)) == false){
					cout << "Station code is already in the data base, please try again" << endl;
				}
				else {
					stations.addNewStation(name, code, firstDistance, secondDistance);
					cout << "Station has been successfully added" << endl;
					string output;

					//print station code, name
					output = stations.printStation();
					cout << output;

					//print to Stations.csv
					ofstream  myFile;
					myFile.open("Stations.csv");
					myFile << output;
					myFile.close();

					//print line \n distance
					output = stations.print();
					cout << output;

					//print to Routes.csv
					ofstream  myFile2;
					myFile2.open("Routes.csv");
					myFile2 << output;
					myFile2.close();
				}

				continue;

			}
			// Find and display a route and its price, given the source and destination stations
			if (choice == 4) {
				cout << "Please enter source station code: ";
				string src;
				cin >> src;
				cout << "Please enter destination station code: ";
				string dest;
				cin >> dest;
				cout << stations.findRoute(src, dest);
				continue;
			}

			if (choice == 0) {
				break;
			}
			else {
				cout << "Invalid option. Please try again." << endl;
			}
		}
	}

	void displayMenu()
	{
		cout << endl;
		cout << "\nMenu \n";
		cout << "--------------------------------\n";
		cout << "[1] Display stations\n";
		cout << "[2] Search station \n";
		cout << "[3] Add station \n";
		cout << "[4] Find Route \n";
		cout << "[0] Exit \n";
		cout << "--------------------------------\n";
		cout << "Enter option : ";
	}
