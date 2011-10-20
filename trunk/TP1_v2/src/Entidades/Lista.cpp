/*
 * Lista.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Lista.h"

Lista::Lista(string nombre, string idEleccion) {

	_nombre = nombre;
	_idEleccion = idEleccion;

}

string Lista::GetNombre(){
	return _nombre;
}

string Lista::GetEleccion(){
	return _idEleccion;
}

void Lista::setNombre(string nombre){
	this->_nombre=nombre;
}

void Lista::setEleccion(string eleccion){
	this->_idEleccion=eleccion;
}

Lista::~Lista() {
	// TODO Auto-generated destructor stub
}
