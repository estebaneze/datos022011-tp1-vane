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

int Cargo::GetIdCargo(){
	return _idCargo;
}

IntegerList Cargo::GetCargosSecundarios(){
	return _cargosSecundarios;
}

void Cargo::AddCargoSecundario(int idCargo){
	_cargosSecundarios.Add(idCargo);
}

Cargo::~Cargo() {
	// TODO Auto-generated destructor stub
}
