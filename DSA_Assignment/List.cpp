// List.cpp - Implementation of List ADT using Array
#include "List.h"  // header file

// constructor
List::List() { size = 0; }

// add an item to the back of the list (append)
bool List::add(ItemType item)
{
	bool success = size < MAX_SIZE;
	if (success)
	{
		people[size] = item;    // add to the end of the list
		size++;                // increase the size by 1
	}
	return success;
}

// add an item at a specified position in the list (insert)
bool List::add(int index, ItemType item)
{
	bool success = (index >= 0) && (index <= size) && (size < MAX_SIZE);
	if (success)
	{  // make room for the item by shifting all people at
	   // positions >= index toward the end of the
	   // List (no shift if index == size + 1)
		for (int pos = size; pos > index; pos--)
			people[pos] = people[pos - 1];
		// insert the item
		people[index] = item;
		size++;  // increase the size by 1
	}
	return success;
}

// remove an item at a specified position in the list
void List::remove(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
	{  // delete item by shifting all people at positions >
	   // index toward the beginning of the list
	   // (no shift if index == size)
		for (int pos = index; pos < size; pos++)
			people[pos] = people[pos + 1];
		size--;  // decrease the size by 1
	}

}

// get an item at a specified position of the list (retrieve)
ItemType List::get(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
		return people[index];
}

// check if the list is empty
bool List::isEmpty() { return size == 0; }

// check the size of the list
int List::getLength() { return size; }

// display the people in the list
void List::print()
{
	for (int i = 0; i < size; i++) {
		cout << people[i].getName() << "\t" << people[i].getNumber() << endl;
	}
}

// replace the  item in the specified index in the list
void List::replace(int index, ItemType item)
{
	bool success = (index >= 0) && (index < size);
	if (success)
		people[index] = item;
}