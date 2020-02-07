#pragma once
#include<string>
#include<iostream>
using namespace std;

class Line
{
private:
	struct Station
	{
		string code;
		Station* next;
		Station* previous;
		int distance;
		Line* interchangeLine;
		Station* interchangeStation1;
		Station* interchangeStation2;
	};

	Station* firstStation;	// point to the first item
	int size;			// number of items in the list

public:
	Line();			// constructor

	~Line();		// distructor

	// add an item to the back of the list (append)
	// pre : size < MAX_SIZE
	// post: item is added to the back of the list
	//       size of list is increased by 1
	bool add(int code);

	// get an item at a specified position of the list (retrieve)
	// pre : 0 <= index < size
	// post: none
	// return the item in the specified index of the list
	string get(int index);

	// check if the list is empty
	// pre : none
	// post: none
	// return true if the list is empty; otherwise returns false
	bool isEmpty();

	// check the size of the list
	// pre : none
	// post: none
	// return the number of items in the list
	int getLength();

	//------------------- Other useful functions -----------------

	// display the items in the list
	void print();

	// void replace(int index, ItemType item);
	// int search(ItemType item);
};

