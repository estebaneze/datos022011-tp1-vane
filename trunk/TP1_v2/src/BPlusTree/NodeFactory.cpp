/*
 * NodeFactory.cpp
 *
 *  Created on: Apr 25, 2010
 *      Author: carlos
 */

#include "NodeFactory.h"
#include "Node.h"
#include "LeafNode.h"
int NodeFactory::nodeCounter=0;
NodeFactory::NodeFactory() {
}

/**
 * En caso que el nivel sea 1 el proximo sera una hoja.
 */
BNode* NodeFactory::createNodeForSearch(int level) {
	nodeCounter++;
	if (level == 1 || level == 0) {
		return new LeafNode();
	} else {
		return new Node();
	}
}
BNode* NodeFactory::createSibling(int level){
	nodeCounter++;
	if(level>=1){
		return new Node();
	}else{
		return new LeafNode();
	}
}
Node* NodeFactory::createKeyNode() {
	nodeCounter++;
	return new Node();
}
LeafNode* NodeFactory::createLeafNode() {
	nodeCounter++;
	return new LeafNode();
}
NodeFactory::~NodeFactory() {

}
