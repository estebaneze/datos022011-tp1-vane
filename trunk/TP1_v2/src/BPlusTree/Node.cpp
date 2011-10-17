/*
 * node.cpp
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#include "Node.h"
#include <math.h>
#include "LeafNode.h"
#include <iostream>
#include "NodeFactory.h"
#include "../strategies/BalanceStrategyFactory.h"
#include "../strategies/BalanceStrategy.h"
#include "../exceptions/KeyNotFoundException.h"
#include "../exceptions/ProgramException.h"
Node::Node() {
	this->leftNode = -1;
}

//TODO: probar que funcione el vaciado de la lista
Node::~Node() {

	vector<KeyElement*>::iterator it = keyElements.begin();
	while (keyElements.begin() != keyElements.end()) {
		delete (*it);
		keyElements.erase(it);
	}

}

std::vector<KeyElement*>::iterator Node::getKeyElementsBegin() {
	return keyElements.begin();
}

std::vector<KeyElement*>::iterator Node::getKeyElementsEnds() {
	return keyElements.end();
}

Offset Node::getLeftNode() {
	return leftNode;
}

void Node::setLeftNode(Offset leftNode) {
	this->leftNode = leftNode;
}
/**
 * Agregamos como primer clave este elemento.
 * Esto implica: Tomar el offsetiquierdo del nodo (que no puede ser NULL) y asignarlo
 * al offSetDerecho de keyElement. El offSetDerecho de keyElement se lo asignamos a el offSetIzquierdo del nodo.
 */
void Node::insertFirstKey(KeyElement* keyelement){
	if(this->leftNode<0){
		throw ProgramException("Se intenta a gregar un firsElement cuando el nodo no tiene puntero a izquierda");
	}
	Offset tmpOfsset=keyelement->getrightNode();
	keyelement->setRightNode(this->leftNode);
	this->leftNode=tmpOfsset;
	this->keyElements.insert(this->keyElements.begin(),keyelement);
}
void Node::appendKeyElementInOrder(KeyElement* keyElementToInsert) {
	//this->keyElements.push_back(keyElement);
	//sort(this->keyElements.begin(),this->keyElements.end());
	vector<KeyElement*>::iterator it;

	for (it = keyElements.begin(); it != keyElements.end(); it++) {
		KeyElement* el = *it;
		if (keyElementToInsert->getKey() < el->getKey()) {
			keyElements.insert(it, keyElementToInsert);
			return;
		}
	}
	keyElements.push_back(keyElementToInsert);

}

/**
 * Realiza la inserccion en el hijo, agregando la clave si hubo overflow y persistiendo el hijo.
 */
bool Node::doInsertOrModifyInChild(BNode* childNodeToInsert,
		Element* elemToInsert, int insertOrModify) {
	bool hasChanged = false;
	bool modified = false;
	switch (insertOrModify) {
	case INSERT:
		modified = childNodeToInsert->insertar(elemToInsert);
		break;
	case MODIFY:
		modified = childNodeToInsert->modify(elemToInsert);
		break;
	default:
		insertOrModify = false;
		break;
	}

	if (modified) {
		BalanceStrategy* strategy =
				BalanceStrategyFactory::createBalanceStrategy(insertOrModify);
		hasChanged = strategy->doBalance(this, childNodeToInsert);
		delete strategy;
	}
	return hasChanged;
}

/**
 * Devuelve el hijo donde seguir la busqueda
 * TODO cambiar el parametro Element* por KeyElement
 * MAYORES O IGUALES ESTAN A LA DERECHA.
 * MENORES ESTRICTOS A LA IZA.
 */
