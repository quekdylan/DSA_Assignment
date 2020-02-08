#include<string>
#include<iostream>
using namespace std;

#include "Dictionary.h"

Dictionary::Dictionary() {
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = NULL;
	}
	size = 0;
}

Dictionary::~Dictionary() {}

int charvalue(char c)
{
	if (isalpha(c))
	{
		if (isupper(c))
			return (int)c - (int)'A';
		else
			return (int)c - (int)'a' + 26;
	}
	else
		return -1;
}


int Dictionary::hash(KeyType key)
{
	int keyValue = 0;

	for (char& c : key)
	{
		if (isalpha(c))
		{
			keyValue += charvalue(c);
		}
	}

	return(keyValue % MAX_SIZE);

}

bool Dictionary::add(KeyType newKey, ItemType newItem)
{
	if (items[hash(newKey)] == NULL)
	{
		Node* newNode = new Node;
		//Create a new Node
		items[hash(newKey)] = newNode;
		//Store newItem in new Node
		newNode->item = newItem;
		newNode->key = newKey;
		newNode->next = NULL;
	}

	else {

		Node* tempNode = items[hash(newKey)];

		if (tempNode->key == newKey)
		{
			return false;
		}

		while (tempNode->next != NULL)
		{
			tempNode = tempNode->next;
			if (tempNode != NULL && tempNode->key == newKey)
			{
				return false;
			}
		}

		Node* newNode = new Node;
		newNode->item = newItem;
		newNode->key = newKey;
		newNode->next = NULL;
		tempNode->next = newNode;
	}
	size++;
	return true;
}



void Dictionary::remove(KeyType key)
{
	Node* newNode = items[hash(key)];
	Node* prevNode = items[hash(key)];
	if (items[hash(key)] != NULL)
	{
		if (newNode->key == key)
		{
			items[hash(key)] = NULL;
		}

		while (newNode != NULL)
		{
			if (newNode->key == key)
			{
				newNode = NULL;
				size--;
				break;
			}
			newNode = newNode->next;
		}

	}
}

ItemType Dictionary::get(KeyType key)
{
	Node* tempNode = items[hash(key)];
	while (tempNode != NULL)
	{
		if (tempNode->key == key)
		{
			return tempNode->item;
		}
		tempNode = tempNode->next;

	}
}

string Dictionary::getline(KeyType key)
{
	string stations;
	Node* tempNode = items[hash(key)];
	while (tempNode != NULL)
	{

		stations += tempNode->item;
		stations += "(" + tempNode->key + ") " + "\n";
		tempNode = tempNode->next;

	}
	return stations;
}

bool Dictionary::isEmpty()
{
	if (size == 0)
	{
		return true;
	}
	else {
		return false;
	}
}

int Dictionary::getLength() {
	return size;
}

void Dictionary::printCodes()
{
	Node* tempNode = new Node;
	for (int i = 0; i < MAX_SIZE; i++)
	{

		if (items[i] != NULL)
		{

			tempNode = items[i];
			while (tempNode != NULL)
			{
				cout << tempNode->key << "        " << endl;
				break;
			}
		}


	}
}

void Dictionary::print()
{
	Node* tempNode = new Node;
	for (int i = 0; i < MAX_SIZE; i++)
	{

		if (items[i] != NULL)
		{

			tempNode = items[i];
			while (tempNode != NULL)
			{
				cout << tempNode->item << "        " << tempNode->key << endl;
				tempNode = tempNode->next;

			}
		}
	}
}