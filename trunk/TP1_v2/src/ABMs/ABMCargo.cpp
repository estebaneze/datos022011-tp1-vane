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


void ABMCargo::Add(string nombre, vector<int> cargosSecundarios){

	int idCargo = Identities::GetNextIdCargo();

	if (!(this->directorio->existKey(Helper::IntToString(idCargo)))){
		this->directorio->insert(Helper::IntToString(idCargo), Helper::concatenar(cargosSecundarios, "|"));
	}
}

/*Elimina una Candidato, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMCargo::Delete(int idCargo){

	if (this->directorio->existKey(Helper::IntToString(idCargo))){
		return (this->directorio->remove(Helper::IntToString(idCargo)));
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

		this->directorio->modify(id,Helper::concatenar(cargosSecundarios, "|"));
	}

}

vector<Cargo> ABMCargo::GetCargos(){

	vector<KeyValue> values = this->directorio->getAllValues();
	vector<Cargo> cargos;

	for(unsigned int i = 0; i < values.size(); i++){

		vector<string> splitedVs = Helper::split(values[i].Value, '|');
		int idCargo = Helper::StringToInt(values[i].Key);
		vector<int> cargosRef;

		for(int i = 0; i < splitedVs.size(); i++){
			cargosRef.push_back(Helper::StringToInt(splitedVs[i]));
		}

		cargos.push_back(Cargo(idCargo, cargosRef));

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
		for(int i = 0; i < splitedVs.size(); i++){
			cargosSecundarios.push_back(Helper::StringToInt(splitedVs[i]));
		}

		return new Cargo(idCargo, cargosSecundarios);
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

