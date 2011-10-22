/*
 * Administrador.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

#include "../Common/Common.h"

class Administrador {
	public:
		Administrador(string usuario, string clave);
		virtual ~Administrador();
		bool Authenticate(string clave);
		string GetClave() const;
		string GetUsuario() const;
		void SetClave(string clave);
		void SetUsuario(string usuario);
	private:
		//int _id;
		string _clave;
		string _usuario;
};

#endif /* ADMINISTRADOR_H_ */
