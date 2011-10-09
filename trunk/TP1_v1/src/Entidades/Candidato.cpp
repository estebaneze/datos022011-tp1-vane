/*
 * Candidato.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Candidato.h"

Candidato::Candidato(int idLista, int idVotante, int idEleccion) {

	_idEleccion = idEleccion;
	_idVotante = idVotante;
	_idLista = idLista;

	 _id = Identities::GetNextIdCandidato();
}

Candidato::~Candidato() {
	// TODO Auto-generated destructor stub
}

int Candidato::GetId(){
	return this->_id;
}
