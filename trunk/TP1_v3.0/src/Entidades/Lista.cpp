/*
 * Lista.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Lista.h"

Lista::Lista(string nombre, int idEleccion) {

	_nombre = nombre;
	_idEleccion = idEleccion;

}

Lista::Lista(string nombre, int idEleccion, int id) {

	_nombre = nombre;
	_idEleccion = idEleccion;
	_id = id;

}

string Lista::GetNombre(){
	return _nombre;
}

int Lista::GetEleccion(){
	return _idEleccion;
}
/*
void Lista::setNombre(string nombre){
	this->_nombre=nombre;
}

void Lista::setEleccion(int eleccion){
	this->_idEleccion=eleccion;
}*/

int Lista::GetId(){
	return _id;
}

Lista::~Lista() {
	// TODO Auto-generated destructor stub
}
