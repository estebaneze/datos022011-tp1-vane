/*
 * Votante.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Votante.h"

Votante::Votante(int id, string nombreYApellido, long dni, string clave, string domicilio, int idDistrito) {

	_id = id;
	_nombreYApellido = nombreYApellido;
	_dni = dni;
	_clave = clave;
	_domicilio = domicilio;
	_idDistrito = idDistrito;

}

bool Votante::Authenticate(string clave){

	return (clave == _clave);

}

string Votante::GetNombreYApellido(){
	return _nombreYApellido;
}

long Votante::GetDni(){
	return _dni;
}

string Votante::GetClave(){
	return _clave;
}

string Votante::GetDomicilio(){
	return _domicilio;
}

int Votante::GetDistrito(){
	return _idDistrito;
}

bool Votante::VotoEnEleccion(int idEleccion){

	return (this->_listaElecciones.IsInList(idEleccion));
}

//Ids de las elecciones en las que ya voto
IntegerList Votante::EleccionesVotadas(){
	return _listaElecciones;
}

//Agrega una eleccion a la lista de elccioes en las que voto
void Votante::AgregarEleccion(int idEleccion){

	if(!_listaElecciones.IsInList(idEleccion)){
		_listaElecciones.Add(idEleccion);
	}
}

Votante::~Votante() {
	// TODO Auto-generated destructor stub
}
