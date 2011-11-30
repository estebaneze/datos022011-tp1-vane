#ifndef PERSISTORBASE_H_
#define PERSISTORBASE_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "../utils/types.h"
#include "Block.h"
#include "AdmEspacioDisponible.h"
#include "exceptions/PersistExceptions.h"

#define HEADER_SIZE 512

class PersistorBase {
protected:
	std::fstream  archivo;
	BlockSize	blockSize;
	AdmEspacioDisponible*	admEspacioLibre;
	std::string fileName;

	virtual void newFile(std::string fileName) ;
	unsigned int size();

public:
	PersistorBase();
	PersistorBase(std::string fileName, BlockSize size) ;
	virtual ~PersistorBase();

	virtual void modify(Block* block) ;
	virtual void load(Offset key, Block* block) ;
	virtual std::string load(Offset key) ;
	virtual void add(Block* block);
	virtual void removeBlock(Offset offset);
	virtual void deleteFile();
	virtual void empty() ;
	virtual unsigned int blocks();

};

#endif /* PERSISTORBASE_H_ */
