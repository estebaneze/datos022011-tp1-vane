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
#include "Test.h"
#include "Menues/Menues.h"
#include "CargaMasiva.h"

using namespace std;


int main(int arg, char *argv[]) {

	cout << endl << endl << endl;
	cout << "Elija una opcion: " << endl << endl;
	cout << "	1. Menu" << endl;
	cout << "	2. Votaciones automaticas" << endl;
	cout << "	3. Cargas Masivas" << endl;
	cout << "	4. Salir" << endl;

	string option;
	cin>> option;

	while(true){

		if(option == "1"){
			system("clear");
			Menues::MenuPpal();
			cout << "\nBye\n" << endl;
			return 0;
		}
		else if(option == "2"){
			system("clear");
			CargaMasiva::GenerarVotosAutomaticos();
			cout << "\nBye\n" << endl;
			return 0;
		}
		else if(option == "3"){
			system("clear");
			CargaMasiva::CargarEntidades();
			cout << "\nBye\n" << endl;
			return 0;
		}
		else if(option == "4"){
			system("clear");
			cout << "\nBye\n" << endl;
			return 0;
		}
		else{
			system("clear");
			cout << "Por favor elija una opcion valida" << endl;
		}
	}
	 return 0;
}


