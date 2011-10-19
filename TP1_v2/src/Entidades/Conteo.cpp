/*
 * Conteo.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Conteo.h"

Conteo::Conteo(string idLista, int idDistrito, int idEleccion, int idConteo) {

	this->_idDistrito = idDistrito;
	this-> _idLista = idLista;
	this->_idEleccion = idEleccion;
	this->_id = idConteo;

}

string Conteo::GetIdLista(){
	return _idLista;
}

int Conteo::GetIdDistrito(){
	return _idDistrito;
}

int Conteo::GetIdEleccion(){
	return _idEleccion;
}

void Conteo::AddVoto(){
	this->_countVotos = this->_countVotos++;
}

int Conteo::GetCountVotos(){
	return _countVotos;
}

int Conteo::GetId(){
	return _id;
}

Conteo::~Conteo() {

}
