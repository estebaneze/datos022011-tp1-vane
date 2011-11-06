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
			//string auxValueBtree;
			vector<int> distritos = eleccion->GetDistritos();
			string concatDistritos = "";

			if(distritos.size() > 0){
				concatDistritos = Helper::concatenar(distritos, ConfigurationMananger::getInstance()->getSeparador1());
				concatDistritos.append("|");
			}

			//data = fecha|idcargo|distritos
			string str = eleccion->GetDate().getStrFecha().append("|").append(Helper::IntToString(eleccion->GetIdCargo())).append("|").append(concatDistritos);
			Data data = (Data)str.c_str();

			int longData = str.length();
			Element * elemento = new Element(idEleccion,data,longData);
			this->bpPlusTree->insert(elemento);

			//logueo el add
			BPlusTreeLog::LogInsert(idEleccion,str,ConfigurationMananger::getInstance()->getLogOperEleccionFile());
			BPlusTreeLog::LogProcess(this->bpPlusTree,ConfigurationMananger::getInstance()->getLogProcessEleccionFile());

			//Agrego al indice

			this->indexByFecha->AppendToIndex(eleccion->GetDate().getStrFecha(),Helper::IntToString(idEleccion));
			this->indexByCargo->AppendToIndex(eleccion->GetIdCargo(),Helper::IntToString(idEleccion));

			//Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
			distritos = eleccion->GetDistritos();
			for(int i = 0; i< distritos.size(); i++){
				this->indexByDistrito->AppendToIndex(Helper::IntToString(distritos[i]), Helper::IntToString(idEleccion));
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
bool ABMEleccion::Delete(Eleccion* eleccion){

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
                this->indexByFecha->DeleteFromIndex(eleccion->GetDate().getStrFecha(),Helper::IntToString(idEleccion));
                this->indexByCargo->DeleteFromIndex(eleccion->GetIdCargo(),Helper::IntToString(idEleccion));

                //Indice por distritos. Los registros de este indice son: clave->idDistrito, value->ideleccion1|ideleccion2|.....
                for(int i = 0; i< distritos.size(); i++){
                        this->indexByDistrito->DeleteFromIndex(Helper::IntToString(distritos[i]), Helper::IntToString(idEleccion));
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

        int idEleccion =  ObtenerKey(eleccion);

        if (Exists(eleccion)){

               //primero borro el id de eleccion indexado en el indice de distritos, despues agrego los que tengo ahora
                Eleccion* old = this->GetEleccion(idEleccion);
                vector<int> oldDistritos = old->GetDistritos(); //Me traigo los distritos que tiene ahora (antes de modificarla)
                for(int i = 0; i< oldDistritos.size(); i++){
                	this->indexByDistrito->DeleteFromIndex(Helper::IntToString(oldDistritos[i]), Helper::IntToString(idEleccion));
                }

                vector<int> distritos = eleccion->GetDistritos();
                string concatDistritos = Helper::concatenar(distritos, ConfigurationMananger::getInstance()->getSeparador1()).append(ConfigurationMananger::getInstance()->getSeparador1());

                //data = fecha|idcargo|distritos
                string str = eleccion->GetDate().getStrFecha().append("|").append(Helper::IntToString(eleccion->GetIdCargo())).append("|").append(concatDistritos);
                Data data = (Data)str.c_str();
                int longData = str.length();
                Element * elemento = new Element(idEleccion,data,longData);
                this->bpPlusTree->modify(elemento);

                //logueo el modify
                BPlusTreeLog::LogModify(idEleccion,str,ConfigurationMananger::getInstance()->getLogOperEleccionFile());
                BPlusTreeLog::LogProcess(this->bpPlusTree,ConfigurationMananger::getInstance()->getLogProcessEleccionFile());

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

                return eleccion;
        }
        else {
                return NULL;
        }
}


/**
 * Devuelve key si el eleccion existe en el arbol, sino -1.
 */
int ABMEleccion::ObtenerKey(Eleccion* eleccion){

	vector<Key> byFecha = this->indexByFecha->GetIds(eleccion->GetDate().getStrFecha());
	vector<Key> byCargo = this->indexByCargo->GetIds(Helper::IntToString(eleccion->GetIdCargo()));
	for(int i = 0; i< byCargo.size(); i++){
		for(int j = 0; j< byFecha.size(); j++){
			 if (byCargo[i]==byFecha[j]) return Helper::StringToInt(byCargo[i]);
		}
	} return -1;
}


/**
 * Devuelve true si el eleccion existe en el arbol, sino false
 */
bool ABMEleccion::Exists(Eleccion* eleccion){

	vector<Key> byFecha = this->indexByFecha->GetIds(eleccion->GetDate().getStrFecha());
	vector<Key> byCargo = this->indexByCargo->GetIds(Helper::IntToString(eleccion->GetIdCargo()));

	for(int i = 0; i< byCargo.size(); i++){
		for(int j = 0; j< byFecha.size(); j++){
			 if (byCargo[i]==byFecha[j]) return true;
		}
	} return false;
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

vector<Eleccion*> ABMEleccion::GetByFechaYCargo(Fecha* fecha, int idCargo){

    vector<Key> byFecha = this->indexByFecha->GetIds(fecha->getStrFecha());
    vector<Eleccion*> elecciones;

    for(int i = 0; i < byFecha.size(); i++){

    	Eleccion* e = this->GetEleccion(Helper::StringToInt(byFecha[i]));

    	if(e->GetIdCargo() == idCargo)
    		elecciones.push_back(e);
    }

    return elecciones;
}

vector<Eleccion*> ABMEleccion::GetByFecha(Fecha* fecha){

	vector<Key> byFecha = this->indexByFecha->GetIds(fecha->getStrFecha());
	vector<Eleccion*> elecciones;

	for(int i = 0; i < byFecha.size(); i++){
		Eleccion* e = this->GetEleccion(Helper::StringToInt(byFecha[i]));
		elecciones.push_back(e);
	}

	return elecciones;
}

vector<Eleccion*> ABMEleccion::GetByFechaYDistrito(Fecha* fecha, int idDistrito){

        vector<Key> byFecha = this->indexByFecha->GetIds(fecha->getStrFecha());
    	vector<Eleccion*> elecciones;

    	for(int i = 0; i < byFecha.size(); i++){

    		Eleccion* e = this->GetEleccion(Helper::StringToInt(byFecha[i]));

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

	vector<Key> byFecha = this->indexByDistrito->GetIds(Helper::IntToString(idDistrito));
	vector<Eleccion*> elecciones;

	for(int i = 0; i < byFecha.size(); i++){
		Eleccion* e = this->GetEleccion(Helper::StringToInt(byFecha[i]));
		elecciones.push_back(e);
	}

	return elecciones;
}


ABMEleccion::~ABMEleccion() {
        delete this->bpPlusTree;
        delete this->indexByFecha;
}
