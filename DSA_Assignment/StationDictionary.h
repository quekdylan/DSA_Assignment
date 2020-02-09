#pragma once
// Dictionary.h - - Specification of Dictionary ADT

#include<string>
#include<iostream>
using namespace std;

typedef string ItemType;
typedef string KeyType;

class StationDictionary
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
	StationDictionary();

	// destructor
	~StationDictionary();

	// add a new item with the specified key to the Dictionary
	void addStation(string name, string code, int distance);

	void addInterchanges(string file);

	Station* findStation(string code);

	string findRoute(string src, string dest);

	Line* getLine(Station* station);

	string print();
};
