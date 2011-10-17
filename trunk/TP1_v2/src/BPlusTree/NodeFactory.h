/*
 * NodeFactory.h
 *
 *  Created on: Apr 25, 2010
 *      Author: carlos
 */

#ifndef NODEFACTORY_H_
#define NODEFACTORY_H_

#include "BNode.h"
#include "LeafNode.h"
#include "Node.h"

class NodeFactory {
public:
	NodeFactory();
	/**
	 * Crea un nodo para búsqueda según en nivel de hoja en el que se encuentre
	 */
	static BNode* createNodeForSearch(int level);
	static Node* createKeyNode();
	static LeafNode* createLeafNode();
	static BNode* createSibling(int level);

	virtual ~NodeFactory();
};

#endif /* NODEFACTORY_H_ */
