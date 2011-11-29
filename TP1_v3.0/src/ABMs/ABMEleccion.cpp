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

	string mainTreeName = ConfigurationMananger::getInstance()->getEleccionFile();
	mainTreeName = Helper::concatenar(mainTreeName,"bpt",".");

	this->bpTreeFile = mainTreeName;

	int bufferSize = ConfigurationMananger::getInstance()->getBufferSizeTree();

	this->bpPlusTree = new BPlusTree(bufferSize,bpTreeFile);

	this->indexByFecha = new Index(Helper::concatenar(bpTreeFile,"Fecha",ConfigurationMananger::getInstance()->getSeparador2()));
	this->indexByDistrito = new Index(Helper::concatenar(bpTreeFile,"Distrito",ConfigurationMananger::getInstance()->getSeparador2()));
	this->indexByCargo = new Index(Helper::concatenar(bpTreeFile,"Cargo",ConfigurationMananger::getInstance()->getSeparador2()));
}

/*
 * Agrego una eleccion, lo guarda en en arbol
 */
int ABMEleccion::Add(Eleccion* eleccion){


	if (!Exists(eleccion)){

		int idEleccion = Identities::GetNextIdEleccion();//eleccion->GetId(); //NO PUEDO HACER EL ID DE LA ELECCION CON "|" PORQUE SE CONFUNDE CUANDO LO QUIERO USAR EN LAS OTRAS ENTIDADES

		//cout << "Insertando la eleccion: " << idEleccion << endl << endl;
		vector<int> distritos = eleccion->GetDistritos();

		string sdata = ProcessData::generarDataEleccion(eleccion->GetDate().getint(),eleccion->GetIdCargo(),distritos);
		Data data = (Data)sdata.c_str();

		int longData = sdata.length();
		Element * elemento = new Element(idEleccion, data, longData);

		this->bpPlusTree->insert(elemento);

		//log info
		string concatDistritos = "";

		if(distritos.size() > 0){
			concatDistritos = Helper::concatenar(distritos, ConfigurationMananger::getInstance()->getSeparador1());
			concatDistritos.append("|");
		}

		//log info data = fecha|idcargo|distritos
		string str = eleccion->GetDate().getStrFecha().append("|").append(Helper::IntToString(eleccion->GetIdCargo())).append("|").append(concatDistritos);

		//logueo el add
		BPlusTreeLog::LogInsert(idEleccion,str,ConfigurationMananger::getInstance()->getLogOperEleccionFile());
		BPlusTreeLog::LogProcess(this->bpPlusTree,ConfigurationMananger::getInstance()->getLogProcessEleccionFile());

		//Agrego al indice

		this->indexByFecha->AppendToIndex(eleccion->GetDate().getint(),idEleccion);

		this->indexByCargo->AppendToIndex(eleccion->GetIdCargo(), idEleccion);

		//Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
		distritos = eleccion->GetDistritos();
		for(int i = 0; i< distritos.size(); i++){
			this->indexByDistrito->AppendToIndex(distritos[i], idEleccion);
		}

		return idEleccion;
	}

	else {
		cout << "Ya existe la eleccion (Fecha y Cargo) ingresada (Fecha: " << eleccion->GetDate().getFriendlyStr() << " - Cargo: " << eleccion->GetIdCargo() << endl;
		return -1;
	}
}

/*
 * Si existe la eleccion la eliget mina y devuelve true, sino devuelve false
 */
