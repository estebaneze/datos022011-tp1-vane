/*
 * Votante.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Votante.h"

Votante::Votante(long dni, string nombreYApellido, string clave, string domicilio, int idDistrito) {

	_dni = dni;
	_nombreYApellido = nombreYApellido;
	_clave = clave;
	_domicilio = domicilio;
	_idDistrito = idDistrito;
	_listaElecciones = IntegerList();
}

bool Votante::Authenticate(string clave){
	return (clave == _clave);
}

long Votante::GetDni(){
	return _dni;
}

string Votante::GetNombreYApellido(){
	return _nombreYApellido;
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

//Ids de las elecciones en las que ya voto
IntegerList Votante::GetEleccionesVotadas(){
	return _listaElecciones;
}

void Votante::SetClave(string clave)
{
    _clave = clave;
}

void Votante::SetDni(long  dni)
{
    _dni = dni;
}

void Votante::SetDomicilio(string domicilio)
{
    _domicilio = domicilio;
}

void Votante::SetIdDistrito(int idDistrito)
{
    _idDistrito = idDistrito;
}

void Votante::SetNombreYApellido(string nombreYApellido)
{
    _nombreYApellido = nombreYApellido;
}

bool Votante::VotoEnEleccion(int idEleccion){

	return (this->_listaElecciones.IsInList(idEleccion));
}

//Agrega una eleccion a la lista de elccioes en las que voto
void Votante::AgregarEleccion(int idEleccion){

	if(!_listaElecciones.IsInList(idEleccion)){
		_listaElecciones.Add(idEleccion);
	}
}

void Votante::SetEleccionesVotadas(IntegerList eleccionesVotadas){
	this->_listaElecciones = eleccionesVotadas;
}

Votante::~Votante() {
	// TODO Auto-generated destructor stub
}
