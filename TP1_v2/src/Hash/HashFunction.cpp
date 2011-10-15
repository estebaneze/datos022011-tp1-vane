/*
 * HashFunction.cpp
 *
 */

#include "HashFunction.h"
#include <math.h>

int HashFunction::Hash (string key){
    //s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
	unsigned int sum = 0;
    int len = key.size();
    for(int j=0; j<len; j++)
       sum += key[j]*pow(31,(len-(j+1)));

    return sum;
}

int HashFunction::MakeAddress (string key, unsigned int depth){

   unsigned int hash = Hash(key);
   return MakeAddress(hash,depth);
}

int HashFunction::MakeAddress(unsigned int key, unsigned int depth){
	//value tiene la cantidad de celdas de la tabla
	unsigned int value = 1 << depth;

	//Devuelve el resto de value y la cantida de celdas
	return (key % value);
}
