/*
 * Element.cpp
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#include "Element.h"
#include "../utils/utiles.h"
#include <iostream>


//**********************************/
// * Constructores de copia
 //**********************************/

 Element::Element(const Element& el){
		key=el.key;
		dataSize=el.dataSize;
		Data dataBuffer = new char[dataSize];
		memcpy(dataBuffer,(char*)el.data,dataSize);

		this->data=dataBuffer;
	}
Element::Element(const Element* el){
		key=el->key;
		dataSize=el->dataSize;
		char* dataBuffer = new char[dataSize];
		memcpy(dataBuffer,(char*)el->data,dataSize);

		this->data=dataBuffer;
}
//**********************************/
// * Fin de Constructores de copia
 //**********************************/

Element::Element() {
	this->key="";
	this->dataSize=0;
	this->data=NULL;
}

Element::Element(Key key,DistributionTable* distributionTable){
		string dtSerialized= distributionTable->serialize();
		Data dtSerializedChar= new char[dtSerialized.size()];
		memcpy(dtSerializedChar,dtSerialized.c_str(),dtSerialized.size());
		this->key=key;
		this->setData(dtSerializedChar,dtSerialized.size());
		delete[] dtSerializedChar;

}
Element::Element(Key key,Data data,DataSize dataSize) {
	this->key  = key;
	this->setData(data,dataSize);
	delete[] data;
}

Element::~Element() {
	if(data != NULL)
		delete[] data;
}

void Element::setKey(Key key) {
	this->key = key;
}

Key Element::getKey() const {
	return key;
}

void Element::setData(Data data, DataSize dataSize){
	this->dataSize = dataSize;

	char* dataBuffer = new char[dataSize];
	memcpy(dataBuffer,data,dataSize);

	this->data=dataBuffer;
}

Data Element::getData() {
	return data;
}

DataSize Element::getElementSize() {
	return dataSize;
}

/**
 * El formato es:
 * KeySize|key|DataSize|data
 */
std::string Element::serialize() {
	std::string buffer = "";
	//serializacion de la key
	KeySize keySize=this->key.size();
	buffer.append((char*)&keySize,sizeof(KeySize));
	buffer.append(key.c_str(),keySize);


	//Serializacion de la data
	buffer.append((char*)&dataSize,sizeof(DataSize));
	buffer.append(data,dataSize);

	return buffer;
}


void Element::unserialize(std::string &buffer) {
	//copia lo que hay en el buffer a key

	//unserialize de la key
	KeySize keySize;
	buffer.copy((char*)&keySize,sizeof(KeySize));
	buffer.erase(0,sizeof(KeySize));

	char* tempData=new char[keySize];
	buffer.copy(tempData,keySize);
	this->key.append(tempData,keySize);
	delete[] tempData;
	buffer.erase(0,keySize);

	//Unserialize de la data
	buffer.copy((char*)&dataSize,sizeof(DataSize));
	buffer.erase(0,sizeof(DataSize));
	data = new char[dataSize];
	buffer.copy(data,dataSize);
	buffer.erase(0,dataSize);
}


int Element::getDataSize(){
	return (sizeof(KeySize)+key.size() + sizeof(dataSize) + dataSize);
}

ostream& operator<<(ostream& myOstream,  Element& elem){
	string data;
	if(elem.getData()!=NULL){ //programacion defensiva
		data.append(elem.getData(),elem.getElementSize());
	}
	myOstream<<"Key> "<<elem.getKey()<<" "<<"Data: "<<data<<" ";
	return myOstream;
}
