/*
 * ABMDistrito.cpp
 *
 *  Created on: 12/10/2011
 *      Author: loo
 */
#include "ABMDistrito.h"

/*
 * creo el arbol y le paso el nombre del archivo a generar y tamaño del bloque
 */
ABMDistrito::ABMDistrito(string bpTreeFile) {

	this->bpTreeFile= Helper::concatenar(bpTreeFile,"bpt",".");
	this->bpPlusTree = new BPlusTree(2048,this->bpTreeFile);
	// OJO! el tamaño lo tioene que leer desde un archivo de configuracion
}

/*
 * Agrego un distrito, lo guarda en en arbol
 */
int ABMDistrito::Add(string nombre){

	int idDistrito = Identities::GetNextIdDistrito();

	if (!Exists(idDistrito)){

		cout << "Insertando el Distrito: " << idDistrito << endl << endl;;
		Data data = (Data)nombre.c_str();
		int longData = nombre.length();
		Element * elemento = new Element(Helper::IntToString(idDistrito),data,longData);
		this->bpPlusTree->insert(elemento);

		return idDistrito;
	}

	return -1;
}

/*
 * Elimina un Distrito, si no exite devuelve false, existe y lo elimina devuelve true
 */
bool ABMDistrito::Delete(int idDistrito){

	if (ExistsKey(Helper::IntToString(idDistrito))){
		this->bpPlusTree->remove(Helper::IntToString(idDistrito));
		return true;
	} else {
		return false;
	}
}

/*
 * Modifica el distrito pasado por parametro si lo encuentra, sino no hace nada
*/
void ABMDistrito::Modify(Distrito distrito){

	if (Exists(distrito)){
		string str= distrito.GetNombre();
		Data data = (Data)str.c_str();
		int longData = str.length();
		Element * elemento = new Element(Helper::IntToString(distrito.GetId()),data,longData);
		this->bpPlusTree->modify(elemento);
	}
}

/*
 * Falta implementar
 */
vector<Distrito> ABMDistrito::GetDistritos(){
	vector<Distrito> distritos;
	return distritos;
}

/*
 * Devuelve el distrito si no existe el nombre NULL
 */
Distrito* ABMDistrito::GetDistrito(int idDistrito){

	string distritoId = Helper::IntToString(idDistrito);

	if (ExistsKey(distritoId)){

		Element* el = bpPlusTree->findExact(distritoId);
		int idDist= Helper::StringToInt(el->getKey());

		return new Distrito(idDist, "");
	}
	else {
		return NULL;
	}
}

/**
 * Devuelve true si el distrito existe en el arbol, sino false.
 */
bool ABMDistrito::Exists(Distrito distrito){
	if(this->bpPlusTree->findExact(Helper::IntToString(distrito.GetId()))==NULL)
		return false;
	else return true;
}

/**
 * Devuelve true si el distrito existe en el arbol, sino false.
 */
bool ABMDistrito::Exists(int idDistrito){
	if(this->bpPlusTree->findExact(Helper::IntToString(idDistrito))==NULL)
		return false;
	else return true;
}

/*
 * Devuelve true si la key existe en el arbol, sino false.
 */
bool ABMDistrito::ExistsKey(Key idDistrito){
	if(this->bpPlusTree->findExact(idDistrito)==NULL)
		return false;
	else return true;
}

/*
 * Imprime por pantalla el arbol de distritos
 */
void ABMDistrito::mostrarDistritosPorPantalla(){
	this->bpPlusTree->exportTree();
}

ABMDistrito::~ABMDistrito() {
	bpPlusTree->deleteTree();
	delete this->bpPlusTree;
}


