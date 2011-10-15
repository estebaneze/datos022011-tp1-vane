/*
 * PersistorBase.h
 *
 *  Created on: 16/04/2010
 *      Author: sergio
 */

#ifndef PERSISTORBASE_H_
#define PERSISTORBASE_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "../utils/types.h"
#include "Block.h"
#include "FreeSpaceManager.h"
#include "exceptions/PersistExceptions.h"

#define HEADER_SIZE 512

class PersistorBase {
protected:
	std::fstream  archivo;
	BlockSize	blockSize;
	FreeSpaceManager*	freeSpaceManager;
	std::string fileName;

	virtual void newFile(std::string fileName) ;
	unsigned int size();

public:
	PersistorBase();
	PersistorBase(std::string fileName, BlockSize size) ;
	virtual ~PersistorBase();

	void modify(Block* block) ;
	void load(Offset key, Block* block) ;
	std::string load(Offset key) ;
	void add(Block* block);
	void removeBlock(Offset offset);
	void deleteFile();
	void empty() ;
	unsigned int blocks();

};

#endif /* PERSISTORBASE_H_ */
