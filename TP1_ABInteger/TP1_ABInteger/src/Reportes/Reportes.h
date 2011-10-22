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
		static void reportePorLista(string lista);
		static void reportePorDistrito(int idDistrito);

	private:
		//TODO: ESTA ORDENANDO DE MENOR A MAYOR. TIENE QUE SER AL REVES.
		static vector<Conteo> OrderByCantidadVotos(vector<Conteo> resultados);
		static vector<Conteo> OrderByFecha(vector<Conteo> resultados);
};

#endif /* REPORTES_H_ */
