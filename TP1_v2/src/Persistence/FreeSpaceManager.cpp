/*
 * FreeSpaceManager.cpp
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#include "FreeSpaceManager.h"

FreeSpaceManager::FreeSpaceManager(std::string fileName) : freeSpaceFile(fileName,BLOCK_SIZE) {
	currentFreeSpaceBlock = 0;
	usedBlockCount = 0;

	if(freeSpaceFile.elementos() == 0) {
		createFreeBlock();
		saveBitMap();
	}

	bitMap = freeSpaceFile.leer(currentFreeSpaceBlock+HEADER_SIZE);

	std::string buffer = freeSpaceFile.leer(0);
	buffer.copy((char*)&usedBlockCount,sizeof(int));
}

FreeSpaceManager::~FreeSpaceManager() {
	saveBitMap();
}

void FreeSpaceManager::createFreeBlock() {
	bitMap = "";
	bitMap.append(BLOCK_SIZE,EMPTY);
}

void FreeSpaceManager::loadBitMap(Offset offset) {
	if(currentFreeSpaceBlock != offset)
		bitMap = freeSpaceFile.leer(offset+HEADER_SIZE);

	currentFreeSpaceBlock = offset;
}

void FreeSpaceManager::saveBitMap() {
	std::string buffer;
	buffer.append((char*)&usedBlockCount,sizeof(int));
	buffer.append(HEADER_SIZE - sizeof(int),'H');

	freeSpaceFile.escribir(buffer,0);
	freeSpaceFile.escribir(bitMap,currentFreeSpaceBlock+HEADER_SIZE);



	freeSpaceFile.flush();
}

Offset FreeSpaceManager::pop() {
	bool wasFound = false;
	int indice = 0;

	for(unsigned int i = 0; i < bitMap.length() && !wasFound; i++) {
		char byte = bitMap[i];

		for(int j = 0; j < 8 && !wasFound; j++) {
			int valor = byte & PIVOTE;

			if(valor == PIVOTE) {
				wasFound = true;
				indice = 8*i + j;

				char newByte = bitMap[i];
				newByte = newByte ^ (128>>j);

				bitMap[i] = newByte;
				//Incrementa el contador de bloques usados;
				usedBlockCount++;

				saveBitMap();
			}

			byte = byte << 1;
		}
	}

	if(!wasFound) {
		// Verifica si hay que crear un bitmap nuevo
		unsigned int posicion = currentFreeSpaceBlock + HEADER_SIZE;
		if(posicion == freeSpaceFile.elementos()-1) {
			createFreeBlock();
			freeSpaceFile.escribir(bitMap,currentFreeSpaceBlock+1+HEADER_SIZE);
		}

		currentFreeSpaceBlock++;
		bitMap = freeSpaceFile.leer(currentFreeSpaceBlock+HEADER_SIZE);

		return this->pop();
	}

	return indice + currentFreeSpaceBlock*BLOCK_SIZE*8;
}


void FreeSpaceManager::push(Offset offset){
	Offset freeSpaceBlock = offset / (BLOCK_SIZE*8);
	int indiceplusbit =  offset % (BLOCK_SIZE*8);
	int indice = indiceplusbit / 8;
	int bit = indiceplusbit % 8;

	Offset currentFSBlockTemp = currentFreeSpaceBlock;

	loadBitMap(freeSpaceBlock);

	bitMap[indice] = bitMap[indice] | (128>>bit);

	//Decremento contador de bloques usados
	usedBlockCount--;

	saveBitMap();

	if(freeSpaceBlock > currentFSBlockTemp)
		loadBitMap(currentFSBlockTemp);

}

int FreeSpaceManager::getUseBlockCount() {
	return usedBlockCount;
}

bool FreeSpaceManager::isBlockUsed(Offset offset) {
	Offset freeSpaceBlock = offset / (BLOCK_SIZE*8);

	int totalBlockSize = freeSpaceFile.size()-HEADER_SIZE;
	int maxBlockUse = totalBlockSize / BLOCK_SIZE;

	if(maxBlockUse >= freeSpaceBlock){
		std::string auxBitMap = freeSpaceFile.leer(freeSpaceBlock+HEADER_SIZE);
		int indiceplusbit =  offset % (BLOCK_SIZE*8);
		int indice = indiceplusbit / 8;
		int bit = indiceplusbit % 8;

		bool result = false;
		if ((auxBitMap[indice] & (128>>bit)) == 0)
			result = true;
		return result;
	}
	else
		return false;
}

void FreeSpaceManager::deleteFile() {
	freeSpaceFile.eliminarArchivo();
}
