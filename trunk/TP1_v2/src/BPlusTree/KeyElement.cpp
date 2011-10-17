/*
 * KeyElement.cpp
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#include "KeyElement.h"

KeyElement::KeyElement() {
	this->rightNode=-1;
}

KeyElement::KeyElement(Key key,Offset rightNode) {
	this->key = key;
	this->rightNode = rightNode;
}

KeyElement::~KeyElement() {

}

void KeyElement::setRightNode(Offset rightNode) {
	this->rightNode = rightNode;
}

Offset KeyElement::getrightNode(){
	return rightNode;
}

void KeyElement::setKey(Key key) {
	this->key = key;
}

Key KeyElement::getKey(){

	return this->key;
}

ostream& operator<<(ostream& myOstream, KeyElement& elem){

	myOstream<<elem.getKey()<<" RightOffSet: "<<elem.getrightNode()<<" ";

	return myOstream;
}


/******************************************************
 * 					PERSISTENCIA
 *
 ****************************************************/
std::string KeyElement::serialize() {
	std::string buffer = "";

	buffer.append((char*)&key,sizeof(Key));
	buffer.append((char*)&rightNode,sizeof(Offset));

	return buffer;
}

void KeyElement::unserialize(std::string &buffer) {
	buffer.copy((char*)&key,sizeof(key));
	buffer.erase(0,sizeof(key));

	buffer.copy((char*)&rightNode,sizeof(Offset));
	buffer.erase(0,sizeof(Offset));
}

int KeyElement::getDataSize(){
	return (sizeof(Key) + sizeof(Offset));
}
