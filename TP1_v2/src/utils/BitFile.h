/*
 * BitFile.h
 *
 *  Created on: 26/06/2010
 *      Author: daniel
 */

#ifndef BITFILE_H_
#define BITFILE_H_

#include <iostream>

class BitFile {
private:
    std::istream * input;
    std::ostream * output;
    unsigned char bitBuffer;
    unsigned char bitCount;

    unsigned long bytesCounter;

public:
    enum Mode {READ,WRITE};
	BitFile(std::istream * input,std::ostream * output,Mode mode);
	virtual ~BitFile();

	unsigned long getBytesCounter();
	int getBit();
	int setBit(short int c);

	void closeFile();

};

#endif /* BITFILE_H_ */
