/*
 * Administrador.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

#include "../Common/Common.h";

class Administrador {
	public:
		Administrador(string usuario, string clave);
		virtual ~Administrador();
		string GetUsuario();
		bool Authenticate(string clave);
	private:
		string _clave;
		string _usuario;
};

#endif /* ADMINISTRADOR_H_ */
