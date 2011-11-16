//============================================================================
// Name        : TP1_v1.cpp
// Author      : vane_richard_virgi_lore_gaby
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 Distrito ((distrito)i, nombreDistrito): Arbol B+
 Votante ((DNI)i, NombreyApellido, clave, domicilio, (distrito)ie, ((eleccion)ie)*): Hash
 Eleccion ((fecha, (cargo)ie)i, ((distrito)ie)+): Arbol B+
 Lista (((eleccion)ie, nombre)i): Hash
 Conteo (((lista)ie, (distrito)ie, (eleccion)ie)i, cantidad): Arbol B+
 Candidato (((lista)ie, (votante)ie, (cargo)ie)i): Hash
 Cargo ((cargo)i, (cargo)*): Hash
 Administrador ((usuario)i, clave): Hash
 * */


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdio.h>

#include "Reportes/Reportes.h"
#include "Logging/Log.h"
#include "ABMs/ABMCandidato.h"
#include "ABMs/ABMLista.h"
#include "ABMs/ABMConteo.h"
#include "ABMs/ABMDistrito.h"
#include "ABMs/ABMVotante.h"
#include "ABMs/ABMEleccion.h"
#include "Menues/Menues.h"
#include "CargaMasiva.h"

using namespace std;

int main(int arg, char *argv[]) {

	//PRUEBA LISTA
/*	Lista* l = new Lista("ga",4568977);
	ABMLista* abm = new ABMLista();
	abm->Add(l);
	cout << Helper::IntToString(abm->GetLista("ga")->GetEleccion()) << endl;
*/

	//PRUEBA CANDIDATO
/*	ABMCandidato* abm = new ABMCandidato();
	abm->Add("lista1",29839928,2450);
	cout << abm->GetCandidato(1)->GetIdLista() << endl;
	cout << abm->GetCandidato(1)->GetIdVotante() << endl;
	cout << abm->GetCandidato(1)->GetIdCargo() << endl;
*/


	//Menues::MenuInicial();
	cout << "FIN" << endl;
	return 0;
}


