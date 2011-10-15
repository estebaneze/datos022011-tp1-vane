/*
 * Conteo.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Conteo.h"

Conteo::Conteo(int idLista, int idDistrito, int idEleccion) {
	// TODO Auto-generated constructor stub

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

Conteo::~Conteo() {
	// TODO Auto-generated destructor stub
}
