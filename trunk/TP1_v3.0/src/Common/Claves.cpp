/*
 * Claves.cpp
 *
 */

#include "Claves.h"
#include "../Persistencia/exceptions/PersistExceptions.h"

void Claves::GuardarClaves(long int n, long int e, long int d){

	Archivo archivoPublica = Archivo(ConfigurationMananger::getInstance()->getClavePublicaFile(),30);
	archivoPublica.vaciar();

	archivoPublica.escribir(Helper::LongToString(n),0);
	archivoPublica.escribir(Helper::LongToString(e),1);

	Archivo archivoPrivada = Archivo(ConfigurationMananger::getInstance()->getClavePrivadaFile(),30);
	archivoPrivada.vaciar();

	archivoPrivada.escribir(Helper::LongToString(n),0);
	archivoPrivada.escribir(Helper::LongToString(d),1);
}

long int Claves::GetClavePublicaN(){

	string fileName = ConfigurationMananger::getInstance()->getClavePublicaFile();
	if(!Archivo::exists(fileName)){
		cout << "El archivo \"" << fileName << "\" no existe" << endl;
		throw new PersistExceptions::FileNotFoundexception();
	}

	Archivo archivo = Archivo(fileName,30);
	string n = archivo.leer(0);
	return Helper::StringToLong(n);
}

long int Claves::GetClavePrivadaN(){

	string fileName = ConfigurationMananger::getInstance()->getClavePrivadaFile();
	if(!Archivo::exists(fileName)){
		cout << "El archivo \"" << fileName << "\" no existe" << endl;
		throw new PersistExceptions::FileNotFoundexception();
	}

	Archivo archivo = Archivo(ConfigurationMananger::getInstance()->getClavePrivadaFile(),30);
	string n = archivo.leer(0);
	return Helper::StringToLong(n);
}

long int Claves::GetClavePrivadaD(){

	string fileName = ConfigurationMananger::getInstance()->getClavePrivadaFile();
	if(!Archivo::exists(fileName)){
		cout << "El archivo \"" << fileName << "\" no existe" << endl;
		throw new PersistExceptions::FileNotFoundexception();
	}

	Archivo archivo = Archivo(ConfigurationMananger::getInstance()->getClavePrivadaFile(),30);
	string d = archivo.leer(1);
	return Helper::StringToLong(d);
}

long int Claves::GetClavePublicaE(){

	string fileName = ConfigurationMananger::getInstance()->getClavePublicaFile();
	if(!Archivo::exists(fileName)){
		cout << "El archivo \"" << fileName << "\" no existe" << endl;
		throw new PersistExceptions::FileNotFoundexception();
	}

	Archivo archivo = Archivo(ConfigurationMananger::getInstance()->getClavePublicaFile(),30);
	string e=archivo.leer(1);
	return Helper::StringToLong(e);
}

