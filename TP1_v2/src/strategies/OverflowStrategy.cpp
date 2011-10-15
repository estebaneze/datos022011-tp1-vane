/*
 * OverflowStrategy.cpp
 *
 *  Created on: Apr 28, 2010
 *      Author: carlos
 */

#include "OverflowStrategy.h"

OverflowStrategy::OverflowStrategy() {

}

/**
 * Devuelve true si modifica a parent. Persitir al hijo es responsabilidad de esta clase.
 * Un overflow implica hacer un split, dividir los nodos en dos
 */
bool OverflowStrategy::doBalance(Node* parent, BNode* child,BalanceStrategy* parentStrategy){
	KeyElement* keyToInsert=NULL;
		bool hasChanged=false;
		PersistorBTree* p=Persistor::getInstance();
		int typeofStrategy=parentStrategy->getTypeOfStrategy();
		if(child->isOverflowded(typeofStrategy)){
	        keyToInsert = child->doSplit();
	        parent->appendKeyElementInOrder(keyToInsert);
	        hasChanged = true;
	    }
	    p->modify(child);
	    return hasChanged;

}

OverflowStrategy::~OverflowStrategy() {
}
