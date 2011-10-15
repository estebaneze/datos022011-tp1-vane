/*
 * Arithmetic.cpp
 *
 *  Created on: 25/06/2010
 *      Author: daniel
 */

#include "Arithmetic.h"

#include "../utils/const.h"
#include "../utils/utiles.h"

#include <bitset>

#define PRECISION           (8 * sizeof(PrecisionInt))	//16

Arithmetic::Arithmetic(std::fstream * input,std::fstream * output, Mode mode, bool log) {
	init();

	loggear = log;

	if(mode == COMPRESS)
		this->bitFile = new BitFile(NULL,output,BitFile::WRITE);

	if(mode == UNCOMPRESS) {
		this->bitFile = new BitFile(input,NULL,BitFile::READ);

		for (int i = 0; i < 16; i++) {
			code <<= 1;

	        if(bitFile->getBit() == 1)
	            code |= 1;
		}
	}
}

Arithmetic::~Arithmetic() {
	delete bitFile;
}

void Arithmetic::init() {
    lower = 0;
    upper = ~0;
    code = 0;
    underflowBits = 0;
    precision = PRECISION;

    bitFile = NULL;

    logger = Logger::getInstance();
}

void Arithmetic::compress(charDT symbol, DistributionTable table) {
	log("Caracter: ");
	log(symbol);
	log("Piso Inicial : " + Util::bitsIntToString(lower,16) + " - " + Util::uIntToString(lower));
	log("Techo Inicial: " + Util::bitsIntToString(upper,16) + " - " + Util::uIntToString(upper));

	calculateLimits(symbol,table);

	log("Piso Actual : " + Util::bitsIntToString(lower,16) + " - " + Util::uIntToString(lower));
	log("Techo Actual: " + Util::bitsIntToString(upper,16) + " - " + Util::uIntToString(upper));

	writeBits();
	if(symbol == C_EOF)
		writeEnd();
}

charDT Arithmetic::uncompress(DistributionTable table) {
	log("Code: " + Util::uIntToString(code));
	log("Piso Inicial : " + Util::bitsIntToString(lower,16) + " - " + Util::uIntToString(lower));
	log("Techo Inicial: " + Util::bitsIntToString(upper,16) + " - " + Util::uIntToString(upper));

	unsigned long range = (unsigned long)(upper - lower) + 1;
	unsigned long cumFrequency = (unsigned long)(code - lower) + 1;
				  cumFrequency = cumFrequency * (unsigned long)table.getTotalFrequency() - 1;
				  cumFrequency /= range;


	charDT symbolFound = table.getSymbolWithCumulativeFrequency((PrecisionInt)cumFrequency);
	log("Caracter: ");
	log(symbolFound);
	calculateLimits(symbolFound,table);
	log("Piso Actual : " + Util::bitsIntToString(lower,16) + " - " + Util::uIntToString(lower));
	log("Techo Actual: " + Util::bitsIntToString(upper,16) + " - " + Util::uIntToString(upper));
	readBits();

	return symbolFound;

}


void Arithmetic::calculateLimits(charDT symbol,DistributionTable table) {
	unsigned long range = (unsigned long)(upper - lower) + 1;
	unsigned long totalFrequency = table.getTotalFrequency();
	unsigned long 	symbolProb = (unsigned long)table.getCumulativeFrequency(symbol) * range;
					symbolProb /= (unsigned long)totalFrequency;

	unsigned long 	prevSymbolProb = (unsigned long)table.getCumulativePreviousCharacterFrequency(symbol) * range;
					prevSymbolProb /= (unsigned long)totalFrequency;


	upper = lower + (PrecisionInt)symbolProb - 1;
	lower = lower + (PrecisionInt)prevSymbolProb;
}


void Arithmetic::writeBits() {
    while(true){
        if (isOverflow()) {
			bitFile->setBit((upper & Util::maskBit(precision,0)) != 0);
            while (underflowBits > 0) {
            	bitFile->setBit((upper & Util::maskBit(precision,0)) == 0);
            	underflowBits--;
            }
        }
        else if (isUnderflow()) {
            underflowBits += 1;
            lower &= ~(Util::maskBit(precision,0) | Util::maskBit(precision,1));
            upper |= Util::maskBit(precision,1);
        }
        else {
            return ;
        }
        lower <<= 1;
        upper <<= 1;
        upper |= 1;
    }
}

void Arithmetic::writeEnd() {
    bitFile->setBit((lower & Util::maskBit(precision,1)) != 0);

    for (underflowBits++; underflowBits > 0; underflowBits--) {
        bitFile->setBit((lower & Util::maskBit(precision,1)) == 0);
    }

    bitFile->closeFile();
}

void Arithmetic::normalize()
{
	int nextBit=0;
    lower <<= 1;
    upper <<= 1;
    upper |= 1;
    code <<= 1;
    if ((nextBit = bitFile->getBit()) == EOF) {
    	code = EOF;
	}
	else {
		code |= nextBit;
	}
}

void Arithmetic::readBits() {

	while(true) {

		if ( (!isOverflow()) && (!isUnderflow())) break;

		if(isUnderflow()) {
			lower   &= ~(Util::maskBit(precision,0) | Util::maskBit(precision,1));
			upper  |= Util::maskBit(precision,1);
			code ^= Util::maskBit(precision,1);
		}
		normalize();
	}
}

bool Arithmetic::isOverflow() {
	return (upper & Util::maskBit(precision,0)) == (lower & Util::maskBit(precision,0));
}

bool Arithmetic::isUnderflow() {
	bool ret  = (lower & Util::maskBit(precision,1)) && !(upper & Util::maskBit(precision,1));
	     ret &= !isOverflow();
	return ret;
}

unsigned long Arithmetic::getBytesCounter() {
	return bitFile->getBytesCounter();
}

void Arithmetic::log(charDT c) {
	std::string tmp = "Caracter leido: ";
	if (c == C_EOF)
		tmp.append("EOF");

	else if(c == C_ESC)
		tmp.append("ESCAPE");

	else
		tmp.append(1,(char)c);

	log(tmp);
}

void Arithmetic::log(std::string message) {
	if(loggear)
		logger->info(message);
}
