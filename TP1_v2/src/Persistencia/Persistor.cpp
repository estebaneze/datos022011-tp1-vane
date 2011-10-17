/*
 * Persistor.cpp
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#include "Persistor.h"

/* Atributos estaticos */
std::string 	Persistor::fileName = "";
BlockSize		Persistor::blockSize = 0;
PersistorBTree*  Persistor::instance = NULL;

PersistorBTree* Persistor::getInstance()  {
	if(Persistor::instance == NULL)
		Persistor::instance = new PersistorBTree(Persistor::fileName, Persistor::blockSize);

	return Persistor::instance;
}

void Persistor::init(std::string fileName,BlockSize size) {

	if(Persistor::instance != NULL) {
		throw new PersistExceptions::PersistorInitializedException();
	}

	Persistor::fileName = fileName;
	Persistor::blockSize = size;
}

