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
//	_listaElecciones = IntegerList();
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
	return this->_clave;
}

string Votante::GetDomicilio(){
	return _domicilio;
}

int Votante::GetDistrito(){
	return _idDistrito;
}

//Ids de las elecciones en las que ya voto
vector<int> Votante::GetEleccionesVotadas(){
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

bool Votante::VotoEnEleccion(Eleccion* eleccion){

	for(int i = 0; i < _listaElecciones.size(); i++){
		if(_listaElecciones[i] == eleccion->GetId())
			return true;
	}

	return false;
	/*
	vector<int>::iterator it = _listaElecciones.begin();
	int e = (int) *it;

	for (it = _listaElecciones.begin(); it != _listaElecciones.end(); it++) {

		e = (int) *it;
		if(e == eleccion->GetId())
			return true;
	}

	return false;*/
}

bool Votante::VotoEnEleccion(int idEleccion){

	for(int i = 0; i < _listaElecciones.size(); i++){
		if(_listaElecciones[i] == idEleccion){
			return true;
		}
	}

	return false;

}

bool Votante::VotoEnEleccion(Eleccion eleccion){

	for(int i = 0; i <_listaElecciones.size(); i++){

		if(_listaElecciones[i] == eleccion.GetId())
			return true;
	}

	return false;

	/*vector<int>::iterator it = _listaElecciones.begin();
	int e = (int) *it;

	for (it = _listaElecciones.begin(); it != _listaElecciones.end(); it++) {

		e = (int) *it;
		if(e == eleccion.GetId())
			return true;
	}

	return false;*/
}

//Agrega una eleccion a la lista de elccioes en las que voto
void Votante::AgregarEleccion(int idEleccion){

	if(!this->VotoEnEleccion(idEleccion)){
		//Eleccion e = Eleccion(eleccion->GetIdCargo(), eleccion->GetDate());
		this->_listaElecciones.push_back(idEleccion);
	}
}

Votante::~Votante() {
	// TODO Auto-generated destructor stub
}
