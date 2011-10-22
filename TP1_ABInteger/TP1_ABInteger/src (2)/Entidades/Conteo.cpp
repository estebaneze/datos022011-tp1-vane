/*
 * Conteo.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Conteo.h"

Conteo::Conteo(){
	this->_countVotos = 0;
}

Conteo::Conteo(string idLista, int idDistrito, int idEleccion, int idConteo) {

	this->_idDistrito = idDistrito;
	this-> _idLista = idLista;
	this->_idEleccion = idEleccion;
	this->_id = idConteo;
	this->_countVotos = 0;
}

Conteo::Conteo(string idLista, int idDistrito, int idEleccion, int idConteo, int cantVotos) {

	this->_idDistrito = idDistrito;
	this-> _idLista = idLista;
	this->_idEleccion = idEleccion;
	this->_id = idConteo;
	this->_countVotos = cantVotos;

}

string Conteo::GetIdLista(){
	return _idLista;
}

int Conteo::GetIdDistrito(){
	return _idDistrito;
}

/*Eleccion* Conteo::GetEleccion(){
	return _eleccion;
}*/

int Conteo::GetIdEleccion(){
	return _idEleccion;
}

int Conteo::AddVoto(){

	if(this->_countVotos <= 0){
		this->_countVotos = 1;
	}
	else{
		this->_countVotos = this->_countVotos++;
	}

	return _countVotos;
}

int Conteo::GetCountVotos(){
	return _countVotos;
}

int Conteo::GetId(){
	return _id;
}

Conteo::~Conteo() {

}
