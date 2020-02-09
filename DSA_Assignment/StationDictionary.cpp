#include<string>
#include<iostream>
#include <fstream>
using namespace std;

#include "StationDictionary.h"

StationDictionary::StationDictionary() {}

StationDictionary::~StationDictionary() {}


void StationDictionary:: addStation(string name, string code, int distance)
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
		Line* tempLine = new Line;
		tempLine = firstLine;
		while (tempLine != NULL) {
			// if in correct line
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
void StationDictionary::addInterchanges(string file) {
	Station* tempStation = new Station();
	Line* tempLine = new Line();
	tempLine = firstLine;

	while (tempLine != NULL) {
		tempStation = tempLine->firstStation;
		while (tempStation != NULL) {
			ifstream infile(file);
			string interchange1, interchange2, line;
			string int1, int2, int3 = "";
			char delimiter = ',';
			while (getline(infile, line)) {
				size_t pos = line.find(delimiter);
				int1 = line.substr(0, pos);
				line.erase(0, pos + 1);

				pos = line.find(delimiter);
				int2 = line.substr(0, pos);
				line.erase(0, pos + 1);
				
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
StationDictionary::Station* StationDictionary::findStation(string code) {
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

StationDictionary::Line* StationDictionary::getLine(StationDictionary::Station* station) {
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



string StationDictionary::findRoute(string src, string dest) {
	Station* source = findStation(src);
	Station* destinaion = findStation(dest);
	Line* sourceLine = getLine(source);
	Line* destinationLine = getLine(destinaion);
	string output = "Error";

	Station* tempStation = sourceLine->firstStation;
	while (tempStation != NULL) {
		if (tempStation->interchangeStation1 != NULL && getLine(tempStation->interchangeStation1) == destinationLine) {
			output = "Route for " + source->name + " to " + destinaion->name + "\nChange at " + tempStation->name;
		}
		tempStation = tempStation->next;
	}
	return(output);
}

string StationDictionary::print() {
	Station* tempStation = new Station();
	Line* tempLine = new Line();
	string output;
	tempLine = firstLine;
	while (tempLine != NULL) {
		tempStation = tempLine->firstStation;
		while (tempStation != NULL) {
			output += tempStation->name + "," + std::to_string(tempStation->distance) + "\n";
			tempStation = tempStation->next;
		}
		tempLine = tempLine->next;
	}
	return output;
}


