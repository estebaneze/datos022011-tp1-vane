/*
 * Administrador.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Administrador.h"

Administrador::Administrador(string usuario, string clave) {
	_clave = clave;
	_usuario = usuario;

}

string Administrador::GetUsuario(){
	return _usuario;
}

bool Administrador::Authenticate(string clave){
	return (_clave == clave);
}

Administrador::~Administrador() {
	// TODO Auto-generated destructor stub
}