/*bool ABMEleccion::Delete(Eleccion* eleccion){

		int idEleccion =  ObtenerKey(eleccion);

        if (Exists(eleccion)){

                vector<int> distritos = eleccion->GetDistritos();

                this->bpPlusTree->remove(idEleccion);
                string auxValueBtree;

                for (unsigned int i=0;i<(eleccion->GetDistritos().size());i++){
                        auxValueBtree = Helper::concatenar(auxValueBtree,Helper::IntToString(eleccion->GetDistritos()[i]),ConfigurationMananger::getInstance()->getSeparador1());
                }

                //logueo el delete
                BPlusTreeLog::LogDelete(idEleccion,auxValueBtree,ConfigurationMananger::getInstance()->getLogOperEleccionFile());
                BPlusTreeLog::LogProcess(this->bpPlusTree,ConfigurationMananger::getInstance()->getLogProcessEleccionFile());

                //Elimino del indice
                this->indexByFecha->DeleteFromIndex(eleccion->GetDate().getStrFecha(),Helper::copyBytesToString(idEleccion));
                this->indexByCargo->DeleteFromIndex(Helper::copyBytesToString(eleccion->GetIdCargo()),Helper::copyBytesToString(idEleccion));

                //Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
                for(int i = 0; i< distritos.size(); i++){
                        this->indexByDistrito->DeleteFromIndex(Helper::copyBytesToString(distritos[i]), Helper::copyBytesToString(idEleccion));
                }

                return true;

        } else {
            return false;
        }
}*/

/*
 * Modifica la eleccion pasada por parametro si lo encuentra, sino no hace nada
*/
/*bool ABMEleccion::Modify(Eleccion* eleccion){

        int idEleccion =  ObtenerKey(eleccion);
cout << "modify eleccion 1 " << endl;
        if (Exists(eleccion)){
        	cout << "modify eleccion 2 " << endl;
		   //primero borro el id de eleccion indexado en el indice de distritos, despues agrego los que tengo ahora
			Eleccion* old = this->GetEleccion(idEleccion);
			vector<int> oldDistritos = old->GetDistritos(); //Me traigo los distritos que tiene ahora (antes de modificarla)
			for(int i = 0; i< oldDistritos.size(); i++){
				this->indexByDistrito->DeleteFromIndex(Helper::copyBytesToString(oldDistritos[i]), Helper::copyBytesToString(idEleccion));
			}

			cout << "modify eleccion 3 " << endl;
			vector<int> distritos = eleccion->GetDistritos();
			string sdata = ProcessData::generarDataEleccion(eleccion->GetDate().getStrFecha(),eleccion->GetIdCargo(),distritos);
			Data data = (Data)sdata.c_str();
			cout << "modify eleccion 4 " << endl;
			int longData = sdata.length();
			Element * elemento = new Element(idEleccion,data,longData);
			this->bpPlusTree->modify(elemento);

			//logueo el modify
			string concatDistritos = Helper::concatenar(distritos, ConfigurationMananger::getInstance()->getSeparador1()).append(ConfigurationMananger::getInstance()->getSeparador1());

			//data = fecha|idcargo|distritos
			string str = eleccion->GetDate().getStrFecha().append("|").append(Helper::IntToString(eleccion->GetIdCargo())).append("|").append(concatDistritos);

			BPlusTreeLog::LogModify(idEleccion,str,ConfigurationMananger::getInstance()->getLogOperEleccionFile());
			BPlusTreeLog::LogProcess(this->bpPlusTree,ConfigurationMananger::getInstance()->getLogProcessEleccionFile());

			//Aca no hay que modificar el indice, ya que lo que se indexa es la fecha, que me devuelve los ids de elcciones correspondientes
					//a esa fecha, pero eso nunca se modifica.

			//Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
			distritos = eleccion->GetDistritos();
			for(int i = 0; i< distritos.size(); i++){
				  this->indexByDistrito->AppendToIndex(Helper::copyBytesToString(distritos[i]), Helper::copyBytesToString(eleccion->GetId()));
			}

			return true;
        }

        return false;
}*/

/*
 * Falta implementar
 */
/*
vector<Eleccion> ABMEleccion::GetElecciones(){

	cout << endl << endl;
	cout << "****************************** Warning ********************************************" << endl;
	cout << "------------------------- ABMEleccion::GetElecciones NOT IMPLEMENTED ------------------------------" << endl;
	cout << "***********************************************************************************" << endl;
	cout << endl << endl;

	vector<Eleccion> es;
	return es;
}*/


