/*
 * Candidato.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef CANDIDATO_H_
#define CANDIDATO_H_

#include "../Common/Common.h"

class Candidato {

	public:
		Candidato(int idLista, int idVotante, int idCargo, int idCandidato);
		virtual ~Candidato();
		int GetIdLista();
		int GetIdVotante();
		int GetIdCargo();
		int GetId();

	private:
		int _idLista;
		int _idVotante;
		int _idCargo;
		int _id;


};

#endif /* CANDIDATO_H_ */
