#include<string>
#include<iostream>
#include <sstream>
using namespace std;

#include "StationDictionary.h"

StationDictionary::StationDictionary() {}

StationDictionary::~StationDictionary() {}


void StationDictionary::addStation(string name, string code, int distance)
{
	string lineCode = code.substr(0, 2);
	Station* station = new Station();
	station->name = name;
	station->code = code;
	station->distance = distance;
	//station->interchangeStation1 = interchangeStation1;
	//station->interchangeStation2 = interchangeStation2;
	station->next = NULL;



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