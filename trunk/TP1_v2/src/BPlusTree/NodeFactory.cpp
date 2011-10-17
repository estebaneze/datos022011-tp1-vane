/*
 * NodeFactory.cpp
 *
 *  Created on: Apr 25, 2010
 *      Author: carlos
 */

#include "NodeFactory.h"

NodeFactory::NodeFactory() {

}

/**
 * En caso que el nivel sea 1 el proximo sera una hoja.
 */
BNode* NodeFactory::createNodeForSearch(int level) {
	if (level == 1 || level == 0) {
		return new LeafNode();
	} else {
		return new Node();
	}
}
BNode* NodeFactory::createSibling(int level){
	if(level>=1){
		return new Node();
	}else{
		return new LeafNode();
	}
}
Node* NodeFactory::createKeyNode() {
	return new Node();
}
LeafNode* NodeFactory::createLeafNode() {
	return new LeafNode();
}
NodeFactory::~NodeFactory() {
}
