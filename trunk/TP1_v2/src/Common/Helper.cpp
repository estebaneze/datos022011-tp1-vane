/*
 * Helper.cpp
 *
 *  Created on: 09/10/2011
 *      Author: minnie
 */

#include "Helper.h"

string Helper::IntToString(int value){

	std::stringstream out;
	out << value;
	return out.str();
}

int Helper::StringToInt(string value){

	istringstream buffer(value);
	int valueInt;
	buffer >> valueInt;

	return valueInt;


}
