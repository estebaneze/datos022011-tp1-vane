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

std::string Distrito::GetNombre(){
	return this->Nombre;
}

void Distrito::SetNombre(string nombre){
	this->Nombre = nombre;
}