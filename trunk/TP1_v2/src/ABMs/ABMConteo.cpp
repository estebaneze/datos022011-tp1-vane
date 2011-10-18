/*
 * ABMConteo.cpp
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */
#include "ABMConteo.h"

ABMConteo::ABMConteo(string BPTree, string indexByDistritoFile, string indexByListaFile, string indexByEleccionFile) {

	this->bpTreeFile= Helper::concatenar(BPTree,"bpt",".");
	this->bplusTree = new BPlusTree(2048,this->bpTreeFile);

	this->indexByDistrito = new Index(Helper::concatenar(BPTree,"Distrito","_"));
	this->indexByLista = new Index(Helper::concatenar(BPTree,"Lista","_"));
	this->indexByEleccion = new Index(Helper::concatenar(BPTree,"Eleccion","_"));

}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
/********* OJO: BUG EN EL INDICE, VER IMPLE DEL INDICE *****************/
int ABMConteo::Add(int idLista, int idDistrito, int idEleccion){

	int idConteo = Identities::GetNextIdConteo();

	if(this->bplusTree->find(Helper::IntToString(idConteo)) != NULL){

		Key key = Helper::IntToString(idConteo);
		string str = Helper::IntToString(idLista).append("|").append(Helper::IntToString(idDistrito)).append("|").append(Helper::IntToString(idEleccion));
		Data data = (Data)str.c_str();
		int longData = str.length();

		cout << data << endl;

		Element * element=new Element(key, data, longData);
		this->bplusTree->insert(element);

		cout << endl;
		this->bplusTree->exportTree();
		cout << endl;

		//Actualizo los indices
		this->indexByDistrito->AppendToIndex(Helper::IntToString(idDistrito), Helper::IntToString(idConteo));
		this->indexByLista->AppendToIndex(Helper::IntToString(idLista), Helper::IntToString(idConteo));
		this->indexByEleccion->AppendToIndex(Helper::IntToString(idEleccion), Helper::IntToString(idConteo));

		return idConteo;
	}
	else{
		cout << "La clave " << idConteo << endl;
		return -1;
	}
}

vector<Conteo> ABMConteo::GetConteoByDistrito(int idDistrito){


	vector<Conteo> conteos;
	vector<Key> ids = this->indexByDistrito->GetIds(Helper::IntToString(idDistrito));

	for(int i = 0; i < ids.size(); i++){

		Element* elemento = this->bplusTree->findExact(ids[i]);
		vector<string> splited = Helper::split(elemento->getData(), '|');
		Conteo c = Conteo(Helper::StringToInt(splited[0]), Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), Helper::StringToInt(ids[i]));

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

		Conteo c = Conteo(Helper::StringToInt(splited[0]), Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), Helper::StringToInt(ids[i]));
		conteos.push_back(c);
	}

	return conteos;
}

vector<Conteo> ABMConteo::GetConteoByLista(int idLista){


	vector<Conteo> conteos;
	vector<Key> ids = this->indexByLista->GetIds(Helper::IntToString(idLista));

	for(int i = 0; i < ids.size(); i++){
		Element* elemento = this->bplusTree->findExact(ids[i]);
		vector<string> splited = Helper::split(elemento->getData(), '|');
		Conteo c = Conteo(Helper::StringToInt(splited[0]), Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), Helper::StringToInt(ids[i]));

		conteos.push_back(c);
	}

	return conteos;
}

void ABMConteo::mostrarConteoPorPantalla(){
	this->bplusTree->exportTree();
}

ABMConteo::~ABMConteo() {
}


