/*
 * Reportes.h
 *
 *  Created on: 18/10/2011
 *      Author: ricardo
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include "../ABMs/ABMConteo.h"

#ifndef REPORTES_H_
#define REPORTES_H_


class Reportes {
	public:
		static void reportePorEleccion(int idEleccion);
		static void reportePorLista(int idLista);
		static void reportePorDistrito(int idDistrito);
};

#endif /* REPORTES_H_ */

