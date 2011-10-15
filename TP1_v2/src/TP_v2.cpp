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

#include "Logging/Log.h"
#include "Common/Common.h"
#include "ABMs/ABMCandidato.h"
#include "Common/Entidades.h"
#include "ABMs/ABMLista.h"
#include "ABMs/ABMConteo.h"
#include "Entidades/Lista.h"


using namespace std;

void pruebaArbol()
{
	Conteo conteo1 = Conteo(1, 1, 1);
	ABMConteo *abmConteo = new ABMConteo("lista.ri");

	abmConteo->Add(conteo1);

	abmConteo->mostrarListasPorPantalla();

}
void pruebaListas(){

	Lista lista1 = Lista("lista5",666);
	Lista lista2 = Lista("lista6",123);
	//Lista lista2 = Lista(2,123);

	ABMLista Listas =	ABMLista("lista.ga");
	Listas.Add(lista1);
	Listas.Add(lista2);
	Listas.mostrarListasPorPantalla();
	//	alta.Add(lista1);
	//alta.Add(lista2);
}


void testCandidato2(){

	cout << endl;
	ABMCandidato abmc = ABMCandidato("candidato.ga");
	cout << endl;
	cout << "Candidatos: "<< endl;
	abmc.mostrarCandidatosPorPantalla();

	cout << "-----------------------------------------------------";
	cout << "-----------------------------------------------------" << endl;
	cout << "prueba abmc.GetCandidatos(): " << endl;
	abmc.GetCandidatos();


}


void testCandidato(){

	cout << endl;
	ABMCandidato abmc = ABMCandidato("candidato.ga");

	string dni;
	string idLista;
	string idCargo;
	/*cout << "Candidato nuevo - DNI: ";
	cin >> dni;
	cout << "Id Cargo: ";
	cin >> idCargo;
	cout << "Id Lista: ";
	cin >> idLista;

	cout << endl;
	cout << endl;
	abmc.Add(Helper::StringToInt(idLista), Helper::StringToInt(dni), Helper::StringToInt(idCargo));
*/
	cout << endl;
	cout << "Candidatos: "<< endl;
	abmc.mostrarCandidatosPorPantalla();

	cout << "-----------------------------------------------------";
	cout << "-----------------------------------------------------" << endl;
	cout << "prueba abmc.GetCandidatos(): " << endl;
	abmc.GetCandidatos();

	cout << "-----------------------------------------------------";
	cout << "-----------------------------------------------------" << endl;
	cout << "-----------------------------------------------------";
	cout << "-----------------------------------------------------" << endl;


	cout << endl;
	cout << endl;

	Candidato c3=Candidato(3, 3, 3, 3);
	Candidato c4=Candidato(3, 3, 3, 4);
	Candidato c5=Candidato(3, 3, 3, 5);
	Candidato c10=Candidato(3, 3, 3, 10);
	cout << "Existe candidato 3 ? -->" << abmc.Exists(c3) << endl;
	cout << "Existe candidato 4 ? -->" << abmc.Exists(c4) << endl;
	cout << "Existe candidato 5 ? -->" << abmc.Exists(c5) << endl;
	cout << "Existe candidato 10 ? -->" << abmc.Exists(c10) << endl;

	cout << endl;
	cout << "Id Candidato: ";
	string idCandidato;
	cin >> idCandidato;
	Candidato* c = abmc.GetCandidato(Helper::StringToInt(idCandidato));
	if(c != NULL){
		cout << "Candidato: " << c->GetId() << endl;
		cout << "Votante: " <<  c->GetIdVotante() << " - ";
		cout << "Cargo: " <<  c->GetIdCargo() << " - ";
		cout << "Lista: " << c->GetIdLista() << " - ";
	}
	else{
		cout << "No existe el candidato" << endl;
	}

	cout << "-----------------------------------------------------";
	cout << "-----------------------------------------------------" << endl;

	cout << "Delete - Id Candidato: ";
	idCandidato;
	cin >> idCandidato;
	abmc.Delete(Helper::StringToInt(idCandidato));
	cout << "Candidatos: "<< endl;
	abmc.mostrarCandidatosPorPantalla();

	cout << "-----------------------------------------------------";
	cout << "-----------------------------------------------------" << endl;

	cout << "Modificar candidato - Id Candidato: ";
	cin >> idCandidato;
	cout << "DNI: ";
	cin >> dni;
	cout << "Id Cargo: ";
	cin >> idCargo;
	cout << "Id Lista: ";
	cin >> idLista;
	//(int idLista, int idVotante, int idCargo, int idCandidato);
	Candidato c1 = Candidato(Helper::StringToInt(idLista), Helper::StringToInt(dni), Helper::StringToInt(idCargo), Helper::StringToInt(idCandidato));
	abmc.Modify(c1);
	cout << "Candidatos: "<< endl;
	abmc.mostrarCandidatosPorPantalla();

}

void testLogging(){

	Log::WriteLog("Inserto algo", "log.txt");
	Log::WriteLog("Inserto algo","log.txt");
	Log::WriteLog("Inserto algo","log.txt");

}



int main( int arg, char *argv[] ){

	testCandidato2();

	//pruebaListas();
	//pruebaArbol();

	//testLogging();
	cout << endl;
	return system("");
}