BNode* Node::findChild(Element* elementToFind) {
	//como es un nodo no hoja, tengo que buscar el donde esta el hijo
	//Se asumen que los elementos (KeyElement estan ordenados, asi que hago una busqueda secuencial,
	//La busqueda puede optimizarse.

	//para de buscar cuando, encuentro el elemento, obtengo uno mayor (entonces es el anterior) o es el ultimo elemento y es menor.

	//Menores a izquiera y mayores o iguales a derecha

	vector<KeyElement*>::iterator it;

	bool found = false;

	BNode* childNodeToSearch = NodeFactory::createNodeForSearch(
			this->getLevel());
	PersistorBTree* p = Persistor::getInstance();
	it = keyElements.begin();
	KeyElement* firtKey = (*it);
	//Caso especial donde levanto el nodo cuyo offset esta en este nodo
	if (elementToFind->getKey() < firtKey->getKey()) {
		p->load(this->leftNode, childNodeToSearch);
		found = true;
	}

	KeyElement* keyFromKeyElements;
	for (it = keyElements.begin(); it != keyElements.end() && !found; it++) {
		keyFromKeyElements = (*it);
		if (elementToFind->getKey() < keyFromKeyElements->getKey()) {
			it--;
			keyFromKeyElements=(*it);
			p->load(keyFromKeyElements->getrightNode(), childNodeToSearch);
			found = true;

		}
	}

	if (!found) {
		it = this->keyElements.end();
		it--;
		keyFromKeyElements = (*it);
		//como no lo encuentra implica que el elemento a insertar es mayor a todos entonces bajo por el de la derecha
		p->load(keyFromKeyElements->getrightNode(), childNodeToSearch);
	}
	return childNodeToSearch;
}
/**
 * Los Node insertan solo KeyElements, con lo cual, solo se insertara un elemento cuando exista un overflow.
 */
bool Node::insertar(Element* elemToInsert) {

	BNode* childNodeToSearch = this->findChild(elemToInsert);

	bool hasChanged = doInsertOrModifyInChild(childNodeToSearch, elemToInsert,
			INSERT);
	delete childNodeToSearch;
	return hasChanged;
}

bool Node::modify(Element* elemToModify) {
	BNode* childNodeToSearch = this->findChild(elemToModify);

	bool hasChanged = doInsertOrModifyInChild(childNodeToSearch, elemToModify,
			MODIFY);
	delete childNodeToSearch;
	return hasChanged;
}
bool Node::remove(Key key) {
	Element elem;
	elem.setKey(key);
	BNode* childNodeToSearch = this->findChild(&elem);
	bool hasChanged = childNodeToSearch->remove(key);
	if (hasChanged) {
		BalanceStrategy* strategy =
				BalanceStrategyFactory::createBalanceStrategy(DELETE);
		hasChanged = strategy->doBalance(this, childNodeToSearch);
	}

	delete childNodeToSearch;
	return hasChanged;
}
/**
 * Divide los elementos key devolviendo un vector con exactamente la mitad.
 * Devuelve la mitad mas alta y se queda con las mas baja. Deja la mitad mas alta
 * con la carga mas grande. Esto es asi para que los mayores o iguales esten a derecha.
 */
vector<KeyElement*> Node::splitKeyElements() {
	vector<KeyElement*> newHalf;

	int initialSize = this->keyElements.size();

	unsigned int finalSizeFirstHalf = floor(initialSize / 2);
	vector<KeyElement*>::iterator it;

	it = this->keyElements.end();
	it--;
	while (this->keyElements.size() != finalSizeFirstHalf) {
		newHalf.insert(newHalf.begin(), (*it));
		this->keyElements.erase(it);
		it--;
	}
	return newHalf;
}

/**
 *Devuevle el elemento medio que ha de insertarse en el nodo padre.
 *Guarda el nuevo nodo que se crea
 */
