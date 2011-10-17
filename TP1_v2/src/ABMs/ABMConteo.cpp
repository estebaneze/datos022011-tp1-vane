/*
 * ABMConteo.cpp
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */
#include "ABMConteo.h"

ABMConteo::ABMConteo(string BPTree, string indexDistritoFile, string indexEleccionFile, string indexListaFile) {

	this->bpTreeFile= BPTree;
	this->bplusTree = new BPlusTree(2048,BPTree);
	this->indexByDistrito = new Index(indexDistritoFile);
	this->indexByLista = new Index(indexListaFile);
	this->indexByEleccion = new Index(indexEleccionFile);
}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
void ABMConteo::Add(int idLista, int idDistrito, int idEleccion){

	int idConteo = Identities::GetNextIdConteo();

	//DistributionTable* dtTmp = new DistributionTable();
	//this->bplusTree->insert(new Element("Elemento",dtTmp));

	//Actualizo los indices
	this->indexByDistrito->AppendToIndex(idDistrito, idConteo);
	this->indexByLista->AppendToIndex(idLista, idConteo);
	this->indexByEleccion->AppendToIndex(idEleccion, idConteo);
}

vector<Conteo> ABMConteo::GetConteoByDistrito(int idDistrito){


	vector<Conteo> conteos;
	vector<int> ids = this->indexByDistrito->GetIds(idDistrito);

	for(int i = 0; i < ids.size(); i++){
		Conteo c = Conteo(1, 1, 1, ids[i]);
		conteos.push_back(c);
	}

	return conteos;
}

vector<Conteo> ABMConteo::GetConteoByEleccion(int idEleccion){


	vector<Conteo> conteos;
	vector<int> ids = this->indexByLista->GetIds(idEleccion);

	for(int i = 0; i < ids.size(); i++){
		Conteo c = Conteo(1, 1, 1, ids[i]);
		conteos.push_back(c);
	}

	return conteos;
}

vector<Conteo> ABMConteo::GetConteoByLista(int idLista){


	vector<Conteo> conteos;
	vector<int> ids = this->indexByLista->GetIds(idLista);

	for(int i = 0; i < ids.size(); i++){
		Conteo c = Conteo(1, 1, 1, ids[i]);
		conteos.push_back(c);
	}

	return conteos;
}

void ABMConteo::mostrarListasPorPantalla(){
	this->bplusTree->exportTree();
}

ABMConteo::~ABMConteo() {
}


