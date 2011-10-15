/*
 * ABMCandidato.h
 *
 *  Created on: 10/10/2011
 *      Author: minnie
 */

#ifndef ABMCANDIDATO_H_
#define ABMCANDIDATO_H_

#include "../Common/Common.h"
#include "../Entidades/Candidato.h"
#include "../Hash/Directory.h"

class ABMCandidato {

	public:
		ABMCandidato(string HashFile);
		virtual ~ABMCandidato();
		bool Exists(Candidato candidato);
		void Add(int idLista, int idVotante, int idCargo);
		bool Delete(int idCandidato);
		void Modify(Candidato candidato);
		vector<Candidato> GetCandidatos(); //FALTA HACER ESTE
		Candidato* GetCandidato(int idCandidato);
		void mostrarCandidatosPorPantalla();
	private:
			string hashFile;
			Directory* directorio;

};

#endif /* ABMCANDIDATO_H_ */
