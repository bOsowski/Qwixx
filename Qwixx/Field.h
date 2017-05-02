#ifndef FIELD_H
#define FIELD_H

#include <iostream>

using namespace std;

class Field
{
private:
	short m_fieldNumber;
	bool crossedOut;
	bool possibleToCrossOut;
	friend ostream& operator<<(ostream& os, const Field& field);

public:
	Field(const short& const fieldNumber);
	~Field();
	short& getFieldNumber();
	bool isCrossedOut();
	bool isPossibleToCrossOut();
	void makeNotPossibleToCrossOut();
	void crossOut();
};

#endif