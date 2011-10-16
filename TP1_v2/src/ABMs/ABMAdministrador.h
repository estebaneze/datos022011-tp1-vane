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
#include "../Hash/Directory.h"

class ABMAdministrador {
public:
	ABMAdministrador(string File);
	virtual ~ABMAdministrador();

	bool existKey(Administrador admin);
	void Add(Administrador admin);
	bool Delete(Administrador admin);
	void ModifyPassword(Administrador admin);
	vector<Administrador> GetAdmins();
	Administrador* GetAdmin(std::string usuario);
	void mostrarAdminsPorPantalla();
private:
		string File;
		Directory* directorio;
};


#endif /* ABMADMINISTRADOR_H_ */
