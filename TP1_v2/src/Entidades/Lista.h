/*
 * Lista.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef LISTA_H_
#define LISTA_H_

#include "../Common/Common.h"

class Lista {

	public:
		Lista(string nombre, int idEleccion);
		virtual ~Lista();
		string GetNombre();
		int GetEleccion();
		void setNombre(string nombre);
		void setEleccion(int eleccion);
	private:
		int _idEleccion;
		string _nombre;
};

#endif /* LISTA_H_ */
