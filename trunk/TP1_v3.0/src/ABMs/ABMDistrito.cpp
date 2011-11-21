/*
 * ABMDistrito.cpp
 *
 *  Created on: 12/10/2011
 *      Author: loo
 */
#include "ABMDistrito.h"

/*
 * Creo el arbol y le paso el nombre del archivo a generar
 */
ABMDistrito::ABMDistrito() {
	string mainTreeName = ConfigurationMananger::getInstance()->getDistritoFile();
	mainTreeName = Helper::concatenar(mainTreeName,"bpt",".");
	//cout << "mainTreeName: "<< mainTreeName  << endl;
	int bufferSize = ConfigurationMananger::getInstance()->getBufferSizeTree();
	this->bpPlusTree = new BPlusTree(bufferSize,mainTreeName);
}

/*
 * Agrego un distrito, lo guarda en en arbol
 */
int ABMDistrito::Add(string nombre){

	if (!Exists(nombre)){

		int idDistrito = Identities::GetNextIdDistrito();

		string sdata="";
    	//metodo que concatena todos los campos
    	sdata = ProcessData::generarData(nombre);

		Data data = (Data)sdata.c_str();

		int longData = sdata.length();
		Element * elemento = new Element(idDistrito,data,longData);

		this->bpPlusTree->insert(elemento);
		//logueo el add
		BPlusTreeLog::LogInsert(Helper::IntToString(idDistrito),nombre,ConfigurationMananger::getInstance()->getLogOperDistritoFile());
		BPlusTreeLog::LogProcess(this->bpPlusTree,ConfigurationMananger::getInstance()->getLogProcessDistritoFile());

		return idDistrito;
	}

	return -1;
}

/*
 * Elimina un Distrito, si no exite devuelve false, existe y lo elimina devuelve true
 */
bool ABMDistrito::Delete(int idDistrito){

	if (ExistsKey(idDistrito)){
		Distrito * d = this->GetDistrito(idDistrito);
		this->bpPlusTree->remove(idDistrito);

		//logueo el delete
		BPlusTreeLog::LogDelete(Helper::IntToString(idDistrito),d->GetNombre(),"Distrito_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Distrito_BPlusTreeProccess.log");
		return true;
	}
	else return false;
}

/*
 * Modifica el distrito pasado por parametro si lo encuentra, sino no hace nada
*/
void ABMDistrito::Modify(Distrito* distrito){

	if (Exists(distrito)){

		string sdata="";
    	//metodo que concatena todos los campos
    	sdata = ProcessData::generarData(distrito->GetNombre());

		Data data = (Data)sdata.c_str();

		int longData = sdata.length();
		Element * elemento = new Element(distrito->GetId(),data,longData);

		//logueo el modify
		BPlusTreeLog::LogModify(Helper::IntToString(distrito->GetId()),distrito->GetNombre(),"Distrito_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Distrito_BPlusTreeProccess.log");
		this->bpPlusTree->modify(elemento);
	}
}

/*
 * Falta implementar
 */
vector<Distrito> ABMDistrito::GetDistritos(){

	vector<Distrito> distritos;


	//this->bpPlusTree->exportTree();

	//this->bpPlusTree->next();//->getFirstKey();
	/*vector<Eleccion> elecciones;

	for(int i = 0; i < byFecha.size(); i++){

		string idEleccion = byFecha[i];
		vector<string> splited = Helper::split(idEleccion, '_');	//ESto es fecha_idCargo
		Fecha f = Fecha(splited[0]);
		int idCargo = Helper::StringToInt(splited[1]);

		elecciones.push_back(Eleccion(idCargo, f));
	}*/

	return distritos;

}

/*
 * Devuelve el distrito si no existe el nombre NULL
 */
Distrito* ABMDistrito::GetDistrito(int idDistrito){

	if (ExistsKey(idDistrito)){

		Element* el = bpPlusTree->findExact(idDistrito);

		int idDist= el->getKey();

		string data = el->getData();
        vector<string> splited;
        ProcessData::obtenerData(data,splited);

		if(splited.size() > 0)
			return new Distrito(idDist, splited[0]);
		else
			return new Distrito(idDist, "");
	}
	else{
		return NULL;
	}
}

/**
 * Devuelve true si el distrito existe en el arbol, sino false.
 */
bool ABMDistrito::Exists(Distrito* distrito){

	if(this->bpPlusTree->findExact(distrito->GetId())==NULL)
		return false;
	else
		return true;
}

/**
 * Devuelve true si el distrito existe en el arbol, sino false.
 */
bool ABMDistrito::Exists(int idDistrito){

	if(this->bpPlusTree->findExact(idDistrito) == NULL) return false;
	return true;
}

/**
 * Devuelve true si el distrito existe en el arbol, sino false.
 */
bool ABMDistrito::Exists(string nombreDistrito){

	vector<Distrito> distritosActuales = this->GetDistritos();

	for(int i = 0; i < distritosActuales.size(); i++){
		if(distritosActuales[i].GetNombre() == nombreDistrito)
			return true;
	}
	return false;
}

/*
 * Devuelve true si la key existe en el arbol, sino false.
 */
bool ABMDistrito::ExistsKey(int idDistrito){

	if(this->bpPlusTree->findExact(idDistrito) == NULL)
		return false;

	return true;
}

/*
 * Imprime por pantalla el arbol de distritos
 */
void ABMDistrito::mostrarDistritosPorPantalla(){
	this->bpPlusTree->exportTree();
}

ABMDistrito::~ABMDistrito() {
	delete this->bpPlusTree;
}


