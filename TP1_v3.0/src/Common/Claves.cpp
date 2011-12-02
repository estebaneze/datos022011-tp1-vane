/*
 * Identities.cpp
 *
 */

#include "Claves.h"

void Claves::GuardarClaves(long int n, long int e, long int d){

	Archivo archivo = Archivo(ConfigurationMananger::getInstance()->getClavesFile(),30);
	archivo.vaciar();
	archivo.escribir(Helper::LongToString(n),0);
	archivo.escribir(Helper::LongToString(e),1);
	archivo.escribir(Helper::LongToString(d),2);
}


long int Claves::GetN(){
	Archivo archivo = Archivo(ConfigurationMananger::getInstance()->getClavesFile(),30);
	string n=archivo.leer(0);
	return Helper::StringToLong(n);
}

long int Claves::GetD(){
	Archivo archivo = Archivo(ConfigurationMananger::getInstance()->getClavesFile(),30);
	string d=archivo.leer(2);
	return Helper::StringToLong(d);
}

long int Claves::GetE(){
	Archivo archivo = Archivo(ConfigurationMananger::getInstance()->getClavesFile(),30);
	string e=archivo.leer(1);
	return Helper::StringToLong(e);
}

