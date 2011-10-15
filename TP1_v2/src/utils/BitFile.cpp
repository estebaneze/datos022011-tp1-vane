/*
 * BitFile.cpp
 *
 *  Created on: 26/06/2010
 *      Author: daniel
 */

#include "BitFile.h"
#include "../logger/Logger.h"

#include <string>

#ifndef EOF
#define EOF -1
#endif

BitFile::BitFile(std::istream * input,std::ostream * output,Mode mode) {
	this->bitBuffer = 0;
	this->bitCount = 0;
	this->bytesCounter = 0;

	this->input = NULL;
	this->output = NULL;


	if(mode == READ)
		this->input = input;

	if(mode == WRITE)
		this->output = output;
}

BitFile::~BitFile() {
	this->input = NULL;
	this->output = NULL;
}

unsigned long BitFile::getBytesCounter() {
	return bytesCounter;
}

int BitFile::getBit() {
	int returnValue;

    if (this->bitCount == 0) {
    	returnValue = input->get();
    	bytesCounter++;

		if (input->eof())
			return EOF;
	    else{
	    	bitCount = 8;
	        bitBuffer = returnValue;
	    }
	}

	bitCount--;
	returnValue = (bitBuffer) >> (bitCount);

	return (returnValue & 0x01);
}

int BitFile::setBit(short int c) {
	int returnValue = c;

	if (output == NULL) {
		return(EOF);
	}

	bitCount++;
	bitBuffer <<= 1;

	if (c != 0) {
		bitBuffer |= 1;
	}

	if (bitCount == 8) {
		bytesCounter++;

		output->put(bitBuffer);
		if (output->eof()) {
			returnValue = EOF;
		}

		bitCount = 0;
		bitBuffer = 0;
	}

	return returnValue;
}

void BitFile::closeFile() {
	if (bitCount != 0)	{
		bitBuffer <<= 8 - bitCount;
		output->put(bitBuffer);
	}
}

