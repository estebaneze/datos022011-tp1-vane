/*
 * util.h
 *
 *  Created on: 03/10/2009
 *      Author: leonardo
 */

#ifndef UTILES_H_
#define UTILES_H_

#include <string>
#include <sstream>
#include "types.h"

enum cacheStrategy {writeback, writetrhough};

using namespace std;

const int TAM_VARIABLE = -1;

class Util {
public:
	Util();
	virtual ~Util();

	static string	toString (int value);
	static string	uIntToString(unsigned int value);
	static string	luIntToString(long unsigned int value);
	static int		toInt (string value);
	static string 	SerializeInt(int value);
	static string 	SerializeString (string value);
	static string 	SerializeBool (bool value);
	static string 	SerializeChar (char value);
	static int 	DeSerializeInt (string &data);
	static string 	DeSerializeString (string& data);
	static bool 	DeSerializeBool (string &data);
	static char 	DeSerializeChar (string &data);
	static bool	archivoExiste (string filename);

	/* Para trabajar con binarios */
	static unsigned int getBit(unsigned int number, unsigned int position);
	static unsigned int getBits(unsigned int number, unsigned int msPos, unsigned int lsPos);

	static void setBit(unsigned int &number, unsigned int position, short unsigned int value);
	static void setBit(unsigned char * buffer,unsigned int bufferSize, unsigned int position, short unsigned int value);

	static unsigned short int getNegBit(unsigned short int bit);

	static string bitsIntToString(unsigned int number, unsigned int presicion);
	static unsigned int bitsStringToInt(string bits);


	static void printBits(unsigned int number);

	static PrecisionInt maskBit(unsigned int precision, PrecisionInt bit);
};

#endif /* UTILES_H_ */
