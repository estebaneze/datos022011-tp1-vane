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
#include "../Indexes/Index.h"
#include "../Logging/HashLog.h"
//Candidato (((lista)ie, (votante)ie, (cargo)ie)i): Hash

class ABMCandidato {

	public:
		ABMCandidato(string HashFile);
		virtual ~ABMCandidato();
		bool Exists(Candidato candidato);
		int Add(int idLista, int idVotante, int idCargo);
		bool Delete(int idCandidato);
		void Modify(Candidato candidato);
		vector<Candidato> GetCandidatos();
		Candidato* GetCandidato(int idCandidato);
		void mostrarCandidatosPorPantalla();
	private:
			string hashFile;
			Directory* directorio;

};

#endif /* ABMCANDIDATO_H_ */
