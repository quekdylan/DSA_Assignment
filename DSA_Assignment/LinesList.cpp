// Done by Dylan (S10186935) and Dong Han (S10189943)

#include "LinesList.h"
#include<string>
#include<iostream>
#include <fstream>
using namespace std;


LinesList::LinesList() {}
LinesList::~LinesList() {}

// Adds a station to the list. Used in initialization only.
void LinesList::addStation(string name, string code, int distance)
{
	string lineCode = code.substr(0, 2);
	Station* station = new Station();
	station->name = name;
	station->code = code;
	station->distance = distance;
	station->interchangeStation1 = NULL;
	station->interchangeStation2 = NULL;
	station->next = NULL;
	station->previous = NULL;

	// if dictionary is empty
	if (firstLine == NULL)
	{
		Line* line = new Line();
		line->code = lineCode;
		line->next = NULL;
		line->firstStation = station;
		firstLine = line;
	}

	else {
		// Traverse through the lines
		Line* tempLine = new Line;
		tempLine = firstLine;
		while (tempLine != NULL) {
			// If in correct line
			if (tempLine->code == lineCode) {
				Station* tempStation = new Station;
				tempStation = tempLine->firstStation;
				while (tempStation->next != NULL) {
					tempStation = tempStation->next;
				}
				tempStation->next = station;
				station->previous = tempStation;
				break;
			}
			// If line does not exist
			else if (tempLine->next == NULL) {
				Line* line = new Line();
				line->code = lineCode;
				line->next = NULL;
				line->firstStation = station;
				tempLine->next = line;
				break;
			}
			tempLine = tempLine->next;

		}

	}
}

// Add a new station, creates new line if doesnt exist.
void LinesList::addNewStation(string name, string code, int firstDistance, int secondDistance)
{
	string currentCode;
	string lineCode = code.substr(0, 2);
	Station* station = new Station();
	Station* nextStation;
	station->name = name;
	station->code = code;
	station->distance = secondDistance;
	station->interchangeStation1 = NULL;
	station->interchangeStation2 = NULL;
	station->next = NULL;
	station->previous = NULL;

	// if dictionary is empty
	if (firstLine == NULL)
	{
		Line* line = new Line();
		line->code = lineCode;
		line->next = NULL;
		line->firstStation = station;
		firstLine = line;
	}

	else {
		Line* tempLine = new Line;
		tempLine = firstLine;
		string tempCode;
		string inputCode;
		inputCode = code.erase(0, 2);

		while (tempLine != NULL) {
			// if in correct line
			if (tempLine->code == lineCode) {
				Station* tempStation = new Station;
				tempStation = tempLine->firstStation;

				currentCode = tempStation->code;

				//If code number doesnt exist, assign code 0
				if (currentCode.length() > 2)
				{
					currentCode.erase(0, 2);

				}
				else
				{
					currentCode = "0";
				}

				while (tempStation->next != NULL && stoi(currentCode) + 1 < stoi(inputCode)) {
					tempStation = tempStation->next;
					currentCode = tempStation->code;
					currentCode.erase(0, 2);
				}
				nextStation = tempStation->next;
				tempStation->distance = firstDistance;
				tempStation->next = station;
				station->previous = tempStation;
				station->next = nextStation;
				break;

			}
			// if line not found
			else if (tempLine->next == NULL) {
				Line* line = new Line();
				line->code = lineCode;
				line->next = NULL;
				line->firstStation = station;
				tempLine->next = line;
				break;
			}
			tempLine = tempLine->next;

		}

	}

}
// Initialization.
// Adds station pointers to interchanges
void LinesList::addInterchanges(string file) {
	Station* tempStation = new Station();
	Line* tempLine = new Line();
	tempLine = firstLine;

	// Traverse through all stations
	while (tempLine != NULL) {
		tempStation = tempLine->firstStation;
		while (tempStation != NULL) {
			ifstream infile(file);
			string interchange1, interchange2, line;
			char delimiter = ',';
			while (getline(infile, line)) {
				string int1, int2, int3 = "";
				size_t pos = line.find(delimiter);
				int1 = line.substr(0, pos);
				line.erase(0, pos + 1);

				pos = line.find(delimiter);
				int2 = line.substr(0, pos);
				line.erase(0, pos + 1);

				//If there is a third interchange
				if (pos < 9999) {
					pos = line.find(delimiter);
					int3 = line.substr(0, pos);
				}
				if (tempStation->code == int1) {
					tempStation->interchangeStation1 = findStation(int2);
					tempStation->interchangeStation2 = findStation(int3);
					break;
				}
				if (tempStation->code == int2) {
					tempStation->interchangeStation1 = findStation(int1);
					tempStation->interchangeStation2 = findStation(int3);
					break;
				}
				if (tempStation->code == int3) {
					tempStation->interchangeStation1 = findStation(int1);
					tempStation->interchangeStation2 = findStation(int2);
					break;
				}
			}
			tempStation = tempStation->next;
		}
		tempLine = tempLine->next;
	}
}

// Return station pointer from station code
LinesList::Station* LinesList::findStation(string code) {
	Station* tempStation = new Station();
	Line* tempLine = new Line();
	tempLine = firstLine;
	while (tempLine != NULL) {
		tempStation = tempLine->firstStation;
		while (tempStation != NULL) {
			if (tempStation->code == code) {
				return tempStation;
			}
			tempStation = tempStation->next;
		}
		tempLine = tempLine->next;
	}
	return NULL;
}

