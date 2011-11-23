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

int main2(int arg, char *argv[]) {

	cout << endl << endl;

	ABMVotante* abmv = new ABMVotante();
	ABMCandidato* abmcan = new ABMCandidato();

	cout << "\nCandidatos de la Lista ga:" << endl;

	vector<int> cs = abmcan->GetByLista(50);

		for(int i = 0; i< cs.size(); i++){

			cout << " " << cs[i] << " - ";
			Candidato* c = abmcan->GetCandidato(cs[i]);
			Votante* v = abmv->GetVotante(c->GetIdVotante());
			cout << " Candidato: " << v->GetNombreYApellido() << endl;
		}

		cout << endl;

	return 0;
}

int main(int arg, char *argv[]) {

	cout << endl << endl;

	CargaMasiva::BorraTodosArchivos();
cout<<endl;
	CargaMasiva::CargarVotantes();
cout<<endl<<endl;
	ABMEleccion* abme = new ABMEleccion();
	Eleccion* eleccion = new Eleccion(1, Fecha(11,11,2011));
	eleccion->AddDistrito(1);
	eleccion->AddDistrito(2);

	int idEleccion = abme->Add(eleccion);

	//cout << "id eleccion: " << idEleccion << endl;
	//PRUEBA LISTA
	Lista* l = new Lista("ga",idEleccion);
	Lista* l2 = new Lista("ga2",idEleccion);
	ABMLista* abmLista = new ABMLista();

	int idLista = abmLista->Add(l);
	int idLista2 = abmLista->Add(l2);

	Lista* lista = abmLista->GetLista(idLista);
	cout << "Lista: " << endl;
	cout << "	Nombre:" << lista->GetNombre() << endl;
	cout << "	Eleccion: " << lista->GetEleccion() << endl<< endl;

	Lista* lista2 = abmLista->GetLista(idLista2);
	cout << "Lista: " << endl;
	cout << "	Nombre:" << lista2->GetNombre() << endl;
	cout << "	Eleccion: " << lista2->GetEleccion() << endl<< endl;


	ABMConteo* c = new ABMConteo();

	Conteo* conteo = c->GetConteo(Identities::GetLastIdConteo() - 1);
	cout << "Conteo: " << endl;
	cout << "	Lista:" << conteo->GetIdLista() << endl;
	cout << "	Distrito: " << conteo->GetIdDistrito() << endl;
	cout << "	Eleccion: " << conteo->GetIdEleccion() << endl << endl;;

	conteo = c->GetConteo(Identities::GetLastIdConteo() - 2);
	cout << "Conteo: " << endl;
	cout << "	Lista:" << conteo->GetIdLista() << endl;
	cout << "	Distrito: " << conteo->GetIdDistrito() << endl;
	cout << "	Eleccion: " << conteo->GetIdEleccion() << endl << endl;


	//Agrego candidatos a la lista "ga"
	ABMCandidato* abmcan = new ABMCandidato();
	abmcan->Add(idLista, 1, 1);
	abmcan->Add(idLista, 2, 1);
	abmcan->Add(idLista, 3, 1);
	abmcan->Add(idLista, 4, 1);

	abmcan->Add(idLista2, 1, 1);
	abmcan->Add(idLista2, 2, 1);
	abmcan->Add(idLista2, 3, 1);

	cout << "\n\nCandidatos:"<<endl;
	vector<Candidato> candidatos = abmcan->GetCandidatos();
	for(int i= 0; i < candidatos.size(); i++){
		cout << " " << candidatos[i].GetId() << endl;
	}
	cout << endl << endl;

	ABMVotante* abmv = new ABMVotante();

	lista = abmLista->GetLista(idLista);
	cout << "\nCandidatos de la Lista ga:" << endl;
	vector<int> cs = abmcan->GetByLista(idLista);

	for(int i = 0; i< cs.size(); i++){

		cout << " " << cs[i] << " - ";
		Candidato* c = abmcan->GetCandidato(cs[i]);
		Votante* v = abmv->GetVotante(c->GetIdVotante());
		cout << " Candidato: " << v->GetNombreYApellido() << endl;
	}


	cout << "\n\nCandidatos de la Lista ga2:" << endl;
	cs = abmcan->GetByLista(idLista2);

	for(int i = 0; i< cs.size(); i++){

		cout << " " << cs[i] << " - ";
		Candidato* c = abmcan->GetCandidato(cs[i]);
		Votante* v = abmv->GetVotante(c->GetIdVotante());
		cout << " Candidato: " << v->GetNombreYApellido() << endl;
	}

	cout << endl;

	//PRUEBA CANDIDATO
/*	ABMCandidato* abm = new ABMCandidato();
	abm->Add("lista1",29839928,2450);
	cout << abm->GetCandidato(1)->GetIdLista() << endl;
	cout << abm->GetCandidato(1)->GetIdVotante() << endl;
	cout << abm->GetCandidato(1)->GetIdCargo() << endl;
*/


	//Menues::MenuInicial();
	cout<< endl << endl << "FIN" << endl;
	return 0;
}


