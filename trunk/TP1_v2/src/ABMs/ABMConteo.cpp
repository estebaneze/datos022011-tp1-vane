/*
 * ABMConteo.cpp
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */
#include "ABMConteo.h"

ABMConteo::ABMConteo() {

	string mainTreeName = "conteo";
	int bufferSize = ConfigurationMananger::getInstance()->getBufferSizeTree();
	this->bplusTree = new BPlusTree(bufferSize,Helper::concatenar(mainTreeName,"bpt","."));

	this->indexByDistrito = new Index(Helper::concatenar(mainTreeName,"Distrito","_"));
	this->indexByLista = new Index(Helper::concatenar(mainTreeName,"Lista","_"));
	this->indexByEleccion = new Index(Helper::concatenar(mainTreeName,"Eleccion","_"));

}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
/********* OJO: BUG EN EL INDICE, VER IMPLE DEL INDICE *****************/
int ABMConteo::Add(string idLista, int idDistrito, int idEleccion){

	int idConteo = Identities::GetNextIdConteo();

	Key key = Helper::IntToString(idConteo);
	string str = idLista.append("|").append(Helper::IntToString(idDistrito)).append("|").append(Helper::IntToString(idEleccion));
	Data data = (Data)str.c_str();
	int longData = str.length();

	Element * element=new Element(key, data, longData);
	this->bplusTree->insert(element);

	//Actualizo los indices
	this->indexByDistrito->AppendToIndex(Helper::IntToString(idDistrito), Helper::IntToString(idConteo));
	this->indexByLista->AppendToIndex(idLista, Helper::IntToString(idConteo));
	this->indexByEleccion->AppendToIndex(Helper::IntToString(idEleccion), Helper::IntToString(idConteo));

	return idConteo;
}

Conteo* ABMConteo::GetConteo(int idConteo){

	Element* elemento = this->bplusTree->findExact(Helper::IntToString(idConteo));
	vector<string> splited = Helper::split(elemento->getData(), '|');
	return new Conteo(splited[0], Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), idConteo);

}

vector<Conteo> ABMConteo::GetConteoByDistrito(int idDistrito){

	vector<Conteo> conteos;
	vector<Key> ids = this->indexByDistrito->GetIds(Helper::IntToString(idDistrito));

	for(int i = 0; i < ids.size(); i++){

		int kint = Helper::StringToInt(ids[i]);
		Element* elemento = this->bplusTree->findExact(ids[i]);
		vector<string> splited = Helper::split(elemento->getData(), '|');
		Conteo c = Conteo(splited[0], Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), Helper::StringToInt(ids[i]));

		conteos.push_back(c);
	}

	return conteos;
}

vector<Conteo> ABMConteo::GetConteoByEleccion(int idEleccion){


	vector<Conteo> conteos;
	vector<Key> ids = this->indexByEleccion->GetIds(Helper::IntToString(idEleccion));

	for(int i = 0; i < ids.size(); i++){
		Element* elemento = this->bplusTree->findExact(ids[i]);

		vector<string> splited = Helper::split(elemento->getData(), '|');

		Conteo c = Conteo(splited[0], Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), Helper::StringToInt(ids[i]));
		conteos.push_back(c);
	}

	return conteos;
}

vector<Conteo> ABMConteo::GetConteoByLista(string idLista){


	vector<Conteo> conteos;
	vector<Key> ids = this->indexByLista->GetIds(idLista);

	for(int i = 0; i < ids.size(); i++){
		Element* elemento = this->bplusTree->findExact(ids[i]);
		vector<string> splited = Helper::split(elemento->getData(), '|');
		Conteo c = Conteo(splited[0], Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), Helper::StringToInt(ids[i]));

		conteos.push_back(c);
	}

	return conteos;
}

void ABMConteo::mostrarConteoPorPantalla(){
	this->bplusTree->exportTree();
}

ABMConteo::~ABMConteo() {
	bplusTree->deleteTree();
	delete this->bplusTree;

	delete this->indexByDistrito;
	delete this->indexByEleccion;
	delete this->indexByLista;
}