Eleccion* ABMEleccion::GetEleccion(int idEleccion){

	if (ExistsKey(idEleccion)){

		Element * el = this->bpPlusTree->findExact(idEleccion);
		char* data = el->getData();

		//data = fecha|idcargo|distritos

		int sfecha;
		vector<int> distritos;
		int idCargo;
		ProcessData::obtenerDataEleccion(data, el->getDataSize(), sfecha, idCargo, distritos);
		//TODO: no anda bien obtenerData para devolver la fecha

		Fecha fecha = Fecha(Helper::IntToString(sfecha));

		//Busco  los distritos
		Eleccion * eleccion =  new Eleccion(idCargo, fecha, idEleccion);

		for(int i = 0; i < distritos.size(); i++){
			eleccion->AddDistrito(distritos[i]);
		}

		return eleccion;
	}
	else {
		return NULL;
	}
}


/**
 * Devuelve key si el eleccion existe en el arbol, sino -1.
 */
/*int ABMEleccion::ObtenerKey(Eleccion* eleccion){

	vector<Key> byFecha = this->indexByFecha->GetIds(Helper::copyBytesToString(eleccion->GetDate().getint()));
	vector<Key> byCargo = this->indexByCargo->GetIds(Helper::copyBytesToString(eleccion->GetIdCargo()));
	for(int i = 0; i< byCargo.size(); i++){
		for(int j = 0; j< byFecha.size(); j++){
			 if (byCargo[i]==byFecha[j]) return Helper::copyBytesToInt(byCargo[i]);
		}
	} return -1;
}*/


/**
 * Devuelve true si el eleccion existe en el arbol, sino false
 */
bool ABMEleccion::Exists(Eleccion* eleccion){

	Fecha* fecha = new Fecha(eleccion->GetDate());
	Eleccion* e = this->GetByFechaYCargo(fecha, eleccion->GetIdCargo());

	if(e == NULL)
		return false;

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
 * Imprime por pantalla el arbol de elecciones
 */
void ABMEleccion::mostrarEleccionesPorPantalla(){
	this->bpPlusTree->exportTree();
}

Eleccion* ABMEleccion::GetByFechaYCargo(Fecha* fecha, int idCargo){

	// TODO: REVISAR Eleccion: GetByFechaYCargo
    vector<int> byFecha = this->indexByFecha->GetIdsInt(fecha->getint());
    vector<Eleccion*> elecciones;

    //DEBERIA HABER UNA  UNICA ELECCION POR FECHA Y CARGO
    if(byFecha.size() == 0){
        return NULL;
    }
    else{

    	for(int i = 0; i < byFecha.size(); i++){
			Eleccion* e = this->GetEleccion(byFecha[i]);
			if(e->GetIdCargo() == idCargo)
				return e;
    	}
    }

    return NULL;
}

vector<Eleccion*> ABMEleccion::GetByFecha(Fecha* fecha){

	// TODO: REVISAR Eleccion: GetByFecha
	vector<int> byFecha = this->indexByFecha->GetIdsInt(fecha->getint());
	vector<Eleccion*> elecciones;

	for(int i = 0; i < byFecha.size(); i++){
		Eleccion* e = this->GetEleccion(byFecha[i]);
		elecciones.push_back(e);
	}

	return elecciones;
}

vector<Eleccion*> ABMEleccion::GetByFechaYDistrito(Fecha* fecha, int idDistrito){

	vector<int> byFecha = this->indexByFecha->GetIdsInt(fecha->getint());
	vector<Eleccion*> elecciones;

	for(int i = 0; i < byFecha.size(); i++){

		Eleccion* e = this->GetEleccion(byFecha[i]);

		vector<int> distritos = e->GetDistritos();
		bool founed = false;
		for(int i = 0; i < distritos.size() && !founed; i++){
			if(distritos[i] == idDistrito){
				elecciones.push_back(e);
				founed = true;
			}
		}

	}

	return elecciones;
}

vector<Eleccion*> ABMEleccion::GetByDistrito(int idDistrito){

	vector<int> byFecha = this->indexByDistrito->GetIdsInt(idDistrito);
	vector<Eleccion*> elecciones;

	for(int i = 0; i < byFecha.size(); i++){
		Eleccion* e = this->GetEleccion(byFecha[i]);
		elecciones.push_back(e);
	}

	return elecciones;
}


ABMEleccion::~ABMEleccion() {
	delete this->bpPlusTree;
//	delete this->indexByFecha;
//	delete this->indexByDistrito;
//	delete this->indexByFecha;
}