//Display station information using station code
string LinesList::displayStation(string code) {
	Station* station = findStation(code);
	string output = "\nStation Information\n--------------------------------\n";
	if (station != NULL) {
		output += "Name: " + station->name + "\nCode: " + station->code;
		if (station->interchangeStation1 != NULL) {
			output += "," + station->interchangeStation1->code;
		}
		if (station->interchangeStation2 != NULL) {
			output += "," + station->interchangeStation2->code;
		}
	}
	return output;
}

//Get line a station lies on
LinesList::Line* LinesList::getLine(LinesList::Station* station) {
	string code = station->code.substr(0, 2);
	Line* tempLine = new Line();
	tempLine = firstLine;
	while (tempLine != NULL) {
		if (tempLine->code == code) {
			return tempLine;
		}
		tempLine = tempLine->next;
	}
}


//Find and display up to 3 possible routes with source and destination
string LinesList::findRoute(string src, string dest) {
	Station* source = findStation(src);
	Station* destination = findStation(dest);
	//If source or destination cannot be found
	if (source == NULL || destination == NULL) {
		return "[Error] Source or destination not found. Please try again. ";
	}
	Line* sourceLine = getLine(source);
	Line* destinationLine = getLine(destination);
	string route1 ="Route not found", route2 = "Route not found", route3 = "Route not found";
	string output = "\nRoute for " + source->name + " to " + destination->name + "\n";
	int distance1 = 0, distance2 = 0, distance3 = 0;

	//Algorithm 1
	//Search for destination along the same line
	distance1 = CalculateDistance(source, destination);
	if (CalculateDistance(source, destination) != 0) {
		route1 = source->name + "  --> " + destination->name;
		route1 += "\nDistace: " + to_string(distance1) + "\nPrice: " + CalculatePrice(distance1);
	}

	// Algorithm 2
	// Search for interchanges in source line that connects to destination line
	Station* tempStation = sourceLine->firstStation;
	while (tempStation != NULL) {
		if (tempStation->interchangeStation1 != NULL) {
			if (getLine(tempStation->interchangeStation1) == destinationLine) {
				//Calculate distance
				distance2 += CalculateDistance(source, tempStation);
				distance2 += CalculateDistance(tempStation->interchangeStation1, destination);
				route2 = source->name + "  -->  " + tempStation->name + "  -->  " + destination->name;
				route2 += "\nDistace: " + to_string(distance2) + "\nPrice: " + CalculatePrice(distance2);
				break;
			}
		}
		tempStation = tempStation->next;
	}


	// Algorithm 3
	// Search for interchanges in destination line that connects to source line
	tempStation = destinationLine->firstStation;
	while (tempStation != NULL) {
		if (tempStation->interchangeStation1 != NULL) {
			if (getLine(tempStation->interchangeStation1) == sourceLine) {
				//Calculate distance
				distance3 += CalculateDistance(source, tempStation->interchangeStation1);
				distance3 += CalculateDistance(tempStation, destination);
				route3 = source->name + "  -->  " + tempStation->name + "  -->  " + destination->name;
				route3 += "\nDistace: " + to_string(distance3) + "\nPrice: " + CalculatePrice(distance3);
				break;
			}
		}
		tempStation = tempStation->next;
	}

	output += "\nRoute 1\n" + route1 + "\n\nRoute 2\n" + route2 + "\n\nRoute 3\n" + route3;
	return(output);
}

//Calculate distance between 2 stations on the same line
int LinesList::CalculateDistance(Station* source, Station* destination) {
	int distance = 0;
	if (getLine(source) == getLine(destination)) {
		Station* tempStation = getLine(source)->firstStation;
		while (tempStation != NULL) {
			if (tempStation == source || tempStation == destination) {
				while (tempStation != NULL) {
					distance += tempStation->distance;
					tempStation = tempStation->next;
					if (tempStation == source || tempStation == destination) {
						return distance;
						break;
					}
				}
				break;
			}
			tempStation = tempStation->next;
		}
	}
	return 0;
}

//Calculate price of trip with distance using Fares.csv
string LinesList::CalculatePrice(int distance) {
	string line, price;
	ifstream infile("Fares.csv");
	while (getline(infile, line)) {
		char delimiter = ',';
		size_t pos = line.find(delimiter);
		if (stoi(line.substr(0, pos)) * 1000 > distance) {
			break;
		}
		line.erase(0, pos + 1);
		price = line;
	}
	return price;
}

//Prints the output for Routes.csv
string LinesList::print() {
	Station* tempStation = new Station();
	Line* tempLine = new Line();
	string output;
	int count = 0;
	tempLine = firstLine;
	while (tempLine != NULL) {
		tempStation = tempLine->firstStation;
		while (tempStation != NULL && count < 2) {
			while (tempStation != NULL && count == 0)
			{
				if (tempStation->next == NULL)
				{
					output += tempStation->code + "\n";
				}
				if (tempStation->next != NULL)
				{
					output += tempStation->code + ",";

				}
				tempStation = tempStation->next;
			}
			count++;
			tempStation = tempLine->firstStation;

			while (tempStation != NULL && count == 1)
			{
				if (tempStation->next == NULL)
				{
					output += to_string(tempStation->distance) + "\n";
				}
				if (tempStation->next != NULL)
				{
					output += to_string(tempStation->distance) + ",";

				}
				tempStation = tempStation->next;
			}

			count++;

		}
		count = 0;
		tempLine = tempLine->next;
	}
	return output;
}

//Prints the output for Stations.csv
string LinesList::printStation()
{
	Station* tempStation = new Station();
	Line* tempLine = new Line();
	string output;
	tempLine = firstLine;
	while (tempLine != NULL) {
		tempStation = tempLine->firstStation;
		while (tempStation != NULL) {
			output += tempStation->code + ", " + tempStation->name + "\n";
			tempStation = tempStation->next;
		}	
		tempLine = tempLine->next;
	}
	return output;

}



