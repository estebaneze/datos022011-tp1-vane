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

/* Le suma un voto al registro y devuelve la cantidad de votos totales */
void ABMConteo::AddVoto(int idConteo, Votante* votante){

	Conteo* c = this->GetConteo(idConteo);

	if(votante->VotoEnEleccion(c->GetIdEleccion())){
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\n\n\El votante " << votante->GetNombreYApellido() << " ya voto en la elecci�n " << c->GetIdEleccion() << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;

	}

	if(c != NULL){

		c->AddVoto();

		Key key = Helper::IntToString(idConteo);
		string str = c->GetIdLista();										//agrego lista
		str.append("|").append(Helper::IntToString(c->GetIdDistrito()));	//agrego id Distrot
		str.append("|").append(Helper::IntToString(c->GetIdEleccion()));	//agrego id eleccion
		str.append("|").append(Helper::IntToString(c->GetCountVotos()));	//agrego cantidad de votos
		Data data = (Data)str.c_str();
		int longData = str.length();

		Element * element=new Element(key, data, longData);
		this->bplusTree->modify(element);

		this->NotifyVotante(votante, c->GetIdEleccion());

		cout <<endl<<endl<<endl <<  "Usted voto la Lista " << c->GetIdLista() << ". Tiene un total del votos de: " << c->GetCountVotos() << endl;
	}

	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\n\n\Error: no se encontro el registro de conteo para realizar la votacion " << c->GetIdEleccion() << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;

}

/* Le avisa al Votante que ya voto en esta eleccion */
void ABMConteo::NotifyVotante(Votante* votante, int idEleccion){

	//Hay que guardar en la entidad Votante el ide de eleccion, para que quede el registro de que ya voto en esta eleccion y no puede volver a votar
	ABMVotante abmVotantes = ABMVotante();
	votante->AgregarEleccion(idEleccion);

	//(long dni, string nombreYApellido, string clave, string domicilio, int idDistrito);
	Votante v = Votante(votante->GetDni(), votante->GetNombreYApellido(), votante->GetClave(), votante->GetDomicilio(), votante->GetDistrito());
	v.SetEleccionesVotadas(votante->GetEleccionesVotadas());

	abmVotantes.Modify(v);
}

/*Busca el registro de Conteo segun la lisa, distrito y eleccion y le suma un voto. Devuelve la cantidad de votos totales*/
void ABMConteo::AddVoto(string idLista, int idDistrito, int idEleccion, Votante* votante){

	vector<Conteo> byEleccion = this->GetConteoByEleccion(idEleccion);

	//Busco dentro de los que corresponden a la Eleccion, los que correspondan al distrito
	Conteo c;
	bool founded = false;
	for(int i = 0; i < byEleccion.size() && !founded; i++){
		if(byEleccion[i].GetIdDistrito() == idDistrito && byEleccion[i].GetIdLista() == idLista){
			c = byEleccion[i];
			founded = true;
		}
	}

	if(!founded){
		cout << "Error: ----------------- No se puede realizar la votaci�n para la Lista " << idLista <<  " en el Distrito " << idDistrito << " en la Eleccion " << idEleccion << endl;
	}

	int cantVotos = c.AddVoto();

	Key key = Helper::IntToString(c.GetId());
	string str = idLista;
	str.append("|").append(Helper::IntToString(idDistrito));	//agrego id Distrot
	str.append("|").append(Helper::IntToString(idEleccion));	//agrego id eleccion
	str.append("|").append(Helper::IntToString(cantVotos));	//agrego cantidad de votos
	Data data = (Data)str.c_str();
	int longData = str.length();

	Element * element=new Element(key, data, longData);
	this->bplusTree->modify(element);

	this->NotifyVotante(votante, c.GetIdEleccion());
}

Conteo* ABMConteo::GetConteo(int idConteo){

	Element* elemento = this->bplusTree->findExact(Helper::IntToString(idConteo));
	vector<string> splited = Helper::split(elemento->getData(), '|');
	int cantVotos = 0;

	if(splited.size() == 4){	//si ya tiene registrado algun voto

		cantVotos = Helper::StringToInt(splited[3]);
	}

	return new Conteo(splited[0], Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), idConteo, cantVotos);
}

vector<Conteo> ABMConteo::GetConteoByDistrito(int idDistrito){

	vector<Conteo> conteos;
	vector<Key> ids = this->indexByDistrito->GetIds(Helper::IntToString(idDistrito));

	for(int i = 0; i < ids.size(); i++){

		int kint = Helper::StringToInt(ids[i]);
		Element* elemento = this->bplusTree->findExact(ids[i]);
		vector<string> splited = Helper::split(elemento->getData(), '|');
		int cantVotos = 0;
		if(splited.size() == 4){	//si ya tiene registrado algun voto
			cantVotos = Helper::StringToInt(splited[3]);
		}

		conteos.push_back(Conteo(splited[0], Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), kint, cantVotos));
	}

	return conteos;
}

vector<Conteo> ABMConteo::GetConteoByEleccion(int idEleccion){


	vector<Conteo> conteos;
	vector<Key> ids = this->indexByEleccion->GetIds(Helper::IntToString(idEleccion));

	for(int i = 0; i < ids.size(); i++){

		int kint = Helper::StringToInt(ids[i]);
		Element* elemento = this->bplusTree->findExact(ids[i]);
		vector<string> splited = Helper::split(elemento->getData(), '|');
		int cantVotos = 0;
		if(splited.size() == 4){	//si ya tiene registrado algun voto
			cantVotos = Helper::StringToInt(splited[3]);
		}

		conteos.push_back(Conteo(splited[0], Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), kint, cantVotos));
	}

	return conteos;
}

vector<Conteo> ABMConteo::GetConteoByLista(string idLista){


	vector<Conteo> conteos;
	vector<Key> ids = this->indexByLista->GetIds(idLista);

	for(int i = 0; i < ids.size(); i++){

		int kint = Helper::StringToInt(ids[i]);
		Element* elemento = this->bplusTree->findExact(ids[i]);
		vector<string> splited = Helper::split(elemento->getData(), '|');
		int cantVotos = 0;
		if(splited.size() == 4){	//si ya tiene registrado algun voto
			cantVotos = Helper::StringToInt(splited[3]);
		}

		conteos.push_back(Conteo(splited[0], Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), kint, cantVotos));
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


