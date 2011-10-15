/*
 * LeafNode.cpp
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#include "LeafNode.h"
#include <iostream>
#include "../exceptions/OperationNotFoundException.h"

LeafNode::LeafNode() {
	nextNode = -1;
	prevNode = -1;
	freeSpace = 0;
	setLevel(0);
}

LeafNode::~LeafNode() {

	std::vector<Element* >::iterator it;

	it=this->elements.begin();
	while(it!=this->elements.end()){
		delete (*it);
		this->elements.erase(it);
	}
}

Offset LeafNode::getPrevNode() {
	return prevNode;
}

Offset LeafNode::getNextNode() {
	return nextNode;
}

FreeSpace LeafNode::getFreeSpace() {
	return freeSpace;
}

Element* LeafNode::getElement(Key key) {
	std::vector<Element*>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++) {
		Element* el = (Element*) *it;
		if (key == el->getKey())
			return el;
	}

	throw new ElementNotFoundException();
}

/**
 * Balancea con el sibling, devuelve true si cambiaron (ambos this y sibling)
 * false en caso contrario.
 * Pasa los primeros elementos de este nodo al final sibling (hermano)
 */
bool LeafNode::rightBalanceWith(BNode* leftSibling){
	LeafNode* myLeftSibling=(LeafNode*)leftSibling;
	vector<Element*>::iterator it=this->elements.begin();
	Element* elem=(*it);

	int borrowRecordCount=0;
	if(!this->isUnderflowded()){
		while(leftSibling->isUnderflowded() && !this->isUnderflowded()){
			borrowRecordCount++;
			this->elements.erase(it);
			myLeftSibling->insertar(elem);
		}
		if(this->isUnderflowded()){
			//no puedo balancear asi que le devuelvo los registros pedidos
			for(int i=borrowRecordCount;i>0;i--){
				it=myLeftSibling->elements.end();
				it--;
				elem=(*it);
				myLeftSibling->elements.erase(it);
				this->elements.push_back(elem);
			}
			return false;
		}else{
			return true;
		}
		return false;
	}
}
/**
 * Balancea con el sibling, devuelve true si cambiaron ambos (this y sibling) false caso contrario.
 * Pasa los ultimos elementos de este nodo al rightSibling
 */
bool LeafNode::leftBalanceWith(BNode* rightSibling){
	LeafNode* myRightSibling=(LeafNode*)rightSibling;
	vector<Element*>::iterator it=this->elements.end();
	Element* elem=(*it);

	int borrowRecordCount=0;
	if(!this->isUnderflowded()){
		while(rightSibling->isUnderflowded() && !this->isUnderflowded() ){
			borrowRecordCount++;
			it--;
			elem=(*it);
			myRightSibling->elements.insert(myRightSibling->elements.begin(),elem);
			this->elements.erase(it);
			it=this->elements.end();
		}
		if(this->isUnderflowded()){// si este quedo en underflow entonces no puedo balancear
			for(int i=borrowRecordCount;i>0;i--){
				it=myRightSibling->elements.begin();
				this->elements.push_back(*it);
				myRightSibling->elements.erase(it);
			}
			return false;
		}else{
			return true;
		}
		return false;
	}
}
/**
 * Toma los elementos de sibling y se los agrega a este nodo
 */
bool LeafNode::join(BNode* sibling){
	LeafNode* mySibling=(LeafNode*)sibling;
	vector<Element*>::iterator it;

	it=mySibling->elements.begin();
	while(it!=mySibling->elements.end()){
		this->elements.push_back((*it));
		mySibling->elements.erase(it);
		it=mySibling->elements.begin();
	}
	return true;
}

//NO USAR PARA BUSCAR EL HERMANO
Key LeafNode::getFirstKey(){
	//puede que este vacio entonces devuelveo
	if(this->elements.size()==0){
		throw ElementNotFoundException();
	}
	return (*(elements.begin()))->getKey();
}
/**
 * Devuleve siempre true. Arroja una exception en caso de que ya exista
 */
bool LeafNode::insertar(Element* elemToInsert){
		std::vector<Element*>::iterator it;


		it = find_if(this->elements.begin(), this->elements.end(), bind2nd(EqualElementComparator(),elemToInsert));
		//it = find (elements.begin(), elements.end(), elemToInsert);

		if(it!=this->elements.end()){
			throw ElementAlreadyExists();
		}

		for (it = elements.begin(); it != elements.end(); it++) {
			Element* el = (Element*) *it;
			if (elemToInsert->getKey() < el->getKey()) {
				elements.insert(it, elemToInsert);
				return true;
			}
		}
		//si llego aca es porque es mayor a todas la claves asi que la inserto al final

		elements.push_back(elemToInsert);
		return true;
}

LeafNode *LeafNode::find(Key key) {
	return this;
}

Element *LeafNode::findExact(Key key) {
	std::vector<Element*>::iterator it = getElementsBegin();

	while(it != getElementsEnds()) {
		if((*it)->getKey() == key)
			return *it;
		it++;
	}

	throw new ElementNotFoundException();
}

/**
 * Tenemos que encontrar la elemento, sino esta, entonces hay que arrojar un error.
 */
bool LeafNode::modify(Element* elemToModify){

	std::vector<Element*>::iterator it;
	Element* el;

	it = find_if(this->elements.begin(), this->elements.end(), bind2nd(EqualElementComparator(),*elemToModify));

	if(it==this->elements.end()){
		throw new ElementNotFoundException();
	}else{
		el=(*it);
		this->elements.erase(it);
		this->elements.insert(it,elemToModify);
		delete el;
	}

	return true;
}

/**
 * Elimina el elemento cuya clave es key
 */
