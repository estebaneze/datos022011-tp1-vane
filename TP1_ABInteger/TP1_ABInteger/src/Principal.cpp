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

using namespace std;

int main( int arg, char *argv[] ){

//	ta.testABMDistrito();
	//ta.testConteo();

	//	testConteo();
	//testReportes();

	//agregarDistritos();
	//agregarVotantes();
	//Ingresar();
	//testCandidato2();

	//testConteo2();

	//	testConteo();
	//pruebaListas();
	//	pruebaListas2();
	//	testABMDistrito();
	//pruebaArbol();
	//testLogging();

	/*ABMDistrito ds = ABMDistrito("distrito");
	ds.Add("Lanus");
	ds.Add("Lomas");
	ds.Add("Cap");
	ds.Add("La Plata");

	string id;
	cout << endl << endl << "Ingrese id ";
	cin>>id;

	Distrito* d = ds.GetDistrito(Helper::StringToInt(id));
	if(d != NULL){
		cout << "epepe" << endl;
	}*/
		//cout << "Ecnontre " << d->GetId() << " - " << d->GetNombre() << endl;
/*
	ABMConteo cs = ABMConteo();
	for(int i = 0; i < 10; i++){

		if(cs.ExistsKey(i)){
			Conteo* c = cs.GetConteo(i);
			if(c != NULL){
				cout << c->GetId() << " - " <<  c->GetIdDistrito() << " - " << c->GetIdEleccion() << endl;
			}
		}

	}

	delete cs;*/

	Menues menu;
	menu.MenuPpal();
	cout << endl <<  "Done" << endl;
		return system("");

}

