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
	this->indexByCargo = new Index(Helper::concatenar(bpTreeFile,"Cargo","_"));
}

/*
 * Agrego una eleccion, lo guarda en en arbol
 */
int ABMEleccion::Add(Eleccion* eleccion){

	int idEleccion = Identities::GetNextIdEleccion();//eleccion->GetId(); //NO PUEDO HACER EL ID DE LA ELECCION CON "|" PORQUE SE CONFUNDE CUANDO LO QUIERO USAR EN LAS OTRAS ENTIDADES

	cout << idEleccion << endl;

	if (!Exists(eleccion)){

		cout << "Insertando la eleccion: " << idEleccion << endl << endl;
		//string auxValueBtree;
		vector<int> distritos = eleccion->GetDistritos();
		string concatDistritos = Helper::concatenar(distritos, "|");
//		for (unsigned int i=0;i<(eleccion->GetDistritos().size());i++){
//			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(distritos[i]),"|");
//		}

		//data = fecha|idcargo|distritos
		string str = eleccion->GetDate().getStrFecha().append("|").append(Helper::IntToString(eleccion->GetIdCargo())).append("|").append(concatDistritos);
		Data data = (Data)str.c_str();
		int longData = str.length();
		Element * elemento = new Element(idEleccion,data,longData);
		this->bpPlusTree->insert(elemento);

		//logueo el add
		BPlusTreeLog::LogInsert(idEleccion,str,"Eleccion_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Eleccion_BPlusTreeProccess.log");

		//Agrego al indice
		this->indexByFecha->AppendToIndex(eleccion->GetDate().getStrFecha(),Helper::IntToString(idEleccion));
		this->indexByCargo->AppendToIndex(eleccion->GetIdCargo(),Helper::IntToString(idEleccion));

		//Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
		distritos = eleccion->GetDistritos();
		for(int i = 0; i< distritos.size(); i++){

			this->indexByDistrito->AppendToIndex(Helper::IntToString(distritos[i]), Helper::IntToString(idEleccion));
		}

		return 0;
	}
	else return -1;
}

/*
 * Si existe la eleccion la elimina y devuelve true, sino devuelve false
 */
bool ABMEleccion::Delete(Eleccion* eleccion){

	int idEleccion = eleccion->GetId();

	if (ExistsKey(idEleccion)){

		vector<int> distritos = eleccion->GetDistritos();

		this->bpPlusTree->remove(idEleccion);
		string auxValueBtree;

		for (unsigned int i=0;i<(eleccion->GetDistritos().size());i++){
			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion->GetDistritos()[i]),"|");
		}

		//logueo el delete
		BPlusTreeLog::LogDelete(idEleccion,auxValueBtree,"Eleccion_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Eleccion_BPlusTreeProccess.log");

		//Elimino del indice
		this->indexByFecha->DeleteFromIndex(eleccion->GetDate().getStrFecha(),Helper::IntToString(idEleccion));
		this->indexByCargo->DeleteFromIndex(eleccion->GetIdCargo(),Helper::IntToString(idEleccion));

		//Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
		for(int i = 0; i< distritos.size(); i++){
			this->indexByDistrito->DeleteFromIndex(Helper::IntToString(distritos[i]), Helper::IntToString(eleccion->GetId()));
		}

		return true;

	} else {
		return false;
	}
}

/*
 * Modifica la eleccion pasada por parametro si lo encuentra, sino no hace nada
*/
bool ABMEleccion::Modify(Eleccion* eleccion){

	int idEleccion = eleccion->GetId();

	if (ExistsKey(idEleccion)){

		//No se puede modificar ni la fecha ni el cargo, solamente los distritos
		Eleccion* oldEleccion = this->GetEleccion(idEleccion);
		Fecha f1 = oldEleccion->GetDate();
		Fecha f2 = eleccion->GetDate();

		if(f1 != f2)
			cout << "pepe" << endl;

		if(f1 != f2 || eleccion->GetIdCargo() != eleccion->GetIdCargo()){
			cout << "No se puede modificar la fecha ni el Cardo de la Eleccion"  << endl;
			return false;
		}

		//primero borro el id de eleccion indexado en el indice de distritos, despues agrego los que tengo ahora
		Eleccion* old = this->GetEleccion(eleccion->GetId());
		vector<int> oldDistritos = old->GetDistritos();	//Me traigo los distritos que tiene ahora (antes de modificarla)
		for(int i = 0; i< oldDistritos.size(); i++){
			this->indexByDistrito->DeleteFromIndex(Helper::IntToString(oldDistritos[i]), Helper::IntToString(eleccion->GetId()));
		}

		/*
		string auxValueBtree;
		for (unsigned int i=0;i<(eleccion->GetDistritos().size());i++){
			auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion->GetDistritos()[i]),"|");
		}

		Data data = (Data)auxValueBtree.c_str();
		int longData = auxValueBtree.length();
		Element * elemento = new Element(idEleccion,data,longData);
		this->bpPlusTree->modify(elemento);
*/

		vector<int> distritos = eleccion->GetDistritos();
		string concatDistritos = Helper::concatenar(distritos, "|");

		//data = fecha|idcargo|distritos
		string str = eleccion->GetDate().getStrFecha().append("|").append(Helper::IntToString(eleccion->GetIdCargo())).append("|").append(concatDistritos);
		Data data = (Data)str.c_str();
		int longData = str.length();
		Element * elemento = new Element(idEleccion,data,longData);
		this->bpPlusTree->modify(elemento);

		//logueo el modify
		BPlusTreeLog::LogModify(idEleccion,str,"Eleccion_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Eleccion_BPlusTreeProccess.log");

		//Aca no hay que modificar el indice, ya que lo que se indexa es la fecha, que me devuelve los ids de elcciones correspondientes
			//a esa fecha, pero eso nunca se modifica.

		//Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
		distritos = eleccion->GetDistritos();
		for(int i = 0; i< distritos.size(); i++){
			this->indexByDistrito->AppendToIndex(Helper::IntToString(distritos[i]), Helper::IntToString(eleccion->GetId()));
		}

		return true;
	}

	return false;
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


Eleccion* ABMEleccion::GetEleccion(int idEleccion){

	if (ExistsKey(idEleccion)){

		Element * el = this->bpPlusTree->findExact(idEleccion);

		string data = el->getData();
		//data = fecha|idcargo|distritos
		vector<string> splited = Helper::split(data, '|');
		Fecha fecha = Fecha(splited[0]);
		int idCargo = Helper::StringToInt(splited[1]);

		//Busco  los distritos
		Eleccion * eleccion =  new Eleccion(idCargo, fecha, idEleccion);
		for(int i = 2; i < splited.size(); i++){
			eleccion->AddDistrito(Helper::StringToInt(splited[i]));
		}

		//string key = el->getKey();
		//vector<string> splitKey = Helper::split(el->getKey(), '_');
		//Fecha fecha = Fecha(splitKey[0]);

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

	if(this->bpPlusTree->findExact(eleccion->GetId()) == NULL)
		return false;
	else
		return true;
}


/*
 * Devuelve true si la key existe en el arbol, sino false.
 */
bool ABMEleccion::ExistsKey(KeyInt key){

	if(this->bpPlusTree->findExact(key) == NULL)
		return false;
	else
		return true;
}

/*
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
*/

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


