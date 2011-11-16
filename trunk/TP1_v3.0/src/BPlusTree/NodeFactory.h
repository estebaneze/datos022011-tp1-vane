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
        static BNode* createNodeForSearch(int level, PersistorBTree* p);
        static Node* createKeyNode(PersistorBTree* p);
        static LeafNode* createLeafNode(PersistorBTree* p);

        virtual ~NodeFactory();
};

#endif /* NODEFACTORY_H_ */
