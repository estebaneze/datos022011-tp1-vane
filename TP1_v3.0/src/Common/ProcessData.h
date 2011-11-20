/*
 * ProcessData.h
 *
 *  Created on: 16/11/2011
 *      Author: gabriel
 */

#include <string>
#include <stdio.h>
#include "../Common/Helper.h"
using namespace std;

#ifndef PROCESSDATA_H_
#define PROCESSDATA_H_

class ProcessData {
public:

	static string generarData(string idLista,long idVotante, int idCargo);
	static string generarData(string nombre, vector<int> cargosSec);
	static string generarData(string nombre,string clave,string domicilio,int distrito,vector<int> v);
	static string generarData(string valor, string valorNuevo);
	static string generarData(vector<string> vec);
	static string generarData(string nombre);
	static void obtenerData(string valor,string &idLista,long &idVotante,int &idCargo);
	static void obtenerData(string valor, string &nombre, vector<int> &CargosSec);
	static void obtenerData(string valor,string &nombre,string &clave,string &dom,int &idDistrito,vector<int> &listaElecciones);
	static void obtenerData(string valor, vector<string> &vec);

};

#endif /* PROCESSDATA_H_ */
