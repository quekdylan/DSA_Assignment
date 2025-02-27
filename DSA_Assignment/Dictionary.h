// Done by Dylan (S10186935) and Dong Han (S10189943)
#pragma once

#include<string>
#include<iostream>
using namespace std;

const int MAX_SIZE = 20;
typedef string ItemType;
typedef string KeyType;

class Dictionary
{
private:
	struct Node
	{
		KeyType  key;   // search key
		ItemType item;	// data item
		Node* next;		// pointer pointing to next item
	};

	Node* items[MAX_SIZE];
	int  size;			// number of items in the Dictionary

public:
	// constructor
	Dictionary();

	// destructor
	~Dictionary();

	int hash(KeyType key);

	// add a new item with the specified key to the Dictionary
	bool add(KeyType newKey, ItemType newItem);

	// remove an item with the specified key in the Dictionary
	void remove(KeyType key);

	// get an item with the specified key in the Dictionary (retrieve)
	ItemType get(KeyType key);

	// get an item with the specified key in the Dictionary (retrieve)
	ItemType getline(KeyType key);

	// check if the Dictionary is empty
	bool isEmpty();

	// check the size of the Dictionary
	int getLength();

	//------------------- Other useful functions -----------------
	// display the items in the Dictionary
	void print();

	// displays the keys in the Dictionary, in this case the station codes
	void printCodes();
};
