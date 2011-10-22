#ifndef PERSISTORBTREE_H_
#define PERSISTORBTREE_H_

class BNode;

#include "../BPlusTree/BNode.h"
#include "PersistorBase.h"
#include "../utils/types.h"

class PersistorBTree : public PersistorBase {
protected:

	//Sobreescribo este metodo para que cree un nodo raiz vacio
	void newFile(std::string fileName) ;

public:
	PersistorBTree(std::string fileName, BlockSize size) ;
	virtual ~PersistorBTree();
	BNode* getRoot();

};

#endif /* PERSISTORBTREE_H_ */
