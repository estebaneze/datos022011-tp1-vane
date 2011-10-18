/*
 * ABMCargo.cpp
 *
 *  Created on: 17/10/2011
 *      Author: vanesa
 */

#include "ABMCargo.h"


ABMCargo::ABMCargo(string hashFile) {

	this->hashFile= hashFile;
	this->directorio = new Directory(hashFile,2048);

}


int ABMCargo::Add(string nombre, vector<int> cargosSecundarios){

	int idCargo = Identities::GetNextIdCargo();

	if (!(this->directorio->existKey(Helper::IntToString(idCargo)))){

		string field = nombre.append("|");
		field.append(Helper::concatenar(cargosSecundarios, "|"));
		this->directorio->insert(Helper::IntToString(idCargo), field);

		HashLog::LogProcess(this->directorio,"Cargo_HashProcess.log");
		HashLog::LogInsert(Helper::IntToString(idCargo),field,"Cargo_HashOperation.log");
		return idCargo;
	}
	else{
		return -1;
	}
}

/*Elimina una Candidato, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMCargo::Delete(int idCargo){

	if (this->directorio->existKey(Helper::IntToString(idCargo))){
		this->directorio->remove(Helper::IntToString(idCargo));
		HashLog::LogProcess(this->directorio,"Cargo_HashProcess.log");
		HashLog::LogDelete(Helper::IntToString(idCargo),"","Cargo_HashOperation.log");
		return true;
	}
	else {
		return false;
	}
}

/* Modifica el idEleccion de una candidato pasada por parametro si la encuentra la modifica sino no hace nada */
void ABMCargo::Modify(Cargo cargo){

	string id = Helper::IntToString(cargo.GetId());
	vector<int> cargosSecundarios = cargo.GetCargosSecundarios();

	if (this->directorio->existKey(id)){

		string aux = Helper::concatenar(cargosSecundarios, "|");
		this->directorio->modify(id,aux);
		HashLog::LogProcess(this->directorio,"Cargo_HashProcess.log");
		HashLog::LogModify(Helper::IntToString(cargo.GetId()),aux,"Cargo_HashOperation.log");

	}

}

vector<Cargo> ABMCargo::GetCargos(){

	vector<KeyValue> values = this->directorio->getAllValues();
	vector<Cargo> cargos;

	for(unsigned int i = 0; i < values.size(); i++){

		vector<string> splitedVs = Helper::split(values[i].Value, '|');
		int idCargo = Helper::StringToInt(values[i].Key);
		vector<int> cargosRef;

		for(int i = 1; i < splitedVs.size(); i++){	//el primero lo omito porque es el nombre
			cargosRef.push_back(Helper::StringToInt(splitedVs[i]));
		}

		if(splitedVs.size() > 0){

			if(cargosRef.size() > 0){
				cargos.push_back(Cargo(idCargo, splitedVs[0], cargosRef));
			}
			else{
				cargos.push_back(Cargo(idCargo, splitedVs[0]));
			}
		}

	}

	return cargos;
}

/*
 * Devuelve la candidato si no existe el nombre NULL
 */
Cargo* ABMCargo::GetCargo(int idCargo){

	string cargoId = Helper::IntToString(idCargo);

	if ((this->directorio->existKey(cargoId))){

		string values = directorio->find(cargoId);
		vector<string> splitedVs = Helper::split(values, '|');

		vector<int> cargosSecundarios;
		for(int i = 1; i < splitedVs.size(); i++){	//EL primero lo omito porque es el nombre
			cargosSecundarios.push_back(Helper::StringToInt(splitedVs[i]));
		}

		if(splitedVs.size() > 0){
			if(cargosSecundarios.size() > 0)
				return new Cargo(idCargo, splitedVs[0], cargosSecundarios);
			else
				return new Cargo(idCargo, splitedVs[0]);
		}
		else{
			return NULL;
		}
	}
	else {
		return NULL;
	}

}

bool ABMCargo::Exists(Cargo cargo){
	return this->directorio->existKey(Helper::IntToString(cargo.GetId()));
}

void ABMCargo::mostrarCargosPorPantalla(){
	this->directorio->inform();
}



ABMCargo::~ABMCargo() {
	delete this->directorio;
}

