/*
 * DirectoryRSA.h
 *
 *  Created on: 29/11/2011
 *      Author: loo
 */

#ifndef DIRECTORYRSA_H_
#define DIRECTORYRSA_H_

#include "Directory.h"
#include "../Persistencia/PersistorBaseRSA.h"	//External

class DirectoryRSA: public Directory {
private:
	PersistorBaseRSA* directoryFile;
	PersistorBaseRSA* bucketFile;

public:
	DirectoryRSA(string, unsigned int);
	virtual ~DirectoryRSA();
};

#endif /* DIRECTORYRSA_H_ */
