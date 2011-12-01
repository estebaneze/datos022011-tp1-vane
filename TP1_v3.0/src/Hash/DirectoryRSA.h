/*
 * DirectoryRSA.h
 *
 *  Created on: 29/11/2011
 *      Author: loo
 */

#ifndef DIRECTORYRSA_H_
#define DIRECTORYRSA_H_

#include "DirectoryBase.h"
#include "../Persistencia/PersistorBaseRSA.h"	//External

class DirectoryRSA: public DirectoryBase {

	private:
		PersistorBaseRSA* directoryFile;
		PersistorBaseRSA* bucketFile;

		PersistorBase* GetDirectoryFile();
		PersistorBase* GetBucketFile();

	public:
		DirectoryRSA(string, unsigned int);
		virtual ~DirectoryRSA();
};

#endif /* DIRECTORYRSA_H_ */
