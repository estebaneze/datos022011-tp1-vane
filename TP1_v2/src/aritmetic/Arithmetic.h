/*
 * Arithmetic.h
 *
 *  Created on: 25/06/2010
 *      Author: daniel
 */

#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include <iostream>
#include <limits.h>

#include "../utils/types.h"
#include "../utils/BitFile.h"
#include "../Hash/DistributionTable.h"
#include "../logger/Logger.h"

class Arithmetic {
private:
	PrecisionInt precision;
	PrecisionInt lower;
	PrecisionInt upper;
	PrecisionInt code;

	unsigned char underflowBits;

	bool loggear;

	BitFile * bitFile;

	Logger * logger;

	void init();
	void calculateLimits(charDT symbo,DistributionTable table);
	void writeBits();
	void writeEnd();
	void readBits();

	bool isOverflow();
	bool isUnderflow();

    void log(charDT c);
    void log(std::string message);
    void normalize();

public:
    enum Mode{COMPRESS, UNCOMPRESS};

	Arithmetic(std::fstream * input,std::fstream * output, Mode mode,bool);
	virtual ~Arithmetic();

	void compress(charDT symbol, DistributionTable table);
	charDT uncompress(DistributionTable table);

	unsigned long getBytesCounter();

};

#endif /* ARITHMETIC_H_ */
