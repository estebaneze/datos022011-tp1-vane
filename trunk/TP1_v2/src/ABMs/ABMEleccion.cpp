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
ABMEleccion::ABMEleccion(string bpTreeFile) {

	this->bpTreeFile= Helper::concatenar(bpTreeFile,"bpt",".");
	this->bpPlusTree = new BPlusTree(2048,this->bpTreeFile);
	this->indexByFecha = new Index(Helper::concatenar(bpTreeFile,"Fecha","_"));
}

/*
 * Agrego una eleccion, lo guarda en en arbol
 */
int ABMEleccion::Add(Eleccion eleccion){

	string fecha = eleccion.GetDate().getStrFecha();
	string value =  Helper::concatenar(fecha,Helper::IntToString(eleccion.GetIdCargo()),"|");

	if (!Exists(eleccion)){

		cout << "Insertando la eleccion: " << value << endl << endl;
		string auxValueBtree;
		for (unsigned int i=0;i<(eleccion.GetDistritos().GetSize());i++){
			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion.GetDistritos().Get(i)),"|");
		}

		Data data = (Data)auxValueBtree.c_str();
		int longData = auxValueBtree.length();
		Element * elemento = new Element(value,data,longData);
		this->bpPlusTree->insert(elemento);

		this->indexByFecha->AppendToIndex(fecha,value);
		return 0;
	}
	else return -1;
}

/*
 * Si existe la eleccion la elimina y devuelve true, sino devuelve false
 */
bool ABMEleccion::Delete(Eleccion eleccion){

	string fecha = eleccion.GetDate().getStrFecha();
	string value =  Helper::concatenar(fecha,Helper::IntToString(eleccion.GetIdCargo()),"|");

	if (ExistsKey(value)){
		this->bpPlusTree->remove(value);
		return true;
	} else return false;
}

/*
 * Modifica la eleccion pasada por parametro si lo encuentra, sino no hace nada
*/
void ABMEleccion::Modify(Eleccion eleccion){

	string fecha = eleccion.GetDate().getStrFecha();
	string value =  Helper::concatenar(fecha,Helper::IntToString(eleccion.GetIdCargo()),"|");

	if (ExistsKey(value)){
		cout << "Insertando la eleccion: " << value << endl << endl;
		string auxValueBtree;
		for (unsigned int i=0;i<(eleccion.GetDistritos().GetSize());i++){
			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion.GetDistritos().Get(i)),"|");
		}

		Data data = (Data)auxValueBtree.c_str();
		int longData = auxValueBtree.length();
		Element * elemento = new Element(value,data,longData);
		this->bpPlusTree->modify(elemento);
	}
}

/*
 * Falta implementar
 */
vector<Eleccion> ABMEleccion::GetElecciones(){
	vector<Eleccion> elecciones;
	return elecciones;
}

/*
 * Devuelve el eleccion, si no existe, NULL
 */
Eleccion * ABMEleccion::GetEleccion(Fecha fecha, int cargo){

	string sfecha = fecha.getStrFecha();
	string value =  Helper::concatenar(sfecha,Helper::IntToString(cargo),"|");

	if (ExistsKey(value)){
		Element * el = this->bpPlusTree->findExact(value);

		string key = el->getKey();

		vector<string> splitKey = Helper::split(el->getKey(), '|');
		Fecha fecha = Fecha(splitKey[1]);
		Eleccion * eleccion =  new Eleccion (Helper::StringToInt(splitKey[0]),fecha);
		return eleccion;
	} else return NULL;
}

/**
 * Devuelve true si el eleccion existe en el arbol, sino false.
 */
bool ABMEleccion::Exists(Eleccion eleccion){

	string fecha = eleccion.GetDate().getStrFecha();
	string value =  Helper::concatenar(fecha,Helper::IntToString(eleccion.GetIdCargo()),"|");

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


