/*
 * ABMCargo.cpp
 *
 *  Created on: 17/10/2011
 *      Author: vanesa
 */

#include "ABMCargo.h"


ABMCargo::ABMCargo() {
	int maxBucketSize = ConfigurationMananger::getInstance()->getHashBSizeCargo();
	this->hashFile= ConfigurationMananger::getInstance()->getCargoFile();
	this->directorio = new Directory(hashFile, maxBucketSize);
}


int ABMCargo::Add(string nombre, vector<int> cargosSecundarios){

         //if (!(this->directorio->existKey(Helper::IntToString(idCargo)))){
	if(!this->Exists(nombre)){      //Si no existe un cargo con el mismo nombre

		int idCargo = Identities::GetNextIdCargo();

		string data = ProcessData::generarDataCargo(nombre, cargosSecundarios);

		this->directorio->insert(Helper::copyBytesToString(idCargo), data);

		//LOGUEO
		string field = nombre.append("|");
		field.append(Helper::concatenar(cargosSecundarios, ConfigurationMananger::getInstance()->getSeparador1()));

		HashLog::LogProcess(this->directorio,ConfigurationMananger::getInstance()->getLogProcessCargoFile());
		HashLog::LogInsert(Helper::IntToString(idCargo),field,ConfigurationMananger::getInstance()->getLogOperCargoFile());

		//Actualizo la lista de cargos del abm *******++ si queda tiempo lo implemento bien (Vane)
		//this->cargos.push_back(Cargo(idCargo, nombre, cargosSecundarios));

		return idCargo;
	}
	else{
		cout << "El Cargo con el nombre " << nombre << " ya fue ingresado " << endl;
		return -1;
	}
}

/*Elimina una Cargo, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMCargo::Delete(int idCargo){

        if (this->directorio->existKey(Helper::copyBytesToString(idCargo))){

                this->directorio->remove(Helper::copyBytesToString(idCargo));

                //LOGUEO
                HashLog::LogProcess(this->directorio,"Cargo_HashProcess.log");
                HashLog::LogDelete(Helper::IntToString(idCargo),"","Cargo_HashOperation.log");

                //Actualizo la lista de cargos del abm *******++ si queda tiempo lo implemento bien (Vane)
                /*int index = 0;
                for(index = 0; index < cargos.size(); index++){

                        if(cargos[index].GetId() == idCargo){
                                break;
                        }
                }

                //borro del vector el elemento en la posicion i
                if(index < this->cargos.size()){
                        this->cargos.erase(cargos.begin() + index);
                }
                        */

                return true;
        }
        else {
                return false;
        }
}

/* Modifica el idEleccion de una candidato pasada por parametro si la encuentra la modifica sino no hace nada */
void ABMCargo::Modify(Cargo cargo){

        string id = Helper::copyBytesToString(cargo.GetId());
        vector<int> cargosSecundarios = cargo.GetCargosSecundarios();

        if (this->directorio->existKey(id)){

        	string data = ProcessData::generarDataCargo(cargo.GetNombre(),cargosSecundarios);
        	this->directorio->modify(id,data);

        	//LOGUEO
			string aux = Helper::concatenar(cargosSecundarios, ConfigurationMananger::getInstance()->getSeparador1());

            HashLog::LogProcess(this->directorio,"Cargo_HashProcess.log");
            HashLog::LogModify(Helper::IntToString(cargo.GetId()),aux,"Cargo_HashOperation.log");

                /*
                //Actualizo la lista de cargos del abm *******++ si queda tiempo lo implemento bien (Vane)
                for(int i = 0; i < cargos.size(); i++){
                        if(cargos[i].GetId() == cargo.GetId()){
                                cargos[i] = cargo;
                                break;
                        }
                }
                */
        }
}

vector<Cargo> ABMCargo::GetCargos(){

        vector<KeyValue> values = this->directorio->getAllValues();
        vector<Cargo> cargos;


        for(unsigned int i = 0; i < values.size(); i++){

                vector<int> cargosSec;
                string nombre;

                ProcessData::obtenerDataCargo(values[i].Value, nombre, cargosSec );

                int idCargo = Helper::copyBytesToInt(values[i].Key);

                if(cargosSec.size() > 0){
                	cargos.push_back(Cargo(idCargo, nombre, cargosSec));
                }
                else{
                    cargos.push_back(Cargo(idCargo, nombre));
                }


        }

        return cargos;
}

/*
 * Devuelve la candidato si no existe el nombre NULL
 */
Cargo* ABMCargo::GetCargo(int idCargo){

        string cargoId = Helper::copyBytesToString(idCargo);

        if ((this->directorio->existKey(cargoId))){

        	string values = directorio->find(cargoId);
        	vector<int> cargosSecundarios;
        	string nombre;
        	ProcessData::obtenerDataCargo(values,nombre,cargosSecundarios);

            if(cargosSecundarios.size() > 0)
            	return new Cargo(idCargo, nombre, cargosSecundarios);
            else
                    return new Cargo(idCargo, nombre);
        }
        else{
        	return NULL;
        }



}

bool ABMCargo::Exists(Cargo cargo){
        return this->directorio->existKey(Helper::copyBytesToString(cargo.GetId()));
}

bool ABMCargo::Exists(int id){
        return this->directorio->existKey(Helper::copyBytesToString(id));
}


bool ABMCargo::Exists(string nombreCargo){

        vector<Cargo> cargosActuales = this->GetCargos();

        for(unsigned int i = 0; i < cargosActuales.size(); i++){

                if(cargosActuales[i].GetNombre() == nombreCargo)
                        return true;
        }

        return false;
}

void ABMCargo::mostrarCargosPorPantalla(){
        this->directorio->inform();
}



ABMCargo::~ABMCargo() {
        delete this->directorio;
}

