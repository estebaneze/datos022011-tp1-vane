/*
 * Candidato.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef CANDIDATO_H_
#define CANDIDATO_H_

class Candidato {

	public:
		Candidato(int idLista, int idVotante, int idEleccion);
		virtual ~Candidato();
		int GetIdLista();
		int GetIdVotante();
		int GetIdEleccion();

	private:
		int _idLista;
		int _idVotante;
		int _idEleccion;

};

#endif /* CANDIDATO_H_ */
