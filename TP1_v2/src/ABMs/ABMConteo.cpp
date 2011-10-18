/*
 * ABMConteo.cpp
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */
#include "ABMConteo.h"

ABMConteo::ABMConteo(string BPTree) {

	this->bpTreeFile= Helper::concatenar(BPTree,"bpt",".");
	this->bplusTree = new BPlusTree(2048,this->bpTreeFile);
	/*
	this->indexByDistrito = new Index(Helper::concatenar(BPTree,"Distrito","_"));
	this->indexByLista = new Index(Helper::concatenar(BPTree,"Lista","_"));
	this->indexByEleccion = new Index(Helper::concatenar(BPTree,"Eleccion","_"));
	*/
}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
/********* OJO: BUG EN EL INDICE, VER IMPLE DEL INDICE *****************/
void ABMConteo::Add(int idLista, int idDistrito, int idEleccion){

	int idConteo = Identities::GetNextIdConteo();

	//DistributionTable* dtTmp = new DistributionTable();
	Key key = Helper::IntToString(idConteo);
	string str = Helper::IntToString(idLista).append("|").append(Helper::IntToString(idDistrito)).append("|").append(Helper::IntToString(idEleccion));
	Data data = (Data)str.c_str();
	int longData = str.length();

	Element * element=new Element(key, data, longData);
	this->bplusTree->insert(element);

	/*
	cout << endl;
	this->bplusTree->exportTree();
	cout << endl;
	*/

	//Actualizo los indices
	this->indexByDistrito->AppendToIndex(idDistrito, idConteo);
	this->indexByLista->AppendToIndex(idLista, idConteo);
	this->indexByEleccion->AppendToIndex(idEleccion, idConteo);
}

vector<Conteo> ABMConteo::GetConteoByDistrito(int idDistrito){


	vector<Conteo> conteos;
	vector<int> ids = this->indexByDistrito->GetIds(idDistrito);

	for(int i = 0; i < ids.size(); i++){
		Element* elemento = this->bplusTree->findExact(Helper::IntToString(ids[i]));

		vector<string> splited = Helper::split(elemento->getData(), '|');

		Conteo c = Conteo(Helper::StringToInt(splited[0]), Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), ids[i]);
		conteos.push_back(c);
	}

	return conteos;
}

vector<Conteo> ABMConteo::GetConteoByEleccion(int idEleccion){


	vector<Conteo> conteos;
	vector<int> ids = this->indexByEleccion->GetIds(idEleccion);

	for(int i = 0; i < ids.size(); i++){
		Element* elemento = this->bplusTree->findExact(Helper::IntToString(ids[i]));

		vector<string> splited = Helper::split(elemento->getData(), '|');

		Conteo c = Conteo(Helper::StringToInt(splited[0]), Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), ids[i]);
		conteos.push_back(c);
	}

	return conteos;
}

vector<Conteo> ABMConteo::GetConteoByLista(int idLista){


	vector<Conteo> conteos;
	vector<int> ids = this->indexByLista->GetIds(idLista);

	for(int i = 0; i < ids.size(); i++){
		Element* elemento = this->bplusTree->findExact(Helper::IntToString(ids[i]));

		vector<string> splited = Helper::split(elemento->getData(), '|');

		Conteo c = Conteo(Helper::StringToInt(splited[0]), Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), ids[i]);
		conteos.push_back(c);
	}

	return conteos;
}

void ABMConteo::mostrarConteoPorPantalla(){
	this->bplusTree->exportTree();
}

ABMConteo::~ABMConteo() {
}


