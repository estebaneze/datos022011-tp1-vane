#include "KeyElement.h"

KeyElement::KeyElement() {
	this->rightNode=-1;
}

KeyElement::KeyElement(KeyInt key,Offset rightNode) {
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

void KeyElement::setKey(KeyInt key) {
	this->key = key;
}

KeyInt KeyElement::getKey(){

	return this->key;
}

ostream& operator<<(ostream& myOstream, KeyElement& elem){

	myOstream << elem.getKey() << " RightOffSet: " << elem.getrightNode() << " ";

	return myOstream;
}


/******************************************************
 * 					PERSISTENCIA
 *
 ****************************************************/
std::string KeyElement::serialize() {
	std::string buffer = "";

	buffer.append((char*)&key,sizeof(KeyInt));
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
	return (sizeof(KeyInt) + sizeof(Offset));
}
