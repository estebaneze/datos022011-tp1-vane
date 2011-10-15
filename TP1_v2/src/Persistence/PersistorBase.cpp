/*
 * PersistorBase.cpp
 *
 *  Created on: 16/04/2010
 *      Author: sergio
 */

#include "PersistorBase.h"
#include <iostream>

PersistorBase::PersistorBase() {}

PersistorBase::PersistorBase(std::string fileName, BlockSize size) {

	/* Validaci�n de que este iniciado */
	if(fileName.length() == 0 || size == 0)
		throw new PersistExceptions::PersistorNotInitializedException();

	/* Abre el archivo para lectura - escritura binario */
	this->archivo.open(fileName.c_str(), std::ios::in|std::ios::out|std::ios::binary);
	this->blockSize = size;
	this->fileName = fileName;

	if (!this->archivo.is_open()){
		this->archivo.clear();
		this->newFile(fileName);
	}

    /* Levanta el bloque header */
    char charBuffer[HEADER_SIZE];
    this->archivo.read(charBuffer,HEADER_SIZE);

    BlockSize test;
    memcpy(&test, &charBuffer,sizeof(BlockSize));

    if (test != size)
		throw new PersistExceptions::WrongBlockSize();

    freeSpaceManager = new FreeSpaceManager(fileName + ".fs");
}

PersistorBase::~PersistorBase() {
	this->archivo.close();

	delete freeSpaceManager;
}

void PersistorBase::newFile(std::string fileName) {
	/* crea el archivo */
	archivo.open(fileName.c_str(), std::ios::out | std::ios::binary);
	archivo.close();

	/* reabre el archivo para lectura - escritura binario */
	archivo.open(fileName.c_str(), std::ios::in|std::ios::out|std::ios::binary);

	/* verifica que haya podido crear el archivo
	 * de caso contrario arroja una excepción */
	if (!archivo.is_open())
		throw new PersistExceptions::FileNotFoundexception();


	/* Se inicializa el header del archivo. */
	std::string buffer = "";
	buffer.append((char*)&this->blockSize,sizeof(BlockSize));
	buffer.append(HEADER_SIZE-sizeof(BlockSize),'\0');

	/* Se escribe el archivo */
	this->archivo.write(buffer.c_str(),HEADER_SIZE);
	this->archivo.flush();

	this->archivo.seekg(0,std::ios::beg);
}

void PersistorBase::add(Block* block) {
	Offset offset = -1;

	offset = freeSpaceManager->pop();
	block->setOffset(offset);

	this->modify(block);
}


void PersistorBase::modify(Block* block) {
    /**
     * verifica que el archivo esta abierto y
     * arroja una excepcion si no lo esta.
     * */
    if ( ! this->archivo.is_open())
    	throw new PersistExceptions::FileNotFoundexception();

    /* Se Posiciona en en inicio del Block */
	archivo.seekg((block->getOffset() * blockSize) + HEADER_SIZE);

	/* Obtiene la serializacion y la escibe en el archivo*/
	std::string buffer = block->serialize();

	buffer.append(blockSize - buffer.length(),'0');


	this->archivo.write(buffer.c_str(),blockSize);
	this->archivo.flush();

	/* chequea si se ha producido un error
	 * arroja una excepción ante la imposibilidad de escribir el reg */
	if (this->archivo.fail())
		throw new PersistExceptions::FailFileWriteException();
}

void PersistorBase::load(Offset key, Block* block) {
	std::string temp = this->load(key);
	block->unserialize(temp);
	block->setOffset(key);
}

std::string PersistorBase::load(Offset key) {
    /**
     * verifica que el archivo esta abierto y
     * arroja una excepcion si no lo esta.
     * */
	if ( ! this->archivo.is_open())
		throw new PersistExceptions::FileNotFoundexception();

	/* Se Posiciona en en inicio del Block */
	if (!freeSpaceManager->isBlockUsed(key)) throw new PersistExceptions::ElementNotFoundException();

	archivo.seekg((key * blockSize) + HEADER_SIZE);

	/* Levanta el bloque en un string*/
	char* charBuffer= new char[blockSize];
	this->archivo.read(charBuffer,blockSize);

	/* Pasa el charBuffer a un string buffer */
	std::string buffer(charBuffer,blockSize);

	delete[] charBuffer;
	return buffer;
}

void PersistorBase::removeBlock(Offset offset) {
	freeSpaceManager->push(offset);
}

void PersistorBase::deleteFile() {
	/* Se limpian los flags y se cierra el archivo*/
	archivo.clear();
	archivo.close();

	/* Se elimina el archivo actual */
	remove(this->fileName.c_str());
	this->freeSpaceManager->deleteFile();
}

void PersistorBase::empty() {
	this->deleteFile();
	this->newFile(this->fileName);
}

unsigned int PersistorBase::size() {
	unsigned int posActual = archivo.tellg();
	archivo.seekg(0, std::ios::end);
	unsigned int result = archivo.tellg();
	archivo.seekg(posActual, std::ios::beg);
	return result;
}

unsigned int PersistorBase::blocks() {
	//return ( (this->size()- HEADER_SIZE) / this->blockSize);
	return this->freeSpaceManager->getUseBlockCount();
}
