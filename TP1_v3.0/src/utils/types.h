#ifndef TYPES_H_
#define TYPES_H_
#include <string>

typedef int Offset;
typedef std::string Key;
//typedef int Key;
typedef int KeyInt;
typedef unsigned int KeySize;
typedef unsigned int Level;
typedef unsigned int RegisterCounter;
typedef unsigned int BlockSize;
typedef unsigned int DataSize;
typedef unsigned int FreeSpace;
typedef double ChargeFactor;
typedef char* Data;
typedef unsigned short PrecisionInt;

// Tipos de DistributionTable
typedef wchar_t charDT;
typedef unsigned int freqDT;

#endif /* TYPES_H_ */
