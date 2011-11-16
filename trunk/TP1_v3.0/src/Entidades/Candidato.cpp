/*
 * Candidato.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Candidato.h"

Candidato::Candidato(string idLista, long idVotante, int idCargo, int id) {

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

long Candidato::GetIdVotante(){
	return this->_idVotante;
}

int Candidato::GetIdCargo(){
	return this->_idCargo;
}


string Candidato::GetIdLista(){
	return this->_idLista;
}
