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

	_distritos.Remove(idDistrito);
}

void Eleccion::AddDistrito(int idDistrito){

	_distritos.Add(idDistrito);
}

Date Eleccion::GetDate(){
	return _date;
}

int Eleccion::GetIdCargo(){
	return _idCargo;
}

IntegerList Eleccion::GetDistritos(){
	return _distritos;
}

Eleccion::~Eleccion() {
	// TODO Auto-generated destructor stub
}
