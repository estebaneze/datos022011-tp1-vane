/*
 * Helper.cpp
 *
 *  Created on: 09/10/2011
 *      Author: minnie
 */

#include "Helper.h"

string Helper::LongToString(long value){

	std::stringstream out;
	out << value;
	return out.str();
}

long Helper::StringToLong(string value){

	istringstream buffer(value);
		long valueLong;
		buffer >> valueLong;

		return valueLong;
}

string Helper::IntToString(int value){

	std::stringstream out;
	out << value;
	return out.str();
}

std::vector<std::string> & Helper::split(const string &s, char delim, vector<string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Helper::split(const string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}



int Helper::StringToInt(string value){

	istringstream buffer(value);
	int valueInt;
	buffer >> valueInt;

	return valueInt;


}

string Helper::concatenar(vector<string> values, string delimitador){

	string aux;

	for(int i = 0; i < values.size(); i++){

		aux.append(values[i]);
		if(i < values.size() - 1)	//Si no estoy en el ultimo valor a concatenar
			aux.append(delimitador);
	}

	cout << "Concat: " << aux.c_str() << endl;

	return aux;

}

string Helper::concatenar(string value1,string value2, string delimitador){

	string aux;
	aux.append(value1);
	aux.append(delimitador);
	aux.append(value2);

	cout << aux.c_str() << endl;

	return aux;

}
