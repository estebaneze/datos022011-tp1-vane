#include "BPlusTree.h"
#include "../strategies/UnderflorRootStrategy.h"
#include "../BPlusTree/exceptions/OverflowException.h"

BPlusTree::BPlusTree(int blockSize, string fileName) {
        this->p = new PersistorBTree(fileName, blockSize);

        this->root = this->p->getRoot();
        this->current = this->getLeftLeafNodo(root);
}

BPlusTree::~BPlusTree() {
        delete this->p;
}

void BPlusTree::insert(Element* element) {
        this->insert(element, INSERT);
}

LeafNode* BPlusTree::getLeftLeafNodo(BNode* actualNode) {
        if (actualNode->getLevel() > 0) {
                Node *internalNode = (Node*) actualNode;
                BNode *leftNode = NodeFactory::createNodeForSearch(
                                actualNode->getLevel(), this->p);
                this->p->load(internalNode->getLeftNode(), leftNode);
                this->getLeftLeafNodo(leftNode);
        }

        return (LeafNode*) actualNode;
}

/**
 * Modifcar implica, encontrar el elemento en la hoja. Una vez encontrado hay que modificar el LeafElement para luego ver si cabe en la hoja.
 * Cabe en la hoja si la hoja no esta llena, sin considerar el factor de carga. Si no cabe, hay que dividir la hoja y subir la clave de
 * la derecha.
 *
 */
void BPlusTree::modify(Element* element) {
        this->insert(element, MODIFY);
}

/**
 * Eliminar una clave implica tambien una posible contraccion del arbol.
 */
void BPlusTree::remove(int key) {
        bool hasChanged = this->root->remove(key);

        if (hasChanged) {
                UnderflorRootStrategy underflowRootStrategy;

                this->root = underflowRootStrategy.doBalance(this->root);
        }
}

/**
 * La busqueda es aproximada, es decir, devuelve el elemento si lo encuentra y sino, el primero anterior mas cercano
 */
LeafNode* BPlusTree::find(int key) {
        return root->find(key);
}

Element* BPlusTree::findExact(int key){
	return root->findExact(key);
}
/**
 * Devuelve el siguiente nodo a partir del actual. Esto supone que se tenga un nodo hoja ya cargado. En caso de no tenerlo se comienza
 * a recorrer con el primero
 */
BNode* BPlusTree::next() {
        LeafNode* nextNode = NodeFactory::createLeafNode(this->p);
        this->p->load(current->getNextNode(), nextNode);

        return nextNode;
}

BNode* BPlusTree::prev() {
        LeafNode* prevNode = NodeFactory::createLeafNode(this->p);
        this->p->load(current->getPrevNode(), prevNode);

        return prevNode;
}

void BPlusTree::deleteTree() {
        this->p->deleteFile();
}

void BPlusTree::exportTree() {
        this->root = this->p->getRoot();
        this->root->exportNode();
        cout << endl;
}


ostream& BPlusTree::printMe(ostream& myOstream){

        this->root = this->p->getRoot();
        return this->root->printMe(myOstream);
}

void BPlusTree::Log(Element* element){

        //Log de la insercion
        string message = "Inserto (";
        message.append(Helper::IntToString(element->getKey()));
        message.append(",");
        message.append(element->getData());
        message.append(")");
        Log::WriteLog(message, "BPTreeOperations.log");
        cout << message << endl;

        //Logueo como queda el arbol
        ofstream logFile;
        logFile.open("BPTreeProcess.log", ios::app);
        this->printMe(logFile);
        logFile.close();
        cout << endl;
        this->exportTree();
        cout << endl;

}


//*****************************************//
//********Impl. Interna********************//
//*****************************************//
void BPlusTree::insert(Element* element, int modifyOrInsert) {

        this->validateElementSize(element);

        KeyElement* keyOverflow = NULL;
        bool modified = false;

        switch (modifyOrInsert) {
        case INSERT:
				//TODO RIK LOG INSERT
                modified = this->root->insertar(element);
                break;
        case MODIFY:
				//TODO RIK LOG MODIFICAR
                modified = this->root->modify(element);
                break;
        }

        if (modified) {
                //como se modifico el nodo, puede que tenga que grabarlo
                //TODO pasarlo a una estrategia de balanceo de root;
                if (this->root->isOverflowded(modifyOrInsert)) {
                        //como hubo overflow entonces, tengo que crear un nuevo root con esta clave
                        Node* newRoot = new Node(this->p);
                        newRoot->setLevel(this->root->getLevel() + 1);
                        keyOverflow = this->root->doSplit();
                        newRoot->setOffset(this->root->getOffset());
                        this->p->add(this->root);
                        newRoot->setLeftNode(this->root->getOffset());
                        newRoot->appendKeyElementInOrder(keyOverflow);
                        this->p->modify(newRoot);

                        BNode* oldRoot = this->root;
                        this->root = newRoot;
                        delete oldRoot;
                } else {
                        UnderflorRootStrategy underflowRootStrategy;
                        this->root = underflowRootStrategy.doBalance(this->root);
                }
        }

}

void BPlusTree::validateElementSize(Element* elm){

        int maxRecordSize=ConfigurationMananger::getInstance()->getMaxRecordSizeTree();

        if(elm->getDataSize() > maxRecordSize){
                cout << "       ******Error: Tamanio invalido de registro: ******" << elm->getDataSize() << endl;
                //throw new OverflowException("tamano invalido de registro");
        }

}
