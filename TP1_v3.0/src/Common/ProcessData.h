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

	static void obtenerData(string valor,string &idLista,long &idVotante,int &idCargo);
	static string generarData(string idLista,long idVotante, int idCargo);
	static void obtenerData(string valor, string &nombre, vector<int> &CargosSec);
	static void obtenerData(string valor,string &nombre,string &clave,string &dom,int &idDistrito,vector<int> &listaElecciones);
	static string generarData(string nombre, vector<int> cargosSec);
	static string generarData(string nombre,string clave,string domicilio,int distrito,vector<int> v);


};

#endif /* PROCESSDATA_H_ */
