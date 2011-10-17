/*
 * LeafNode.h
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#ifndef LEAFNODE_H_
#define LEAFNODE_H_
#include "../utils/const.h"
#include "../utils/types.h"
#include "../exceptions/ElementAlreadyExists.h"
#include "../exceptions/ElementNotFoundException.h"
#include "BNode.h"
#include "Element.h"
#include <string.h>
#include <vector>
#include <algorithm>
#include "../Persistence/PersistorBase.h"
#include "../Persistence/Persistor.h"
#include <functional>
#include "EqualElementComparator.h"
class LeafNode: public BNode {
private:
	Offset nextNode;
	Offset prevNode;
	FreeSpace freeSpace;
	std::vector<Element*> elements;
	std::vector<Element* > splitElements();

	int getDataElementsSize(std::vector<Element*> vector);
public:
	LeafNode();
	virtual ~LeafNode();


	KeyElement* doSplit();


	Element* getElement(Key key);
	std::vector<Element*>::iterator getElementsBegin();
	std::vector<Element*>::iterator getElementsEnds();

    /**
   	 * Balancea con el sibling, devuelve true si cambiaron (ambios this y sibling)
   	 * false en caso contrario.
   	 * Pasa los primeros elementos de este nodo al sibling (hermano)
   	 */
   	bool rightBalanceWith(BNode* leftSibling);

   	/**
   	 * Balancea con el sibling, devuelve true si cambiaron (ambios this y sibling)
   	 * false en caso contrario.
   	 * Pasa los ultimos elementos de este nodo al sibling (hermano)
   	 */
   	bool leftBalanceWith(BNode* rightSibling);
   	/**
   	 * Agrega todos los elementos de siblin a este nodo
   	 */
   	bool join(BNode* sibling);
	Key getFirstKey();
	Offset getPrevNode();
	Offset getNextNode();
	FreeSpace getFreeSpace();

	/**
	* True implica que se modifico el nodo.
	* False implica que no se modifico.
	* Si hubo overflow devuelve el elemento de overflow en keyOverflow. Para el caso de overflow el nodo se modifica dejadolo
	* listo para que se le haga un split, esto implica que hay que grabarlo
	* En caso de no poder insertar hay que arrojar una excepcion. El unico caso que se me ocurre por el cual no se puede insertar es
	* por elemento duplicado
	* Se puede arrojar una excepcion. Lo implemente con excepcion una vez y no quedo bien.
	*
	*/
	bool insertar(Element* elem);

   	/**
   	 * Devuelve el nodo hoja que contiene la clave (o el valor)
   	 */
   	LeafNode* find(Key key);
   	Element* findExact(Key key);
	/**
	 * Modifica el elemento cuya clave coincide con el que se pasa.
	 * En caso de no encontrarlo arroja una exception.
	 * Devolvera siempre true.
	 */
	bool modify(Element* elemToModify);

	bool insertarTest(Element* elem);
	bool remove(Key key);
	/* Serializable */
	std::string serialize();
	void unserialize(std::string &buffer);
	/* Devuelve el tama�o del nodo hoja:
	 * 2*Offset + FreeSpace(?) + el tama�o de todos los elementos
	 * + BNode Size (Level y RecordCount)
	 * */
	int getDataSize();

	bool isOverflowded(int modifyOrInsert);
	bool isUnderflowded();
	virtual ostream& printMe(ostream&);

	void exportNode();
	RegisterCounter getRegisterCounter();

};
//Borrar si la clase EqualElementComparator funciona bien
/*struct ElementComparator: public std::binary_function<Element,Element,bool>{
  bool operator () ( const Element& elem,const Element& elem2) const {
	return elem.getKey()==elem2.getKey();
    }
  };*/
#endif /* LEAFNODE_H_ */
