/*
 * VotanteLog.h
 *
 *  Created on: 22/10/2011
 *      Author: gabriel
 */

#ifndef VOTANTELOG_H_
#define VOTANTELOG_H_
#include "../Hash/Directory.h"
#include "Log.h"
#include "../utils/Fecha.h"

class VotanteLog {
public:
	VotanteLog();
	static void LogSuccess(string info);
	static void LogUserInvalid(string info);
	static void LogPasswordInvalid(string info);
	static void LogVoto(string dni,string lista);
	static void LogChangeVoto(string dni,string lista,string listaAnterior);

	virtual ~VotanteLog();
};

#endif /* VOTANTELOG_H_ */

