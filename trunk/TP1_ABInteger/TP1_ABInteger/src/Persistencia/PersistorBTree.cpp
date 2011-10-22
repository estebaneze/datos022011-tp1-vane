
#include "PersistorBTree.h"
#include "../BPlusTree/LeafNode.h"
#include "../BPlusTree/Node.h"
#include "../BPlusTree/NodeFactory.h"

PersistorBTree::PersistorBTree(std::string fileName, BlockSize size) {
	/* Validaci�n de que este iniciado */
	if(fileName.length() == 0 || size == 0)
		throw new PersistExceptions::PersistorNotInitializedException();

	admEspacioLibre = new AdmEspacioDisponible(fileName + ".fs");

	/* Abre el archivo para lectura - escritura binario */
	this->archivo.open(fileName.c_str(), std::ios::in|std::ios::out|std::ios::binary);
	this->blockSize = size;
	this->fileName = fileName;

	if (!this->archivo.is_open()){
		this->archivo.clear();
		this->newFile(fileName);
	}

	this->archivo.seekg(0,std::ios::beg);
    /* Levanta el bloque header */
    char charBuffer[HEADER_SIZE];
    this->archivo.read(charBuffer,HEADER_SIZE);

    BlockSize test;
    memcpy(&test, &charBuffer,sizeof(BlockSize));

    if (test != size)
		throw new PersistExceptions::WrongBlockSize();
}

PersistorBTree::~PersistorBTree() {
}


void PersistorBTree::newFile(std::string fileName) {
	PersistorBase::newFile(fileName);

	LeafNode *root = NodeFactory::createLeafNode(this);

	this->add(root);

	delete root;
}

BNode* PersistorBTree::getRoot() {
	std::string buffer;
	Level level;
	BNode *root;

	buffer = this->load(0);
	buffer.copy((char*)&level,sizeof(Level));

	if(level == 0)
		root = NodeFactory::createLeafNode(this);
	else
		root = NodeFactory::createKeyNode(this);

	root->unserialize(buffer);
	root->setOffset(0);

	return root;
}
