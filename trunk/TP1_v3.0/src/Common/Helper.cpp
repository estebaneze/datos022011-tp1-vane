/*
 * Helper.cpp
 *
 *  Created on: 09/10/2011
 *      Author: minnie
 */

#include "Helper.h"

string Helper::FloatToString(float value){

	std::stringstream out;
	out << value;
	return out.str();
}

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

	for(unsigned int i = 0; i < values.size(); i++){

		aux.append(values[i]);
		if(i < values.size() - 1)	//Si no estoy en el ultimo valor a concatenar
			aux.append(delimitador);
	}

	return aux;

}

string Helper::concatenar(vector<int> values, string delimitador){

	string aux;

	for(unsigned int i = 0; i < values.size(); i++){

		aux.append(Helper::IntToString(values[i]));
		if(i < values.size() - 1)	//Si no estoy en el ultimo valor a concatenar
			aux.append(delimitador);
	}

	return aux;

}

string Helper::concatenar(string value1,string value2, string delimitador){

	string aux;
	aux.append(value1);
	aux.append(delimitador);
	aux.append(value2);

	return aux;

}

string Helper::copyBytesToString(int valor){

	string data="";
	char c_int[4];
	memcpy((void*)c_int,(void*)&valor,4);

	for (int i=0;i<4;i++){

		/*if(c_int[i] == '\0')
			cout << "c_int[i] " << " - es null" << endl;
		else
			cout << "c_int[i] " << c_int[i] << endl;*/
		data.append(1,c_int[i]);
	}

	return data;

}




string Helper::copyBytesToString(long valor){

	string data;
	data.clear();
	char* c_long = new char[sizeof(valor)];
	memcpy((void*)c_long,(void*)&valor,sizeof(valor));


	for (int i=0;i<4;i++){
		data.append(1,c_long[i]);
	}

	//	cout << "data long size" << data.size() << endl;
		//descomentar para probar
		/*cout << "id eleccion (char): " << data.c_str() << endl;

		int res=0;
	   	memcpy((void*)&res,(void*)data.c_str(),sizeof(int));

	   	cout << "id eleccion (int): " << res << endl;*/
		delete c_long;

		return data;

}


int Helper::copyBytesToInt(string valor){

	int res=0;
	memcpy((void*)&res,(void*)valor.c_str(),sizeof(int));

	return res;


}


long Helper::copyBytesToLong(string valor){

	long res=0;
	memcpy((void*)&res,(void*)valor.c_str(),sizeof(long));

	return res;


}
