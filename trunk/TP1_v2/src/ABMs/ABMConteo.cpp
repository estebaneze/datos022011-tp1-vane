/*
 * ABMConteo.cpp
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */
#include "ABMConteo.h"

ABMConteo::ABMConteo(string BPTree) {

	this->bpTreeFile= BPTree;
	this->bplusTree = new BPlusTree(2048,BPTree);
}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
void ABMConteo::Add(Conteo conteo){

	DistributionTable* dtTmp = new DistributionTable();
	this->bplusTree->insert(new Element("Elemento",dtTmp));
}


void ABMConteo::mostrarListasPorPantalla(){
	this->bplusTree->exportTree();
}

ABMConteo::~ABMConteo() {
}


