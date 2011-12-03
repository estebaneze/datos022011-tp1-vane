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
		Candidato(int idLista, long idVotante, int idCargo, int idCandidato);
		virtual ~Candidato();
		int GetIdLista();
		long GetIdVotante();
		int GetIdCargo();
		int GetId();

	private:
		int _idLista;
		long _idVotante; //dni
		int _idCargo;
		int _id;


};

#endif /* CANDIDATO_H_ */
