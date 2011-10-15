/*
 * Distrito.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef DISTRITO_H_
#define DISTRITO_H_

#include "../Common/Common.h"

class Distrito {

	public:
		Distrito(int id, string nombre);
		virtual ~Distrito();
		string GetNombre();
		int GetId();

	private:
		int _id;
		std::string Nombre;
};

#endif /* DISTRITO_H_ */
