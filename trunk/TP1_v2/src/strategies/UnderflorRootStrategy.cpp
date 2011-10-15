/*
 * UnderflorRootStrategy.cpp
 *
 *  Created on: May 1, 2010
 *      Author: carlos
 */

#include "UnderflorRootStrategy.h"
#include "../BPlusTree/Node.h"
#include "../BPlusTree/LeafNode.h"
#include "../BPlusTree/BNode.h"
#include "../Persistence/Persistor.h"
#include "../Persistence/PersistorBTree.h"
#include "../BPlusTree/NodeFactory.h"
UnderflorRootStrategy::UnderflorRootStrategy() {

}
// el root se contrae cuando TODOS sus hijos entran en una hoja y es es cuando hay 2 hijos y
//esos entran en una hoja, para ello uno debe estar en underflow y el otro no debe poder pedirle
//nada.

BNode* UnderflorRootStrategy::doBalance(BNode* root){
	PersistorBTree* p=Persistor::getInstance();

	if(root->isUnderflowded()){
		//aca hay que contraerlo.
		if(!root->getLevel()==0){ //si no es nodo hoja entonces se puede contraer.
			//El root solo se va a contraer cuando tiene un elemento.
			Node* myroot=(Node*)root;
			if(myroot->getRegisterCounter()==0){//si es un hijo es el unico caso en el que puedo pasar el nodo hoja a root
				BNode* newroot=NodeFactory::createNodeForSearch(myroot->getLevel());
				p->load(myroot->getLeftNode(),newroot);
				Offset oldOffset=newroot->getOffset();
				newroot->setOffset(root->getOffset());
				p->removeBlock(oldOffset);
				p->modify(newroot);
				delete root;
				return newroot;
			}
		}
	}
	p->modify(root);
	return root;

}
UnderflorRootStrategy::~UnderflorRootStrategy() {
}

