/*
 * PersistorBTree.h
 *
 *  Created on: 23/04/2010
 *      Author: daniel
 */

#ifndef PERSISTORBTREE_H_
#define PERSISTORBTREE_H_

#include "PersistorBase.h"
#include "../utils/types.h"
#include "../BPlusTree/BNode.h"

class PersistorBTree : public PersistorBase {
protected:

	//Sobreescribo este metodo para que cree un nodo raiz vacio
	void newFile(std::string fileName) ;

public:
	PersistorBTree(std::string fileName, BlockSize size) ;
	virtual ~PersistorBTree();
	BNode* getNodeInBlock(int blockNumber);
	BNode* getRoot();

};

#endif /* PERSISTORBTREE_H_ */