bool LeafNode::remove(Key key){
		vector<Element*>::iterator it = this->elements.begin();
		bool found=false;
		while(it != this->elements.end() && !found) {
			if((*it)->getKey() == key){
				delete *it;
				this->elements.erase(it);
				found=true;
			}
			it++;

		}

		if(!found){
			throw new ElementNotFoundException();
		}
		return found;
}

/**
 * Metodo para test
 */
bool LeafNode::insertarTest(Element* elem) {

	std::vector<Element*>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++) {
		Element* el = (Element*) *it;
		if (elem->getKey() < el->getKey()) {
			elements.insert(it, elem);
			return true;
		}
	}

	elements.push_back(elem);
	return true;
}

/**
 * Divide la carga de bytes en dos nuevos Nodos
 */
KeyElement* LeafNode::doSplit() {
	KeyElement* keyElementFromMiddle=new KeyElement();

	LeafNode* newLeafNode=NodeFactory::createLeafNode();
	PersistorBTree* p=Persistor::getInstance();
	newLeafNode->elements=this->splitElements();

	vector<Element*>::iterator it;

	p->add(newLeafNode);
	keyElementFromMiddle->setRightNode(newLeafNode->getOffset());
	Element* elemen= (Element*)(*newLeafNode->elements.begin());
	keyElementFromMiddle->setKey(elemen->getKey());
	newLeafNode->nextNode=this->nextNode;
	this->nextNode=newLeafNode->getOffset();

	return keyElementFromMiddle;
}

/**
 * Devuelve la mitad de la carga de este nodo.
 */
std::vector<Element*> LeafNode::splitElements(){
	std::vector<Element* > newElements;

	std::vector<Element* >::iterator it=this->elements.end();
	it--;

	while(this->getDataElementsSize(this->elements)>this->getDataElementsSize(newElements)){
		newElements.insert(newElements.begin(),(*it));
		this->elements.erase(it);
		it--;
	}

	return newElements;
}

bool LeafNode::isOverflowded(int modifyOrInsert){
		bool isOverflow=false;
		switch (modifyOrInsert) {
			case INSERT:
				//Vemos que no supere el porcentaje de carga
				int dataSize;
				dataSize=this->getDataSize();
				int maxNodeLoad;
				maxNodeLoad=ConfigurationMananger::getInstance()->maxNodeLoadForInsert();
				isOverflow=dataSize>maxNodeLoad;
				break;
			case MODIFY:
				//si entra esta bien.
				dataSize=this->getDataSize();
				maxNodeLoad=ConfigurationMananger::getInstance()->getBufferSizeTree();
				isOverflow=dataSize>maxNodeLoad;
				break;
			default:
				throw OperationNotFoundException();
				break;
		}

		return isOverflow;
}

bool LeafNode::isUnderflowded() {
	ConfigurationMananger *cManager = ConfigurationMananger::getInstance();

	int minUnderflow=cManager->getMinUnderflowSizeTree();
	int dataSize=this->getDataSize();
	if(minUnderflow>dataSize)
		return true;
	else
		return false;
}

/******************************************************
 * 					PERSISTENCIA
 *
 ****************************************************/
RegisterCounter LeafNode::getRegisterCounter(){
	return this->elements.size();
}
std::vector<Element*>::iterator LeafNode::getElementsBegin() {
	return elements.begin();
}

std::vector<Element*>::iterator LeafNode::getElementsEnds() {
	return elements.end();
}
std::string LeafNode::serialize() {
	std::string buffer = BNode::serialize();

	buffer.append((char*)&prevNode,sizeof(Offset));
	buffer.append((char*)&nextNode,sizeof(Offset));

	std::vector<Element*>::iterator it;

	for(it = elements.begin() ; it != elements.end(); it++){
		Element* el = (Element*)*it;
		buffer.append(el->serialize());
	}

	return buffer;
}

void LeafNode::unserialize(std::string &buffer) {
	BNode::unserialize(buffer);
	RegisterCounter registerCounter;

	buffer.copy((char*)&registerCounter,sizeof(RegisterCounter));
    buffer.erase(0,sizeof(RegisterCounter));

	buffer.copy((char*)&prevNode,sizeof(Offset));
	buffer.erase(0,sizeof(Offset));

	buffer.copy((char*)&nextNode,sizeof(Offset));
	buffer.erase(0,sizeof(Offset));


	for(RegisterCounter i = 0 ; i < registerCounter; i++){
		Element* el = new Element();
		el->unserialize(buffer);
		elements.push_back(el);
	}
}

/**
 * Devuelve el tamaño del vector
 */
int LeafNode::getDataElementsSize(std::vector<Element*> vector){

	int size=0;
	std::vector<Element* >::iterator it;

	for(it=vector.begin();it!=vector.end();it++){
		Element* elem=(*it);
		size+=elem->getDataSize();
	}
	return size;
}

int LeafNode::getDataSize() {
	 return (2 * sizeof(Offset) + sizeof(FreeSpace) + getDataElementsSize(elements) + BNode::getDataSize());
}

void LeafNode::exportNode(){

	std::vector<Element* >::iterator it;
	cout<<"Nodo: "<<this->getOffset()<<" ";
	for(it=this->elements.begin();it!=elements.end();it++){
		Element* elem=(*it);
		elem->toSrtring();
		cout<<" ";
	}
	cout<<endl;

}
ostream& LeafNode::printMe(ostream& myOstream){
	std::vector<Element* >::iterator it;
	myOstream<<"Nodo: "<<getOffset()<<" ";
	for(it=getElementsBegin();it!=getElementsEnds();it++){
		Element* elem=(*it);
		myOstream<<*elem<<" ";
	}
	myOstream<<endl;
	return myOstream;

}


//**********************************//
//*****functor para la busqueda*****//
//**********************************//


