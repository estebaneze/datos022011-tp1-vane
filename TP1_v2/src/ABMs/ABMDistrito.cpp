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
ABMDistrito::ABMDistrito(string bpTreeFile) {
	int bufferSize = ConfigurationMananger::getInstance()->getBufferSizeTree();
	this->bpPlusTree = new BPlusTree(bufferSize,Helper::concatenar(bpTreeFile,"bpt","."));
}

/*
 * Agrego un distrito, lo guarda en en arbol
 */
int ABMDistrito::Add(string nombre){

	int idDistrito = Identities::GetNextIdDistrito();
	//cout<<"antes in"<<endl;

	if (!Exists(nombre)){
	//	cout<<"antes jfkdjfin"<<endl;

		Data data = (Data)nombre.c_str();
		//cout << "Insertando el D: " << idDistrito << nombre << endl;

		int longData = nombre.length();
		Element * elemento = new Element(Helper::IntToString(idDistrito),data,longData);
		//cout<<"antes insert"<<endl;

		this->bpPlusTree->insert(elemento);
		//logueo el add
		BPlusTreeLog::LogInsert(Helper::IntToString(idDistrito),data,"Distrito_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Distrito_BPlusTreeProccess.log");

		return idDistrito;
	}

	cout << "El Distrito con el nombre " << nombre << " ya fue ingresado " << endl;
	return -1;
}

/*
 * Elimina un Distrito, si no exite devuelve false, existe y lo elimina devuelve true
 */
bool ABMDistrito::Delete(int idDistrito){

	if (ExistsKey(Helper::IntToString(idDistrito))){
		Distrito * d = this->GetDistrito(idDistrito);
		this->bpPlusTree->remove(Helper::IntToString(idDistrito));
		//logueo el delete
		BPlusTreeLog::LogDelete(Helper::IntToString(idDistrito),d->GetNombre(),"Distrito_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Distrito_BPlusTreeProccess.log");
		return true;
	} else return false;
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
		//logueo el modify
		BPlusTreeLog::LogModify(Helper::IntToString(distrito.GetId()),data,"Distrito_BPlusTreeOperation.log");
		BPlusTreeLog::LogProcess(this->bpPlusTree,"Distrito_BPlusTreeProccess.log");
		this->bpPlusTree->modify(elemento);
	}
}

/*
 * Falta implementar
 *TODO: implementar
 */
vector<Distrito> ABMDistrito::GetDistritos(){

	cout << endl << endl << "************WARNING: IMPLEMENTAR " << "ABMDistrito::GetDistritos()" << endl << endl;

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
	else
		return true;
}

/**
 * Devuelve true si el distrito existe en el arbol, sino false.
 */
bool ABMDistrito::Exists(int idDistrito){
	if(this->bpPlusTree->findExact(Helper::IntToString(idDistrito))==NULL)
		return false;
	else return true;
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


