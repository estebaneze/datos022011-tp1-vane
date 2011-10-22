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
		Candidato(string idLista, long idVotante, int idCargo, int idCandidato);
		virtual ~Candidato();
		string GetIdLista();
		long GetIdVotante();
		int GetIdCargo();
		int GetId();

	private:
		string _idLista; //nombre lista
		long _idVotante; //dni
		int _idCargo;
		int _id;


};

#endif /* CANDIDATO_H_ */
