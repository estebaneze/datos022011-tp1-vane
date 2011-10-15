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
	_id = Identities::GetNextIdAdministrador();
}

bool Administrador::Authenticate(string clave){
	return (_clave == clave);
}

Administrador::~Administrador() {
	// TODO Auto-generated destructor stub
}

string Administrador::GetClave() const
{
    return _clave;
}

string Administrador::GetUsuario() const
{
    return _usuario;
}

void Administrador::SetClave(string clave)
{
    _clave = clave;
}

void Administrador::SetUsuario(string usuario)
{
    _usuario = usuario;
}