KeyElement* Node::doSplit() {
	PersistorBTree* p = Persistor::getInstance();
	KeyElement* keyElementFromMiddle;
	Node* newNode = NodeFactory::createKeyNode();

	//como son elementos de longitud fija puedo pasar la mitad


	newNode->keyElements = this->splitKeyElements();
	newNode->setLevel(this->getLevel());
	vector<KeyElement*>::iterator it = newNode->keyElements.begin();
	keyElementFromMiddle = (*it);
	newNode->keyElements.erase(it);
	newNode->setLeftNode(keyElementFromMiddle->getrightNode());
	p->add(newNode);
	keyElementFromMiddle->setRightNode(newNode->getOffset());

	return keyElementFromMiddle;
}

/**
 * Balancea con el lefSibling, devuelve true si pudo balancear
 * false en caso contrario.
 * Pasa el primer elemento de este nodo al final del lefSibling (hermano)
 *
 * Algoritmo:
 * Tomar la primer clave de este nodo.
 * Verificar si
 * Intercabiar el offsetIzquierda de este nodo con por el offsetDerecho de la clave
 * Insertar la clave en leftSiblingInUnderflow
 */
bool Node::rightBalanceWith(BNode* leftSiblingInUnderflow) {
	bool balanced=false;
	Node *myLeftSiblingInUnderflow = (Node*) leftSiblingInUnderflow;

	// si tenemos para prestarle
	if(!isUnderflowded() && keyElements.size()>1){
		vector<KeyElement*>::iterator itKeyElements= keyElements.begin();
		KeyElement* elementToInsert=(*itKeyElements);
		this->keyElements.erase(itKeyElements);
		if(!this->isUnderflowded()){
			Offset tmp=this->leftNode;
			this->leftNode=elementToInsert->getrightNode();
			elementToInsert->setRightNode(tmp);
			myLeftSiblingInUnderflow->keyElements.push_back(elementToInsert);
			balanced=true;
		}else{
			//rollback
			this->keyElements.insert(this->keyElements.begin(),elementToInsert);
		}
	}
	return balanced;
}

/**
 * Hay que hacer un balanceo a izquierda. Se pide 1 elemento, dado que una contraccion se genera solamente al
 * eleminar un elemento del nodo hijo y por consiguiente la supresion de una clave, balanceamos agregando 1 clave.
 * Se pasa el ultimo elemento de este nodo al principio del rightSibling.
 * Algoritmo de balanceo:
 * Tomo el ultimo elemento de la izquierda (Si no lo hace quedar en subflujo)
 * Agrego la clave en el nodo como "first" key.
 */
bool Node::leftBalanceWith(BNode* rightSiblingInUnderflow) {

	bool balanced=false;
	Node *myRightSiblingInUnderflow = (Node*) rightSiblingInUnderflow;

	// si tenemos para prestarle
	if(!isUnderflowded() && keyElements.size()>1){
		vector<KeyElement*>::iterator itKeyElements= keyElements.end();
		itKeyElements--;
		KeyElement* elementToInsert=(*itKeyElements);
		this->keyElements.erase(itKeyElements);
		if(!this->isUnderflowded()){
			myRightSiblingInUnderflow->insertFirstKey(elementToInsert);
			balanced=true;
		}else{
			//rollback
			this->keyElements.push_back(elementToInsert);
		}
	}
	return balanced;
}

LeafNode* Node::find(Key key) {
	Element* el = new Element();
	el->setKey(key);

	BNode* returnNode = findChild(el);

	if (returnNode->getLevel() > 0)
		returnNode = returnNode->find(key);
	delete el;
	return (LeafNode*) returnNode;
}

Element* Node::findExact(Key key) {
	//TODO hacer un delete del nodo que devuelve find, y devolver una referencia y no un puntero (constructor de copia)
	return find(key)->findExact(key);
}

/**
 * Agrega todos los elementos de siblin a este nodo.
 *
 * Algoritmo: Creo una clave con la primer clave del sibling.
 *
 */
