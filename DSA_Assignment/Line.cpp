#include "Line.h"

Line::Line() { size = 0; }

Line::~Line() { }

bool Line::add(int code) {

	Station* newStation = new Station;
	newStation->code = code;
	newStation->next = NULL;

	if (size == 0) {
		firstStation = newStation;
	}

	else {
		Station* traverseStation = firstStation;
		for (int i = 0; i < size - 1; i++) {
			traverseStation = traverseStation->next;
		}
		traverseStation->next = newStation;
	}
	size++;
	return true;
}

string Line::get(int index) {
	if (index >= 0 && index < size) {
		Station* traverseStation = new Station;
		for (int i = 0; i < index - 1; i++) {
			traverseStation = traverseStation->next;
		}
		return traverseStation->code;
	}
}

bool Line::isEmpty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

int Line::getLength() {
	return size;
}

void Line::print() {
	Station* traverseStation = firstStation;
	while (traverseStation != NULL) {
		cout << traverseStation->code << "\t";
		traverseStation = traverseStation->next;
	}
	cout << endl;
}