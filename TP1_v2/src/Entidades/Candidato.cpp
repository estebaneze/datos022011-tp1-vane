/*
 * Candidato.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Candidato.h"

Candidato::Candidato(int idLista, int idVotante, int idCargo, int id) {

	_idVotante = idVotante;
	_idCargo = idCargo;
	_idLista = idLista;
	_id = id;

}

Candidato::~Candidato() {

}

int Candidato::GetId(){
	return this->_id;
}

int Candidato::GetIdVotante(){
	return this->_idVotante;
}

int Candidato::GetIdCargo(){
	return this->_idCargo;
}


int Candidato::GetIdLista(){
	return this->_idLista;
}
