/*
 * ABMConteo.cpp
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */
#include "ABMConteo.h"

ABMConteo::ABMConteo(string BPTree, string indexFile) {

	this->bpTreeFile= BPTree;
	this->bplusTree = new BPlusTree(2048,BPTree);
	//this->indexDistrito = new Index(indexFile);
}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
void ABMConteo::Add(int idLista, int idDistrito, int idEleccion){

	int idConteo = Identities::GetNextIdConteo();

	//DistributionTable* dtTmp = new DistributionTable();
	//this->bplusTree->insert(new Element("Elemento",dtTmp));
	//this->indexDistrito->AppendToIndex(idDistrito, idConteo);
}

vector<Conteo> ABMConteo::GetConteoByDistrito(int idDistrito){

	/*
	vector<Conteo> conteos;
	vector<int> ids = this->indexDistrito->GetIds(idDistrito);

	for(int i = 0; i < ids.size(); i++){
		Conteo c = Conteo(1, 1, 1, ids[i]);
		conteos.push_back(c);
	}

	return conteos;*/
}

void ABMConteo::mostrarListasPorPantalla(){
	this->bplusTree->exportTree();
}

ABMConteo::~ABMConteo() {
}


