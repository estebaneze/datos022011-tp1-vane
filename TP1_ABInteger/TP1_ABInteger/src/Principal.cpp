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

/*int main2(){

	cout << endl << endl <<endl <<endl << endl;
		cout << " por distrito " << endl;
		Reportes::reportePorDistrito(1);

	cout << endl << endl << endl << endl;
	cout << " por lista " << endl;
	Reportes::reportePorLista("8");

	cout << "Done!!!!!!!! " << endl;
	return 0;
}

int main3(){
	Menues::MenuABMEleccion();
}

int main4(){
	//Reportes::reportePorLista("12");

	ABMEleccion* elecc = new ABMEleccion();
	int maxId = Identities::GetLastIdEleccion();

	for(int i = 1; i <= maxId; i++){

		Eleccion* e = elecc->GetEleccion(i);

		if(e != NULL){
			cout << "Eleccion " << i << " - Fecha:" << e->GetDate().getFriendlyStr() << " - Cargo: " << e->GetIdCargo() << " - Distritos: ";
			vector<int> ds = e->GetDistritos();
			for(int j = 0; j < ds.size(); j++){
				cout << ds[j] << " ";
			}
		}
		else{
			cout << "Eleccion " << i << " no existe" << endl;
		}

		cout << endl << endl;
	}

}

int main5(){

	ABMDistrito* da = new ABMDistrito();
	ABMVotante* va = new ABMVotante();

	for(int i = 11; i <= 100; i++){
		da->Add(Helper::IntToString(i));
		va->Add(new Votante(i, Helper::IntToString(i), Helper::IntToString(i), Helper::IntToString(i), i));
	}

	for(int i = 1; i <= 100; i++){

		Distrito* d = da->GetDistrito(i);

		if(d != NULL){
			cout << "Distrito " << d->GetId() << endl;
		}
	}

	for(int i = 1; i <= 100; i++){

		Votante* v = va->GetVotante(i);

		if(v != NULL){
			cout << "Votante " << v->GetDni() << " - Pertenece al distrito : " << v->GetDistrito()<< endl;
		}
	}
}
*/

int main(){
	CargaMasiva::CargarEntidades();
	//Reportes::reportePorDistrito(45);
}

int main2(int arg, char *argv[]) {

	cout << endl << endl << endl;
	cout << "Elija una opcion: " << endl << endl;
	cout << "	1. Menu" << endl;
	cout << "	2. Votaciones automaticas" << endl;
	cout << "	3. Salir" << endl;

	string option;
	cin>> option;

	while(true){

		if(option == "1"){
			Menues::MenuPpal();
			return 0;
		}
		else if(option == "2"){
			CargaMasiva::GenerarVotosAutomaticos();
			return 0;
		}
		else if(option == "3"){
			return 0;
		}
	}
	 return 0;
}


