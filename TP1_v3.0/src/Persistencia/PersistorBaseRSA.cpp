/*
 * PersistorBaseRSA.cpp
 *
 *  Created on: 29/11/2011
 *      Author: loo
 */

#include "PersistorBaseRSA.h"

PersistorBaseRSA::PersistorBaseRSA() {
}

PersistorBaseRSA::PersistorBaseRSA(std::string fileName, BlockSize size) {

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

    admEspacioLibre = new AdmEspacioDisponible(fileName + ".fs");
}


PersistorBaseRSA::~PersistorBaseRSA() {
	// TODO Auto-generated destructor stub
}


void PersistorBaseRSA::modify(Block* block) {
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

	this->archivo.write(
			//RSA::encriptar(const_cast<char *>(buffer.c_str())),
			RSA::encriptar((char*)buffer.c_str()),
			//buffer.c_str(),
			blockSize);

	this->archivo.flush();

	/* chequea si se ha producido un error
	 * arroja una excepción ante la imposibilidad de escribir el reg */
	if (this->archivo.fail())
		throw new PersistExceptions::FailFileWriteException();
}


std::string PersistorBaseRSA::load(Offset key) {
    /**
     * verifica que el archivo esta abierto y
     * arroja una excepcion si no lo esta.
     * */
	if ( ! this->archivo.is_open())
		throw new PersistExceptions::FileNotFoundexception();

	/* Se Posiciona en en inicio del Block */
	if (!admEspacioLibre->isBlockUsed(key)) throw new PersistExceptions::ElementNotFoundException();

	archivo.seekg((key * blockSize) + HEADER_SIZE);

	/* Levanta el bloque en un string*/
	char* charBufferEnc= new char[blockSize];
	char* charBuffer= new char[blockSize];
	this->archivo.read(charBufferEnc,blockSize);

	charBuffer = RSA::desencriptar(charBufferEnc);

	/* Pasa el charBuffer a un string buffer */
	std::string buffer(charBuffer,blockSize);

	delete[] charBuffer;
	//cout << buffer.c_str() << endl;
	return buffer;
}

void PersistorBaseRSA::load(Offset key, Block* block) {
	std::string temp = this->load(key);
	block->unserialize(temp);
	block->setOffset(key);
}
