// Done by Dylan (S10186935) and Dong Han (S10189943)

#pragma once
#include<string>
#include<iostream>
using namespace std;

typedef string ItemType;
typedef string KeyType;

class LinesList
{
private:

	struct Station
	{
		string code;
		string name;
		Station* next;
		Station* previous;
		int distance;
		Station* interchangeStation1;
		Station* interchangeStation2;
	};

	struct Line {
		Line* next;
		string code;
		Station* firstStation;
	};

	Line* firstLine;

public:
	// constructor
	LinesList();

	// destructor
	~LinesList();

	// Adds a station to the list. Used in initialization only.
	void addStation(string name, string code, int distance);

	// Add a new station, creates new line if doesnt exist.
	void addNewStation(string name, string code, int firstDistance, int secondDistance);

	// Assigns interchanges to each station. Used in initialization only.
	void addInterchanges(string file);

	//Find a station using station code
	Station* findStation(string code);

	//Display station information using station code
	string displayStation(string code);

	//Find and display up to 3 possible routes with source and destination
	string findRoute(string src, string dest);

	//Get line a station lies on
	Line* getLine(Station* station);

	//Prints the output for Routes.csv
	string print();

	//Prints the output for Stations.csv
	string printStation();

	//Calculate price of trip with distance using Fares.csv
	string CalculatePrice(int distance);

	//Calculate distance between 2 stations on the same line
	int CalculateDistance(Station* source, Station* dest);
};
