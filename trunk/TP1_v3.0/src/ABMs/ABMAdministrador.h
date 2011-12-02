/*
 * ABMAdministrador.h
 *
 *  Created on: 15/10/2011
 *      Author: gabriel
 */

#ifndef ABMADMINISTRADOR_H_
#define ABMADMINISTRADOR_H_

#include "../Common/Common.h"
#include "../Entidades/Administrador.h"
#include "../Hash/DirectoryRSA.h"
#include "../Logging/HashLog.h"

class ABMAdministrador {

	public:
		ABMAdministrador();
		virtual ~ABMAdministrador();
		bool existKey(string admin);
		void Add(Administrador* admin);
		bool Delete(Administrador* admin);
		void ModifyPassword(Administrador* admin);
		vector<Administrador> GetAdmins();
		Administrador* GetAdmin(std::string usuario);
		void mostrarAdminsPorPantalla();

	private:
		string File;
		DirectoryRSA* directorio;
};


#endif /* ABMADMINISTRADOR_H_ */