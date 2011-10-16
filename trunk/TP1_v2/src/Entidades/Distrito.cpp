/*
 * Distrito.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Distrito.h"

Distrito::Distrito(int id, string nombre) {

	this->Nombre = nombre;
	this->_id = id;

}

Distrito::~Distrito() {
	// TODO Auto-generated destructor stub
}

 int Distrito::GetId() {
	return this->_id;
}