bool Node::join(BNode* sibling) {
	vector<KeyElement*>::iterator it;

	Node* mySiblingToJoin = (Node*) sibling;

	PersistorBTree* p=Persistor::getInstance();
	if(mySiblingToJoin->leftNode<0){
		throw ProgramException("nodo izquierdo con offset nulo en Node.join");
	}
	BNode* node=NodeFactory::createNodeForSearch(this->getLevel());

	p->load(mySiblingToJoin->leftNode,node);
	Key newKey=node->getFirstKey();
	delete node;
	KeyElement* newKeyElement=new KeyElement(newKey,mySiblingToJoin->getLeftNode());
	this->keyElements.push_back(newKeyElement);
	it = mySiblingToJoin->keyElements.begin();
	while (it != mySiblingToJoin->keyElements.end()) {
		this->keyElements.push_back((*it));
		mySiblingToJoin->keyElements.erase(it);
		it = mySiblingToJoin->keyElements.begin();
	}
	return true;
}
//NO USAR PARA BUSCAR EL HERMANO
Key Node::getFirstKey() {
	if (this->keyElements.size() == 0) {
		throw KeyNotFoundException();
	}
	return (*this->keyElements.begin())->getKey();
}
/*****************************************
 * Metodos de persistencia
 *****************************************/

std::string Node::serialize() {
	std::string buffer = BNode::serialize();

	buffer.append((char*) &leftNode, sizeof(Offset));

	std::vector<KeyElement*>::iterator it;

	for (it = keyElements.begin(); it != keyElements.end(); it++) {
		KeyElement* ke = (KeyElement*) *it;
		buffer.append(ke->serialize());
	}

	return buffer;
}
void Node::unserialize(std::string &buffer) {
	BNode::unserialize(buffer);
	RegisterCounter registerCounter;

	buffer.copy((char*) &registerCounter, sizeof(RegisterCounter));
	buffer.erase(0, sizeof(RegisterCounter));

	buffer.copy((char*) &leftNode, sizeof(Offset));
	buffer.erase(0, sizeof(Offset));
	for (RegisterCounter i = 0; i < registerCounter; i++) {
		KeyElement *ke = new KeyElement();
		ke->unserialize(buffer);
		keyElements.push_back(ke);
	}
}

/**
 * Aca el modify or insert no lo usuamos
 */
bool Node::isOverflowded(int modifyOrInsert) {
	return this->getDataSize()
			> ConfigurationMananger::getInstance()->getBufferSizeTree();
}

bool Node::isUnderflowded() {
	int blockSize = ConfigurationMananger::getInstance()->getBufferSizeTree();

	//El tama�o del BlockSize exclusivo para elementos
	blockSize = blockSize - BNode::getDataSize() - sizeof(Offset);

	unsigned int maxCantidadElementos = blockSize / (sizeof(Key)
			+ sizeof(Offset));
	unsigned int minCantidadElementos = maxCantidadElementos / 2;

	if (minCantidadElementos > this->getRegisterCounter())
		return true;
	else
		return false;
}

/**
 * Cambia la clave a la que apunta child por la clave del primer elemento de child
 */
void Node::changeKey(BNode* child) {
	std::vector<KeyElement*>::iterator it = this->keyElements.begin();

	if(this->getLeftNode()==child->getOffset()){
		//para el nodo izquierdo no es necesario cambiar la clave ya que la clave la mantiene el
		//primer elemento de key elements;
		return;
	}
	bool found = false;
	while (it != this->keyElements.end() && !found) {
		if ((*it)->getrightNode() == child->getOffset()) {
			(*it)->setKey(child->getFirstKey());
			found = true;
		}
		it++;
	}

	if (!found)
		throw new KeyNotFoundException();

}
void Node::removeKey(Key key) {
	std::vector<KeyElement*>::iterator it;
	it = this->keyElements.begin();

	bool found = false;
	KeyElement* keyElement;
	while (!found && it != this->keyElements.end()) {
		if (key == (*it)->getKey()) {
			found=true;
			keyElement = (*it);
			delete keyElement;
			this->keyElements.erase(it);
		}
		if(!found){
			it++;
		}
	}
}
/**
 * Elimina la clave que corresponde al offset del nodo hijo
 */
