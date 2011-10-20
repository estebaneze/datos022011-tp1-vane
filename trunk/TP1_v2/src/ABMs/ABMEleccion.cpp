/*
 * ABMEleccion.cpp
 *
 *  Created on: 12/10/2011
 *      Author: loo
 */

#include "ABMEleccion.h"

/*
 * creo el arbol y le paso el nombre del archivo a generar y tamaño del bloque
 */
ABMEleccion::ABMEleccion() {

	this->bpTreeFile= Helper::concatenar("eleccion","bpt",".");
	this->bpPlusTree = new BPlusTree(2048,this->bpTreeFile);
	this->indexByFecha = new Index(Helper::concatenar(bpTreeFile,"Fecha","_"));
}

/*
 * Agrego una eleccion, lo guarda en en arbol
 */
int ABMEleccion::Add(Eleccion* eleccion){

	string value = eleccion->GetId(); //NO PUEDO HACER EL ID DE LA ELECCION CON "|" PORQUE SE CONFUNDE CUANDO LO QUIERO USAR EN LAS OTRAS ENTIDADES

	if (!Exists(eleccion)){

		cout << "Insertando la eleccion: " << value << endl << endl;
		string auxValueBtree;
		for (unsigned int i=0;i<(eleccion->GetDistritos().GetSize());i++){
			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion->GetDistritos().Get(i)),"|");
		}

		Data data = (Data)auxValueBtree.c_str();
		int longData = auxValueBtree.length();
		Element * elemento = new Element(value,data,longData);
		this->bpPlusTree->insert(elemento);
		//logueo el add
		BPlusTreeLog::LogInsert(value,auxValueBtree,"Eleccion_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Eleccion_BPlusTreeProccess.log");

		//Agrego al indice
		this->indexByFecha->AppendToIndex(eleccion->GetDate().getStrFecha(),value);

		return 0;
	}
	else return -1;
}

/*
 * Si existe la eleccion la elimina y devuelve true, sino devuelve false
 */
bool ABMEleccion::Delete(Eleccion* eleccion){

	string value = eleccion->GetId();

	if (ExistsKey(value)){
		this->bpPlusTree->remove(value);
		string auxValueBtree;
		for (unsigned int i=0;i<(eleccion->GetDistritos().GetSize());i++){
			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion->GetDistritos().Get(i)),"|");
		}
		//logueo el delete
		BPlusTreeLog::LogDelete(value,auxValueBtree,"Eleccion_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Eleccion_BPlusTreeProccess.log");
		return true;
	} else return false;
}

/*
 * Modifica la eleccion pasada por parametro si lo encuentra, sino no hace nada
*/
void ABMEleccion::Modify(Eleccion* eleccion){

	string value = eleccion->GetId();

	if (ExistsKey(value)){

		string auxValueBtree;
		for (unsigned int i=0;i<(eleccion->GetDistritos().GetSize());i++){
			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion->GetDistritos().Get(i)),"|");
		}

		Data data = (Data)auxValueBtree.c_str();
		int longData = auxValueBtree.length();
		Element * elemento = new Element(value,data,longData);
		this->bpPlusTree->modify(elemento);
		//logueo el modify
		BPlusTreeLog::LogModify(value,auxValueBtree,"Eleccion_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Eleccion_BPlusTreeProccess.log");
		//TODO: Actualizo el indice

	}
}

/*
 * Falta implementar
 */
vector<Eleccion> ABMEleccion::GetElecciones(){

	cout << endl << endl;
	cout << "****************************** Warning ********************************************" << endl;
	cout << "------------------------- ABMEleccion::GetElecciones NOT IMPLEMENTED ------------------------------" << endl;
	cout << "***********************************************************************************" << endl;
	cout << endl << endl;
}


Eleccion* ABMEleccion::GetEleccion(string idEleccion){

	if (ExistsKey(idEleccion)){

		Element * el = this->bpPlusTree->findExact(idEleccion);

		string key = el->getKey();

		vector<string> splitKey = Helper::split(el->getKey(), '_');
		Fecha fecha = Fecha(splitKey[0]);
		Eleccion * eleccion =  new Eleccion (Helper::StringToInt(splitKey[1]),fecha);

		return eleccion;
	}
	else {
		return NULL;
	}
}


/**
 * Devuelve true si el eleccion existe en el arbol, sino false.
 */
bool ABMEleccion::Exists(Eleccion* eleccion){

	string value = eleccion->GetId();

	if(this->bpPlusTree->findExact(value) == NULL) return false;
	else return true;
}


/*
 * Devuelve true si la key existe en el arbol, sino false.
 */
bool ABMEleccion::ExistsKey(Key key){
	if(this->bpPlusTree->findExact(key) == NULL) return false;
	else return true;
}

bool ABMEleccion::ExistsKey(Fecha fecha, int idCargo){

	Eleccion *eleccion = new Eleccion(idCargo,fecha);

	if(this->bpPlusTree->findExact(eleccion->GetId()) == NULL){
		delete eleccion;
		return false;
	}
	else {
		delete eleccion;
		return true;
	}
}


/*
 * Imprime por pantalla el arbol de elecciones
 */
void ABMEleccion::mostrarEleccionesPorPantalla(){
	this->bpPlusTree->exportTree();
}

ABMEleccion::~ABMEleccion() {
	bpPlusTree->deleteTree();
	delete this->bpPlusTree;
	delete this->indexByFecha;
}


