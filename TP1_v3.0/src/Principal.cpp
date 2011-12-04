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

int maisdn(){
	RSA::generarClave();
	char* pepe = RSA::encriptar("hola mundo");
	char* desencriptado = RSA::desencriptar(pepe);

	string pepe1 = RSA::encriptar("hola mundo2");
	string pepe2 = RSA::encriptar("hola mundo3");

	cout << "cifrado: " << pepe << endl;
	cout << "descifrado: " << desencriptado << endl;
	//delete pepe;

	return 0;
}

int main(){

	RSA::generarClave();
	char* value = "hola mundo";

	string encrypted = RSA::encriptar(value);
	cout << "resultado encrypted: " << endl << "   " << encrypted<< endl << endl << endl;

	string originalValue = RSA::desencriptar("025471051411026934033896040338");
	cout << "originalValue : " << string(originalValue ) << endl;

	//Menues::MenuInicial();

	//CargaMasiva::CargarEntidades();


	cout << endl << "Bye!!!" << endl;
	return 0;
}

