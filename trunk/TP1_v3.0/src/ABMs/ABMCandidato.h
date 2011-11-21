/*
 * ABMCandidato.h
 *
 *  Created on: 10/10/2011
 *      Author: minnie
 */

#ifndef ABMCANDIDATO_H_
#define ABMCANDIDATO_H_

#include "../Indexes/Index.h"
#include "../Common/Common.h"
#include "../Entidades/Candidato.h"
#include "../Hash/Directory.h"
#include "../Indexes/Index.h"
#include "../Logging/HashLog.h"
#include "../Common/ProcessData.h"
#include "../ABMs/ABMLista.h"
//Candidato (((lista)ie, (votante)ie, (cargo)ie)i): Hash

class ABMCandidato {

	public:
		ABMCandidato();
		virtual ~ABMCandidato();
		bool Exists(Candidato *candidato);
		int Add(int idLista,long idVotante, int idCargo);
		//bool Delete(int idCandidato);
		//void Modify(Candidato *candidato);
		vector<Candidato> GetCandidatos();
		Candidato* GetCandidato(int idCandidato);
		void mostrarCandidatosPorPantalla();
		vector<int> GetByLista(int idLista);
		string generarData(string idLista,long idVotante, int idCargo);
		vector<string> obteneData(string valor);
	private:
			string hashFile;
			Directory* directorio;
			Index* index;
};

#endif /* ABMCANDIDATO_H_ */
