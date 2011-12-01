/*
 * DirectoryRSA.cpp
 *
 *  Created on: 29/11/2011
 *      Author: loo
 */

#include "DirectoryRSA.h"

DirectoryRSA::DirectoryRSA(string dirfile, unsigned int maxBucketSize) {
	    this->depth = 0;
		this->maxBucketSize = maxBucketSize;
		this->insertionSizeLimit = 0.80;

		// Abro o creo los archivos de Tabla y Buckets
		string tmp = dirfile;
		tmp.append(".dir");
		this->directoryFile = new PersistorBaseRSA(tmp,BUFFERTABLE);
		this->bucketFile = new PersistorBaseRSA(dirfile.append(".bk"),maxBucketSize);

		//Creo instancias de Tabla y Bucket vacios para trabajar.
		this->tabla = new Table();
		this->bucketActual = new Bucket (maxBucketSize);
		this->bucketActual->setInsertionSizeLimit(this->insertionSizeLimit);

		// si no hay bloques en el archivo agrego un bucket vacio.
		if (bucketFile->blocks() == 0)
			bucketFile->add(bucketActual);

		// Inserto la primer posicion en la Tabla
		this->tabla->insert(bucketActual->getOffset(),0,0);
		// si no hay bloques en el archivo agrego el inicio de una nueva Tabla.
		if (directoryFile->blocks() > 0)
			 directoryFile->load(0,tabla);
		else directoryFile->add(tabla);

		this->setDepth();
}

PersistorBase* DirectoryRSA::GetDirectoryFile(){
	return this->directoryFile;
}

PersistorBase* DirectoryRSA::GetBucketFile(){
	return this->bucketFile;
}

void DirectoryRSA::Destroy(){
	cout << "DirectoryRSA::Destroy" << endl;
	// Borrar instancias de elementos utilizados.
	delete this->directoryFile;
	delete this->bucketFile;
    delete this->tabla;
    delete this->bucketActual;
}

DirectoryRSA::~DirectoryRSA() {
	Destroy();
}
