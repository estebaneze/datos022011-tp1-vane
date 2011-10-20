/*
 * Eleccion.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Eleccion.h"

Eleccion::Eleccion(int idCargo, Fecha date) {

	_idCargo = idCargo;
	_date = date;

}


Eleccion::Eleccion(const Eleccion &e) {
	_idCargo = e._idCargo;
	_date = e._date;
}

/* El id lo armamos: fecha_idcargo (NO CON |, PORQUE EN LAS DEMAS ENTIDADES SE CONFUNDIRIA CON LA CLAVE IDENTIFICADOR DEL ARBOL O HASH) */
string Eleccion::GetId(){

	string fecha = _date.getStrFecha();
	string value =  Helper::concatenar(fecha,Helper::IntToString(_idCargo),"_");

	//string str = _date.getStrFecha().append("_");
	//str.append(Helper::IntToString(_idCargo));
	return value;
}


/*int Eleccion::GetId()
{
	return this->_id;
}*/


void Eleccion::RemoveDistrito(int idDistrito){

	_distritos.Remove(idDistrito);
}

void Eleccion::AddDistrito(int idDistrito){

	_distritos.Add(idDistrito);
}

Fecha Eleccion::GetDate(){
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
