/*
 * Cargo.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Cargo.h"

Cargo::Cargo(int idCargo) {
	_idCargo = idCargo;
}

Cargo::Cargo(int idCargo, vector<int> cargosSecundarios) {
	_idCargo = idCargo;
	_cargosSecundarios = cargosSecundarios;
}


int Cargo::GetId(){
	return _idCargo;
}

vector<int> Cargo::GetCargosSecundarios(){
	return _cargosSecundarios;
}

void Cargo::AddCargoSecundario(int idCargo){
	_cargosSecundarios.push_back(idCargo);
}

Cargo::~Cargo() {
	// TODO Auto-generated destructor stub
}
