//A header file with the enum,  so I can simply include this in other classes without code duplication.
#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>
using namespace std;

//The enum values are assigned values to represent the colour in order. The white is out of bounds as a white row does not exist.
enum Colour { WHITE = 4, RED = 0, YELLOW = 1, GREEN = 2, BLUE =3 };


inline ostream& operator<<(ostream& out, const Colour colour) {

	switch (colour) {
	case WHITE:
		out << "White";
		break;
	case RED:
		out << "Red";
		break;
	case BLUE:
		out << "Blue";
		break;
	case YELLOW:
		out << "Yellow";
		break;
	case GREEN:
		out << "Green";
		break;
	}
	return out;
}
#endif



