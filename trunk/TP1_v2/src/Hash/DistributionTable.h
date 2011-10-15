/*
 * DistributionTable.h
 *
 *  Created on: Jun 5, 2010
 *      Author: carlos
 */

#ifndef DISTRIBUTIONTABLE_H_
#define DISTRIBUTIONTABLE_H_

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "../utils/types.h"
using namespace std;
class DistributionTable {

private:
	//caracter frecuencia
	std::map<charDT,freqDT> distributionTable;

public:
	DistributionTable();
	virtual ~DistributionTable();

	/* Incrementa en 1 la frecuencia de un caracter */
	void updateFrequency(charDT c);

	/* Obtiene la frecuencia de un caracter en particular */
	freqDT getFrequency(charDT c);

	/* Obtiene la suma de la frecuencias de todos los caracteres de la tabla */
	freqDT getTotalFrequency();

	/* Obtiene la frecuencia acumulada del caracter */
	freqDT getCumulativeFrequency(charDT c);

	/* Obtiene elfrecuencia del caracter anterior, si no esta devuelve 0 */
	freqDT getCumulativePreviousCharacterFrequency(charDT currentC);

	/* Obtiene la frecuencia mas grande */
	freqDT getHigherFrequency();

	/* Obtiene el symbolo que corresponde a la frecuencia acumulada */
	charDT getSymbolWithCumulativeFrequency(unsigned int cumFreq);

	/* Devuelve el rango de un caracter */
	void calculateRange(charDT c,unsigned int &lowerBound,unsigned int &upperBound);

	/* Agrega un caracter a la tabla de distribuciones con frecuencia 1 */
	void addCharacter(charDT c);

	/* Agrega un caracter a la tabla de distribuciones con frecuencia determinada */
	void addCharacter(charDT c,freqDT frequency);

	/* Devuelve true si el caracter se encuentra en la tabla */
	bool isCharacterInTable(charDT c);

	/* Remueve del mapa los caracter que estan en el vector */
	void removeCharacters (std::vector<charDT> v);

	/* Devuelve un vector con todos los caracteres del mapa */
	std::vector<char> getCharsVector();


	/* Devuelve iterador al mapa de caracteres */
	std::map<charDT,freqDT>::iterator getBegin();
	std::map<charDT,freqDT>::iterator getEnd();


	void clear();

	unsigned int count();

	std::string toHuman();


	/******************************************************/
	//****************PERSISTENCIA************************//
	string serialize();
	void unserialize(std::string tempString);

};

#endif /* DISTRIBUTIONTABLE_H_ */
