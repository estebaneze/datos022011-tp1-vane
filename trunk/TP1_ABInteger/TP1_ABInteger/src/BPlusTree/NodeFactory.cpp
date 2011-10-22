#include "NodeFactory.h"

NodeFactory::NodeFactory() {

}

/**
 * En caso que el nivel sea 1 el proximo sera una hoja.
 */
BNode* NodeFactory::createNodeForSearch(int level, PersistorBTree* p) {
	if (level == 1 || level == 0) {
		return new LeafNode(p);
	} else {
		return new Node(p);
	}
}

Node* NodeFactory::createKeyNode(PersistorBTree* p) {
	return new Node(p);
}
LeafNode* NodeFactory::createLeafNode(PersistorBTree* p) {
	return new LeafNode(p);
}
NodeFactory::~NodeFactory() {
}