void Node::removeKey(BNode* child) {

	std::vector<KeyElement*>::iterator it;
	it = this->keyElements.begin();

	bool found = false;
	KeyElement* keyElement;
	while (!found && it!= this->keyElements.end()) {
		if (child->getOffset() == (*it)->getrightNode()) {//esta es la clave que apunta al hijo y hay que eliminar
			keyElement = (*it);
			delete keyElement;
			this->keyElements.erase(it);
			found=true;
		}
		it++;
	}

}

/**
 *	Devolvemos el nodo derecho. Puede ser NULL, porque le Ke es la clave del último hijo.
 *	Buscamos la clave MAYOR estricto y devolvemos esa.
 */
BNode* Node::getRightSibling(BNode* child) {
	PersistorBTree* p = Persistor::getInstance();
	std::vector<KeyElement*>::iterator it;
	BNode* rightSibling = NULL;
	if (this->leftNode == child->getOffset()) {
		//el primer elemento de la lista puede ser null o el hermano derecho
		if(this->keyElements.size()>0){
			it=this->keyElements.begin();
			rightSibling = NodeFactory::createNodeForSearch(this->getLevel());
			p->load((*it)->getrightNode(), rightSibling);
			return rightSibling;
		}
	}
	it = this->keyElements.begin();

	bool found = false;
	while (it != this->keyElements.end() && !found) {
		if ((*it)->getrightNode() ==child->getOffset()) {
			//si encontramos el nodo que apunta entonces el siguiente tiene los hermanos mayores
			found = true;
		}
		it++;
	}
	if (found && it!=this->keyElements.end()) {
		rightSibling = NodeFactory::createNodeForSearch(this->getLevel());
		Offset offSetRightNode = (*it)->getrightNode();
		if (offSetRightNode != -1) {
			p->load(offSetRightNode, rightSibling);
		} else {
			rightSibling = NULL;
		}
		return rightSibling;
	} else {
		return NULL;
	}

}
/**
 * Hay que obtener la primer clave menor a la primer clave del child
 * Si clave del primer elemento de child mayor o igual al primer elemento de la lista de hijos (keyElemens), entonces tengo
 * que levantar le nodo izquierdo (si no es null), sino tengo que buscar el primer elemento
 * de la lista mayor o igual para levantar el anterior, que es el nodo que busco..
 *
 * Buscamos el offset del child dentro, no se puede buscar por clave porque  puede no tener ningun registro.
 * Cuando encontramos el offset del child entonces un elemento menos es el que estoy buscando
 */
