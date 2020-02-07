#include<string>
#include<iostream>
using namespace std;

#include "StationDictionary.h"

StationDictionary::StationDictionary() {}

StationDictionary::~StationDictionary() {}


void StationDictionary:: addStation(string code, int distance)
{
	string lineCode = code.substr(0, 2);
	Station* station = new Station();
	station->code = code;
	station->distance = distance;
	//station->interchangeStation1 = interchangeStation1;
	//station->interchangeStation2 = interchangeStation2;
	station->next = NULL;

	// if dictionary is empty
	if (stations == NULL)
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
			}
			// if line not found
			else if (tempLine->next == NULL) {
				Line* line = new Line();
				line->code = lineCode;
				line->next = NULL;
				line->firstStation = station;
				cout << lineCode;
			}
			else {
				tempLine->next;
			}
		}

	}
}




