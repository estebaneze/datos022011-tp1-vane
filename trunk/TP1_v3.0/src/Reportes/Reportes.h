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
#include "../ABMs/ABMCargo.h"
#include "../ABMs/ABMEleccion.h"
#include "../ABMs/ABMDistrito.h"
#include "../Vigenere/Vigenere.h"

#ifndef REPORTES_H_
#define REPORTES_H_


class Reportes {
	public:
		static void reportePorEleccion(int idEleccion, bool guardaEncriptado, string claveEncriptado);
		static void reportePorLista(int idLista, bool guardaEncriptado, string claveEncriptado);
		static void reportePorDistrito(int idDistrito, bool guardaEncriptado, string claveEncriptado);
		static void reporteDesencriptar(string fileName, string claveEncriptado);

	private:
		//TODO: ESTA ORDENANDO DE MENOR A MAYOR. TIENE QUE SER AL REVES.
		static vector<Conteo> OrderByCantidadVotos(vector<Conteo> resultados);
		static vector<Conteo> OrderByFecha(vector<Conteo> resultados);
		static vector<Conteo> GroupByLista(vector<Conteo> resultados);
};

#endif /* REPORTES_H_ */