BNode* Node::getLeftSibling(BNode* child) {
	PersistorBTree* p = Persistor::getInstance();
	std::vector<KeyElement*>::iterator it;
	Offset offSetChild = child->getOffset();
	if (this->leftNode == offSetChild) {
		return NULL; //No tiene hijo izquierdo
	}
	if(this->keyElements.size()==0){
		return NULL;// no tiene hermanos
	}
	it = this->keyElements.begin();
	KeyElement* keyFromKeElements = (*it);//tomamos el rimero
	if (keyFromKeElements->getrightNode() == offSetChild) {
		BNode* leftSibling = NodeFactory::createNodeForSearch(this->getLevel());
		p->load(this->leftNode, leftSibling);
		return leftSibling;
	}
	bool found = false;
	while (it != this->keyElements.end() && !found) {
		keyFromKeElements = (*it);
		found = keyFromKeElements->getrightNode() == offSetChild;
		if (!found) {
			it++;
		}
	}
	BNode* leftSibling = NULL;
	if (found) {
		leftSibling = NodeFactory::createNodeForSearch(this->getLevel());
		it--;
		p->load((*it)->getrightNode(), leftSibling);
	} else {
		leftSibling = NULL;
	}
	return leftSibling;

	//boorar!!!
	/*	Key keyToSearch=child->getFirstKey();
	 std::vector<KeyElement*>::iterator it;
	 PersistorBTree* p=Persistor::getInstance();
	 it=this->keyElements.begin();
	 KeyElement* keyFromKeElements=(*it);
	 BNode* leftSibling=NodeFactory::createNodeForSearch(this->getLevel());

	 if( keyFromKeElements->getKey()>=keyToSearch ){
	 if(this->leftNode!=-1){
	 if(this->leftNode!=child->getOffset()){
	 p->load(leftNode,leftSibling);
	 return leftSibling;
	 }else{
	 return NULL;
	 }
	 }else{
	 return NULL;
	 }
	 }else{
	 //buscamos la primer clave mayor o igual
	 it=this->keyElements.begin();
	 keyFromKeElements=(*it);
	 bool found=false;
	 while(it!=this->keyElements.end() && !found){
	 keyFromKeElements=(*it);
	 found=keyFromKeElements->getKey()>=keyToSearch;
	 it++;
	 }
	 if(found){
	 it--;
	 p->load((*it)->getrightNode(),leftSibling);
	 }else{
	 leftSibling=NULL;
	 }
	 return leftSibling;
	 }*/
}

int Node::getDataSize() {
	std::vector<KeyElement*>::iterator it;

	int size = 0;
	for (it = keyElements.begin(); it != keyElements.end(); it++) {
		KeyElement* ke = (KeyElement*) *it;
		size += ke->getDataSize();
	}

	return (sizeof(Offset) + size + BNode::getDataSize());
}

ostream& Node::printMe(ostream& myOstream) {
	std::vector<KeyElement*>::iterator it;
	myOstream << "Nodo: " << getOffset() << " Left OffSet: " << getLeftNode()
			<< " Elementos Key: ";
	KeyElement* keyElement;
	for (it = getKeyElementsBegin(); it != getKeyElementsEnds(); it++) {
		keyElement = (*it);
		myOstream << *keyElement;
	}
	myOstream << endl;

	Offset rightNode = getLeftNode();
	PersistorBTree* p = Persistor::getInstance();
	BNode* bNode = NodeFactory::createNodeForSearch(getLevel());
	p->load(rightNode, bNode);
	myOstream << bNode;
	delete bNode;

	for (it = getKeyElementsBegin(); it != getKeyElementsEnds(); it++) {
		Offset rightNode = (*it)->getrightNode();
		PersistorBTree* p = Persistor::getInstance();
		BNode* bNode = NodeFactory::createNodeForSearch(getLevel());
		p->load(rightNode, bNode);
		myOstream << *bNode;
		delete bNode;
	}

	myOstream << endl;
	return myOstream;
}
/**
 * Mostramos todas las claves y luego exportamos cada uno de los hijos a los que apunta
 */
void Node::exportNode() {

	std::vector<KeyElement*>::iterator it;
	cout << "Nodo: " << getOffset() << " Left OffSet: " << this->getLeftNode()
			<< " Elementos Key: ";
	for (it = this->keyElements.begin(); it != this->keyElements.end(); it++) {
		((KeyElement*) (*it))->toString();
	}
	cout << endl;

	Offset rightNode = leftNode;
	PersistorBTree* p = Persistor::getInstance();
	BNode* bNode = NodeFactory::createNodeForSearch(this->getLevel());
	p->load(rightNode, bNode);
	bNode->exportNode();
	delete bNode;

	for (it = this->keyElements.begin(); it != this->keyElements.end(); it++) {
		Offset rightNode = ((KeyElement*) (*it))->getrightNode();
		PersistorBTree* p = Persistor::getInstance();
		BNode* bNode = NodeFactory::createNodeForSearch(this->getLevel());
		p->load(rightNode, bNode);
		bNode->exportNode();
		delete bNode;
	}

	cout << endl;
}
