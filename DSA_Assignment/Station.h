#pragma once
using namespace std;
#include <iostream>

class station
{
private:
	string name;
	int phoneNumber;

public:
	station();
	station(string n, int no);

	void setName(string n);
	string getName();

	void setPhoneNumber(int no);
	int getPhoneNumber();

};

