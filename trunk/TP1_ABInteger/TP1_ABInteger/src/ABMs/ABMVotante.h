/*
 * ABMVotante.h
 *
 *  Created on: 15/10/2011
 *      Author: gabriel
 */

#ifndef ABMVOTANTE_H_
#define ABMVOTANTE_H_

#include "../Common/Common.h"
#include "../Entidades/Votante.h"
#include "../Hash/Directory.h"
#include "../Logging/HashLog.h"

class ABMVotante {

public:

	ABMVotante();
	virtual ~ABMVotante();
	bool existKey(long dni);
	void Add(Votante *votante);
	bool Delete(Votante *votante);
	void Modify(Votante *votante);
	vector<Votante*> GetVotantes();
	Votante* GetVotante(long dni);

	void mostrarVotantesPorPantalla();
private:
	string file;
	Directory* directorio;

};

#endif /* ABMVOTANTE_H_ */
