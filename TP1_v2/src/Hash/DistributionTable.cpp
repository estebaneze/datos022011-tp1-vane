/*
 * DistributionTable.cpp
 *
 *  Created on: Jun 5, 2010
 *      Author: carlos
 */

#include "DistributionTable.h"
#include "../utils/const.h"
#include "../utils/utiles.h"
#include <exception>
#include <sstream>
#include <assert.h>
DistributionTable::DistributionTable() {
}

DistributionTable::~DistributionTable() {
	distributionTable.clear();
}

void DistributionTable::updateFrequency(charDT c) {
	distributionTable.find(c)->second++;
}

freqDT DistributionTable::getFrequency(charDT c) {
	//TODO: Excepcion de que no está el caracter
	if (!this->isCharacterInTable(c))
		throw new std::exception();
	return distributionTable.find(c)->second;
}


freqDT DistributionTable::getTotalFrequency() {
	std::map<charDT, freqDT>::iterator it;

	freqDT accumulator = 0;

	for (it = getBegin(); it != getEnd(); it++)
		accumulator += it->second;

	return accumulator;
}

freqDT DistributionTable::getCumulativeFrequency(charDT c){
	std::map<charDT, freqDT>::iterator it = getBegin();
	freqDT accumulator = 0;
	bool found = false;

	while(!found && it != getEnd()) {
		accumulator += it->second;
		if(it->first ==  c)
			found = true;

		it++;
	}

	if(!found)
		accumulator = 0;

	return accumulator;
}

freqDT DistributionTable::getCumulativePreviousCharacterFrequency(charDT currentC) {
	std::map<charDT, freqDT>::iterator it = distributionTable.find(currentC);

	if(it == getBegin())
		return 0;
	else {
		it--;
		return getCumulativeFrequency(it->first);
	}
}

freqDT DistributionTable::getHigherFrequency() {
	std::map<charDT, freqDT>::iterator it;

	freqDT maxFreq= 0;

	for(it = getBegin(); it != getEnd(); it++) {
		if(it->second > maxFreq)
			maxFreq = it->second;
	}

	return maxFreq;
}

charDT DistributionTable::getSymbolWithCumulativeFrequency(unsigned int cumFreq) {
	std::map<charDT, freqDT>::iterator it = getBegin();
	charDT symbol = C_EOF;
	bool found = false;

	while(it != getEnd() && !found) {
		if(cumFreq >= getCumulativePreviousCharacterFrequency(it->first) &&
	       cumFreq < getCumulativeFrequency(it->first)) {
			found = true;
			symbol = it->first;
		}
		it++;
	}

	return symbol;
}

void DistributionTable::calculateRange(charDT c,unsigned int &lowerBound,unsigned int &upperBound) {

}

void DistributionTable::addCharacter(charDT c) {
	addCharacter(c,1);
}

void DistributionTable::addCharacter(charDT c, freqDT frequency) {
	unsigned int sizedt=distributionTable.size();

	std::map<charDT, freqDT>::iterator it = distributionTable.begin();
	bool found = false;

	while(it != distributionTable.end() && !found) {
		if(it->first > c) {
			it--;
			distributionTable.insert(it,std::pair<charDT, freqDT>(c, frequency));
			found = true;
		}
		it++;
	}

	if(!found)
		distributionTable.insert(std::pair<charDT, freqDT>(c, frequency));

	sizedt++;
		assert( (sizedt==distributionTable.size()) );
}

std::map<charDT, freqDT>::iterator DistributionTable::getBegin() {
	return distributionTable.begin();
}

std::map<charDT, freqDT>::iterator DistributionTable::getEnd() {
	return distributionTable.end();
}

void DistributionTable::clear() {
	this->distributionTable.clear();
}

bool DistributionTable::isCharacterInTable(charDT c) {
	return (distributionTable.find(c) != this->distributionTable.end());
}

std::vector<char> DistributionTable::getCharsVector() {
	std::vector<char> tmp;

	for (std::map<charDT, freqDT>::iterator i =
			this->distributionTable.begin(); i != this->distributionTable.end(); i++) {
		if (i->first < C_EOF)
			tmp.push_back(i->first);
	}

	return tmp;
}

void DistributionTable::removeCharacters(std::vector<charDT> v) {
	for (std::vector<charDT>::iterator it = v.begin(); it != v.end(); it++) {
		std::map<charDT,freqDT>::iterator i = distributionTable.find(*it);
		if (i != distributionTable.end()) distributionTable.erase(i);
	}
}

/******************************************************/
//****************PERSISTENCIA************************//
void DistributionTable::unserialize(std::string tempString) {

	int size;
	tempString.copy((char*) &size, sizeof(int));
	tempString.erase(0, sizeof(int));
	charDT temC;
	freqDT tempInt;
	for (int i = 0; i < size; i++) {

		tempString.copy((char*) &temC, sizeof(charDT));
		tempString.erase(0, sizeof(charDT));

		tempString.copy((char*) &tempInt, sizeof(freqDT));
		tempString.erase(0, sizeof(freqDT));

		this->addCharacter(temC, tempInt);
	}
}

string DistributionTable::serialize() {

	map<charDT, freqDT>::iterator it;
	stringstream temp;
	int size;

	size = distributionTable.size();
	temp.write((char*) &size, sizeof(int));

	for (it = distributionTable.begin(); it != distributionTable.end(); it++) {
		temp.write((char*) &it->first, sizeof(charDT));
		temp.write((char*) &it->second, sizeof(freqDT));
	}

	return temp.str();
}

unsigned int DistributionTable::count()
{
	return this->distributionTable.size();
}

std::string DistributionTable::toHuman(){

	//A pedido de lenny
	std::string humanTable;
	map<charDT, freqDT>::iterator it;
	unsigned int acum = 0;
	for (it = distributionTable.begin(); it != distributionTable.end(); it++) {
		charDT c = it->first;
		freqDT freq = it->second;
		if(c == C_EOF)
			humanTable.append("EOF");
		else if(c == C_ESC)
			humanTable.append("ESC");
		else if ((int)c > 47 && (int)c < 128 )
				humanTable.append(Util::toString(c));
			else humanTable.append(Util::toString((int)c));

		humanTable.append(" ");
		humanTable.append(Util::luIntToString(freq));
		humanTable.append(" ");
		humanTable.append(Util::luIntToString(acum));
		humanTable.append(" ");
		acum += freq;
		humanTable.append(Util::luIntToString(acum));
		humanTable.append(1,'\n');
	}
	return humanTable;
}
