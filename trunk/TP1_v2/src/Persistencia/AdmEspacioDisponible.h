/*
 * FreeSpaceManager.h
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#ifndef FREESPACEMANAGER_H_
#define FREESPACEMANAGER_H_

#include <string.h>

#include "../utils/types.h"
#include "Archivo.h"

#define PIVOTE 128
#define EMPTY 255
#define BLOCK_SIZE 5
#define HEADER_SIZE 512

class AdmEspacioDisponible {
private:
	std::string bitMap;
	Offset currentFreeSpaceBlock;
	int usedBlockCount;
	Archivo freeSpaceFile;

	void createFreeBlock();
	void saveBitMap();
	void loadBitMap(Offset offset);

public:
	AdmEspacioDisponible(std::string fileName);
	virtual ~AdmEspacioDisponible();

	void push(Offset offset);
	Offset pop() ;
	bool isBlockUsed(Offset offset);
	int getUseBlockCount();
	void deleteFile();
};

#endif /* FREESPACEMANAGER_H_ */
