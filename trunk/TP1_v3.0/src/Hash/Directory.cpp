/*
 * directorio.cpp
 *
 */

#include "Directory.h"
#include "HashExceptions.h"
#include <assert.h>
#include <iostream>
#include <set>
#include <map>
#include "../Logging/Log.h"
#include "../Common/Common.h"

/**
 * Setea el archivo de Directorio y de Buckets
 * */

Directory::Directory(){

}

Directory::Directory(string dirfile, unsigned int maxBucketSize){

      this->depth = 0;
      this->maxBucketSize = maxBucketSize;
      this->insertionSizeLimit = 0.80;

      // Abro o creo los archivos de Tabla y Buckets
      string tmp = dirfile;
      tmp.append(".dir");
      this->directoryFile = new PersistorBase(tmp,BUFFERTABLE);
      this->bucketFile = new PersistorBase(dirfile.append(".bk"),maxBucketSize);

      //Creo instancias de Tabla y Bucket vacios para trabajar.
      this->tabla = new Table();
      this->bucketActual = new Bucket (maxBucketSize);
      this->bucketActual->setInsertionSizeLimit(this->insertionSizeLimit);

      // si no hay bloques en el archivo agrego un bucket vacio.
      if (GetBucketFile()->blocks() == 0)
	      GetBucketFile()->add(bucketActual);

      // Inserto la primer posicion en la Tabla
      this->tabla->insert(bucketActual->getOffset(),0,0);
      // si no hay bloques en el archivo agrego el inicio de una nueva Tabla.
      if (GetDirectoryFile()->blocks() > 0)
		GetDirectoryFile()->load(0,tabla);
      else GetDirectoryFile()->add(tabla);

      this->setDepth();
}

Directory::~Directory(){

	delete this->directoryFile;
	delete this->bucketFile;
    delete this->tabla;
    delete this->bucketActual;
}


PersistorBase* Directory::GetDirectoryFile(){
	return this->directoryFile;
}

PersistorBase* Directory::GetBucketFile(){
	return this->bucketFile;
}
