/*
 * Conteo.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Conteo.h"

Conteo::Conteo(int idLista, int idDistrito, int idEleccion, int idConteo) {

	this->_idDistrito = idDistrito;
	this-> _idLista = idLista;
	this->_idEleccion = idEleccion;
	this->_id = idConteo;

}

int Conteo::GetIdLista(){
	return _idLista;
}

int Conteo::GetIdDistrito(){
	return _idDistrito;
}

int Conteo::GetIdEleccion(){
	return _idEleccion;
}

void Conteo::AddVoto(){
	_countVotos = _countVotos++;
}

int Conteo::GetCountVotos(){
	return _countVotos;
}

int Conteo::GetId(){
	return _id;
}

Conteo::~Conteo() {

}
