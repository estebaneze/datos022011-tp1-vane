/*
 * Eleccion.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Eleccion.h"

Eleccion::Eleccion(int idCargo, Date date) {

	_idCargo = idCargo;
	_date = date;

}

void Eleccion::RemoveDistrito(int idDistrito){

	//_distritos.Remove(idDistrito);
}

int Eleccion::GetId(){
	return _id;
}

void Eleccion::AddDistrito(int idDistrito){

	_distritos.push_back(idDistrito);
}

Date Eleccion::GetDate(){
	return _date;
}

int Eleccion::GetIdCargo(){
	return _idCargo;
}

vector<int> Eleccion::GetDistritos(){
	return _distritos;
}

Eleccion::~Eleccion() {
	// TODO Auto-generated destructor stub
}
