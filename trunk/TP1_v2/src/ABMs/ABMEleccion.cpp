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

	this->bpTreeFile = "eleccion.bpt";
	int bufferSize = ConfigurationMananger::getInstance()->getBufferSizeTree();

	this->bpPlusTree = new BPlusTree(bufferSize,"eleccion.bpt");

	this->indexByFecha = new Index(Helper::concatenar(bpTreeFile,"Fecha","_"));
	this->indexByDistrito = new Index(Helper::concatenar(bpTreeFile,"Distrito","_"));
}

/*
 * Agrego una eleccion, lo guarda en en arbol
 */
int ABMEleccion::Add(Eleccion* eleccion){

	string idEleccion = eleccion->GetId(); //NO PUEDO HACER EL ID DE LA ELECCION CON "|" PORQUE SE CONFUNDE CUANDO LO QUIERO USAR EN LAS OTRAS ENTIDADES
	cout << idEleccion << endl;
	if (!Exists(eleccion)){

		cout << "Insertando la eleccion: " << idEleccion << endl << endl;
		string auxValueBtree;
		for (unsigned int i=0;i<(eleccion->GetDistritos().size());i++){
			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion->GetDistritos()[i]),"|");
		}

		Data data = (Data)auxValueBtree.c_str();
		int longData = auxValueBtree.length();
		Element * elemento = new Element(idEleccion,data,longData);
		this->bpPlusTree->insert(elemento);
		//logueo el add
		BPlusTreeLog::LogInsert(idEleccion,auxValueBtree,"Eleccion_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Eleccion_BPlusTreeProccess.log");

		//Agrego al indice
		this->indexByFecha->AppendToIndex(eleccion->GetDate().getStrFecha(),idEleccion);

		//Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
		vector<int> distritos = eleccion->GetDistritos();
		for(int i = 0; i< distritos.size(); i++){

			this->indexByDistrito->AppendToIndex(Helper::IntToString(distritos[i]), idEleccion);
		}

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

		vector<int> distritos = eleccion->GetDistritos();

		this->bpPlusTree->remove(value);
		string auxValueBtree;

		for (unsigned int i=0;i<(eleccion->GetDistritos().size());i++){
			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion->GetDistritos()[i]),"|");
		}

		//logueo el delete
		BPlusTreeLog::LogDelete(value,auxValueBtree,"Eleccion_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Eleccion_BPlusTreeProccess.log");

		//Elimino del indice
		this->indexByFecha->DeleteFromIndex(eleccion->GetDate().getStrFecha(),value);

		//Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
		for(int i = 0; i< distritos.size(); i++){

			this->indexByDistrito->DeleteFromIndex(Helper::IntToString(distritos[i]), eleccion->GetId());
		}

		return true;

	} else {
		return false;
	}
}

/*
 * Modifica la eleccion pasada por parametro si lo encuentra, sino no hace nada
*/
void ABMEleccion::Modify(Eleccion* eleccion){

	string value = eleccion->GetId();

	if (ExistsKey(value)){

		//primero borro el id de eleccion en los distritos que este indexado, despues agrego los que tengo ahora
		Eleccion* old = this->GetEleccion(eleccion->GetId());
		vector<int> oldDistritos = old->GetDistritos();	//Me traigo los distritos que tiene ahora (antes de modificarla)
		for(int i = 0; i< oldDistritos.size(); i++){
			this->indexByDistrito->DeleteFromIndex(Helper::IntToString(oldDistritos[i]), eleccion->GetId());
		}

		string auxValueBtree;
		for (unsigned int i=0;i<(eleccion->GetDistritos().size());i++){
			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion->GetDistritos()[i]),"|");
		}

		Data data = (Data)auxValueBtree.c_str();
		int longData = auxValueBtree.length();
		Element * elemento = new Element(value,data,longData);
		this->bpPlusTree->modify(elemento);

		//logueo el modify
		BPlusTreeLog::LogModify(value,auxValueBtree,"Eleccion_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Eleccion_BPlusTreeProccess.log");

		//Aca no hay que modificar el indice, ya que lo que se indexa es la fecha, que me devuelve los ids de elcciones correspondientes
			//a esa fecha, pero eso nunca se modifica.

		//Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
		vector<int> distritos = eleccion->GetDistritos();
		for(int i = 0; i< distritos.size(); i++){
			this->indexByDistrito->AppendToIndex(Helper::IntToString(distritos[i]), eleccion->GetId());
		}
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

vector<Eleccion> ABMEleccion::GetByFecha(Fecha* fecha){

	vector<Key> byFecha = this->indexByFecha->GetIds(fecha->getStrFecha());
	vector<Eleccion> elecciones;

	for(int i = 0; i < byFecha.size(); i++){

		string idEleccion = byFecha[i];
		vector<string> splited = Helper::split(idEleccion, '_');	//ESto es fecha_idCargo
		Fecha f = Fecha(splited[0]);
		int idCargo = Helper::StringToInt(splited[1]);

		elecciones.push_back(Eleccion(idCargo, f));
	}

	return elecciones;
}

vector<Eleccion> ABMEleccion::GetByFechaYDistrito(Fecha* fecha, int idDistrito){

	vector<Key> byFecha = this->indexByFecha->GetIds(fecha->getStrFecha());
	vector<Eleccion> elecciones;

	for(int i = 0; i < byFecha.size(); i++){

		string idEleccion = byFecha[i];
		vector<string> splited = Helper::split(idEleccion, '_');	//ESto es fecha_idCargo
		Fecha f = Fecha(splited[0]);
		int idCargo = Helper::StringToInt(splited[1]);

		elecciones.push_back(Eleccion(idCargo, f));
	}

	return elecciones;
}

ABMEleccion::~ABMEleccion() {
	bpPlusTree->deleteTree();
	delete this->bpPlusTree;
	delete this->indexByFecha;
}


