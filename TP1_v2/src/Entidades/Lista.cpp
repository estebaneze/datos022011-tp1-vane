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

string Lista::GetNombre(){
	return _nombre;
}

int Lista::GetEleccion(){
	return _idEleccion;
}

Lista::~Lista() {
	// TODO Auto-generated destructor stub
}
