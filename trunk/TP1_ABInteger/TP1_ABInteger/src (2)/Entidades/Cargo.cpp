/*
 * Cargo.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Cargo.h"

Cargo::Cargo(int idCargo, string nombre) {
	_idCargo = idCargo;
	_nombre = nombre;
}

Cargo::Cargo(int idCargo, string nombre, vector<int> cargosSecundarios) {
	_idCargo = idCargo;
	_cargosSecundarios = cargosSecundarios;
	_nombre = nombre;
}


string Cargo::GetNombre(){
	return _nombre;
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
