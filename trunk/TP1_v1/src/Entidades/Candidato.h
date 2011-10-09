/*
 * Candidato.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef CANDIDATO_H_
#define CANDIDATO_H_

#include "../Common/Common.h";

class Candidato {

	public:
		Candidato(int idLista, int idVotante, int idEleccion);
		virtual ~Candidato();
		int GetIdLista();
		int GetIdVotante();
		int GetIdEleccion();
		int GetId();

	private:
		int _idLista;
		int _idVotante;
		int _idEleccion;
		int _id;


};

#endif /* CANDIDATO_H_ */
