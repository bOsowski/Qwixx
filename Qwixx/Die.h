#ifndef DIE_H
#define DIE_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Colour.h"

using namespace std;
class Die {

private:
	short numberOfFaces = 6;
	Colour m_colour;
	unsigned short output;
	bool m_isActive = true;

	

public:
	bool isActive();
	void setInactive();
	int getOutput();
	void throwDie();
	Colour getColour();
	Die(const Colour& const colour);
};


#endif

