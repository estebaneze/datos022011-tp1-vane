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

	cout << endl << endl;
	Identities::InitializeFile();

	cout << endl << endl;

	CargaMasiva::BorraTodosArchivos();
	cout<<endl;

	CargaMasiva::CargarVotantes();
	cout<<endl<<endl;

	ABMDistrito * abmDis = new ABMDistrito();
	int idDistrito1 = abmDis->Add("Dis1");
	int idDistrito2 = abmDis->Add("Dis2");
	int idDistrito3 = abmDis->Add("Dis3");
	int idDistrito4 = abmDis->Add("Dis4");

	Distrito *d1 = abmDis->GetDistrito(idDistrito1);
	Distrito *d2 = abmDis->GetDistrito(idDistrito2);
	Distrito *d3 = abmDis->GetDistrito(idDistrito3);
	Distrito *d4 = abmDis->GetDistrito(idDistrito4);

	cout << "Distritos: " << endl;
	cout<<"	Id: "<< d1->GetId() << " - Nombre distrito: " << d1->GetNombre() << endl;
	cout<<"	Id: "<< d2->GetId() << " - Nombre distrito: " << d2->GetNombre() << endl;
	cout<<"	Id: "<< d3->GetId() << " - Nombre distrito: " << d3->GetNombre() << endl;
	cout<<"	Id: "<< d4->GetId() << " - Nombre distrito: " << d4->GetNombre() << endl;

	ABMCargo abmCargos = ABMCargo();
	vector<int> cargosSec;
	int idCargo1 = abmCargos.Add("Cargo1", cargosSec);
	cargosSec.push_back(idCargo1);
	cargosSec.push_back(20);
	cargosSec.push_back(30);
	int idCargo2 = abmCargos.Add("Cargo2", cargosSec);

	cout << "Cargos: " << endl;
	Cargo* c1 = abmCargos.GetCargo(idCargo1);
	Cargo* c2 = abmCargos.GetCargo(idCargo2);

	cout << "	Cargo: "<< c1->GetNombre() << " - Id: " <<c1->GetId() << " - cant cargos sec: ";
	for(int i = 0; i < c1->GetCargosSecundarios().size(); i++){
		cout << c1->GetCargosSecundarios()[i] << " - ";
	}
	cout << endl;

	cout << "	Cargo: "<< c2->GetNombre() << " - Id: " << c2->GetId() << " - cant cargos sec: ";
	for(int i = 0; i < c2->GetCargosSecundarios().size(); i++){
		cout << c2->GetCargosSecundarios()[i] << " - ";
	}
	cout << endl;

	ABMEleccion* abme = new ABMEleccion();
	Eleccion* eleccion = new Eleccion(idCargo1, Fecha(11,11,2011));
	eleccion->AddDistrito(1);
	eleccion->AddDistrito(2);

	Eleccion* eleccion2 = new Eleccion(idCargo2, Fecha(12,11,2011));
	eleccion2->AddDistrito(3);
	eleccion2->AddDistrito(4);

	int idEleccion = abme->Add(eleccion);
	int idEleccion2 = abme->Add(eleccion2);

	Eleccion* e = abme->GetEleccion(idEleccion);
	Eleccion* e2 = abme->GetEleccion(idEleccion2);

	cout << "Elecciones: " << endl;
	cout << "	Id: " << e->GetId() << " - Fecha: " << e->GetDate().getFriendlyStr() << " - Cargo: " << e->GetIdCargo();
	cout << " - Distritos: ";
	for(int i = 0; i < e->GetDistritos().size(); i++){
		cout << e->GetDistritos()[i] << " - ";
	}
	cout << endl;

	cout << "	Id: " << e2->GetId() << " - Fecha: " << e2->GetDate().getFriendlyStr() << " - Cargo: " << e2->GetIdCargo();
		cout << " - Distritos: ";
		for(int i = 0; i < e2->GetDistritos().size(); i++){
			cout << e2->GetDistritos()[i] << " - ";
		}
		cout << endl << endl;

	//PRUEBA LISTA
	Lista* l = new Lista("ga",idEleccion);
	Lista* l2 = new Lista("ga2",idEleccion2);
	ABMLista* abmLista = new ABMLista();

	int idLista = abmLista->Add(l);
	int idLista2 = abmLista->Add(l2);

	Lista* lista = abmLista->GetLista(idLista);
	cout << "Lista: " << endl;
	cout << "	Id:" << lista->GetId() << endl;
	cout << "	Nombre:" << lista->GetNombre() << endl;
	cout << "	Eleccion: " << lista->GetEleccion() << endl;
	cout << "	Fecha Eleccion: " << abme->GetEleccion(lista->GetEleccion())->GetDate().getFriendlyStr() << endl<< endl;


	Lista* lista2 = abmLista->GetLista(idLista2);
	cout << "Lista: " << endl;
	cout << "	Id:" << lista2->GetId() << endl;
	cout << "	Nombre:" << lista2->GetNombre() << endl;
	cout << "	Eleccion: " << lista2->GetEleccion() << endl;
	cout << "	Fecha Eleccion: " << abme->GetEleccion(lista2->GetEleccion())->GetDate().getFriendlyStr() << endl<< endl;

	ABMConteo* abmconteo = new ABMConteo();


	cout << "\nConteos: " << endl;
	int k =1 ;
	Conteo* conteo = abmconteo->GetConteo(Identities::GetLastIdConteo() - k);
	while(conteo != NULL){

		cout << "	Id:" << conteo->GetId() << endl;
		cout << "	Lista:" << conteo->GetIdLista() << endl;
		cout << "	Distrito: " << conteo->GetIdDistrito() << endl;
		cout << "	Eleccion: " << conteo->GetIdEleccion() << endl << endl;;
		cout << "	Votos: " << conteo->GetCountVotos() << endl << endl;;

		k++;
		conteo = abmconteo->GetConteo(Identities::GetLastIdConteo() - k);
	}

	k =1 ;
	conteo = abmconteo->GetConteo(Identities::GetLastIdConteo() - k);
	ABMVotante abmv = ABMVotante();
	while(conteo != NULL){

		long dni = conteo->GetIdDistrito() + 1000;
		Votante* v = new Votante(dni, "pepe" + Helper::LongToString(dni), "clave", "calle", conteo->GetIdDistrito());
		abmv.Add(v);

		abmconteo->AddVoto(conteo->GetId(), v);

		k++;
		conteo = abmconteo->GetConteo(Identities::GetLastIdConteo() - k);
	}



	cout << "\nConteos: " << endl;
	k =1 ;
	conteo = abmconteo->GetConteo(Identities::GetLastIdConteo() - k);
	while(conteo != NULL){

		cout << "	Id:" << conteo->GetId() << endl;
		cout << "	Lista:" << conteo->GetIdLista() << endl;
		cout << "	Distrito: " << conteo->GetIdDistrito() << endl;
		cout << "	Eleccion: " << conteo->GetIdEleccion() << endl << endl;;
		cout << "	Votos: " << conteo->GetCountVotos() << endl << endl;;

		k++;
		conteo = abmconteo->GetConteo(Identities::GetLastIdConteo() - k);
	}

	cout << "\n\nConteos del Distrito 1" << endl;
	vector<Conteo> cs = abmconteo->GetConteoByDistrito(1);
	for(int i = 0; i < cs.size(); i++){

		Conteo c = cs[i];
		cout << "	Id:" << c.GetId() << endl;
		cout << "	Lista:" << c.GetIdLista() << endl;
		cout << "	Distrito: " << c.GetIdDistrito() << endl;
		cout << "	Eleccion: " << c.GetIdEleccion() << endl << endl;;
		cout << "	Votos: " << c.GetCountVotos() << endl << endl;;

	}
	cout << "\n\nConteos del Distrito 2" << endl;
	cs = abmconteo->GetConteoByDistrito(2);
	for(int i = 0; i < cs.size(); i++){
		Conteo c = cs[i];
		cout << "	Id:" << c.GetId() << endl;
		cout << "	Lista:" << c.GetIdLista() << endl;
		cout << "	Distrito: " << c.GetIdDistrito() << endl;
		cout << "	Eleccion: " << c.GetIdEleccion() << endl << endl;;
		cout << "	Votos: " << c.GetCountVotos() << endl << endl;;

	}

	cout << "\n\nConteos del Distrito 3" << endl;
	cs = abmconteo->GetConteoByDistrito(3);
	for(int i = 0; i < cs.size(); i++){
		Conteo c = cs[i];
		cout << "	Id:" << c.GetId() << endl;
		cout << "	Lista:" << c.GetIdLista() << endl;
		cout << "	Distrito: " << c.GetIdDistrito() << endl;
		cout << "	Eleccion: " << c.GetIdEleccion() << endl << endl;;
		cout << "	Votos: " << c.GetCountVotos() << endl << endl;;

	}

	cout << "\n\nConteos del Distrito 4" << endl;
	cs = abmconteo->GetConteoByDistrito(4);
	for(int i = 0; i < cs.size(); i++){
		Conteo c = cs[i];
		cout << "	Id:" << c.GetId() << endl;
		cout << "	Lista:" << c.GetIdLista() << endl;
		cout << "	Distrito: " << c.GetIdDistrito() << endl;
		cout << "	Eleccion: " << c.GetIdEleccion() << endl << endl;;
		cout << "	Votos: " << c.GetCountVotos() << endl << endl;;

	}

	cout << "\n\nConteos de la lista 1" << endl;
	cs = abmconteo->GetConteoByLista(1);
	for(int i = 0; i < cs.size(); i++){
		Conteo c = cs[i];
		cout << "	Id:" << c.GetId() << endl;
		cout << "	Lista:" << c.GetIdLista() << endl;
		cout << "	Distrito: " << c.GetIdDistrito() << endl;
		cout << "	Eleccion: " << c.GetIdEleccion() << endl << endl;;
		cout << "	Votos: " << c.GetCountVotos() << endl << endl;;

	}

	cout << "\n\nConteos de la lista 2" << endl;
	cs = abmconteo->GetConteoByLista(2);
	for(int i = 0; i < cs.size(); i++){
		Conteo c = cs[i];
		cout << "	Id:" << c.GetId() << endl;
		cout << "	Lista:" << c.GetIdLista() << endl;
		cout << "	Distrito: " << c.GetIdDistrito() << endl;
		cout << "	Eleccion: " << c.GetIdEleccion() << endl << endl;;
		cout << "	Votos: " << c.GetCountVotos() << endl << endl;;

	}

	cout << "\n\nConteos de la eleccion 1" << endl;
	cs = abmconteo->GetConteoByEleccion(1);
	for(int i = 0; i < cs.size(); i++){
		Conteo c = cs[i];
		cout << "	Id:" << c.GetId() << endl;
		cout << "	Lista:" << c.GetIdLista() << endl;
		cout << "	Distrito: " << c.GetIdDistrito() << endl;
		cout << "	Eleccion: " << c.GetIdEleccion() << endl << endl;;
		cout << "	Votos: " << c.GetCountVotos() << endl << endl;;

	}

	cout << "\n\nConteos de la eleccion 2" << endl;
	cs = abmconteo->GetConteoByEleccion(2);
	for(int i = 0; i < cs.size(); i++){
		Conteo c = cs[i];
		cout << "	Id:" << c.GetId() << endl;
		cout << "	Lista:" << c.GetIdLista() << endl;
		cout << "	Distrito: " << c.GetIdDistrito() << endl;
		cout << "	Eleccion: " << c.GetIdEleccion() << endl << endl;;
		cout << "	Votos: " << c.GetCountVotos() << endl << endl;;

	}



	//Agrego candidatos a la lista "ga"
	ABMCandidato* abmcan = new ABMCandidato();
	abmcan->Add(idLista, 1, 1);
	abmcan->Add(idLista, 2, 1);
	abmcan->Add(idLista, 3, 1);
	abmcan->Add(idLista, 4, 1);

	abmcan->Add(idLista2, 5, 1);
	abmcan->Add(idLista2, 6, 1);
	abmcan->Add(idLista2, 7, 1);

	cout << "\n\nCandidatos:"<<endl;
	vector<Candidato> candidatos = abmcan->GetCandidatos();
	for(int i= 0; i < candidatos.size(); i++){
		cout << " " << candidatos[i].GetId() << " - " << candidatos[i].GetIdVotante() << endl;
	}
	cout << endl << endl;

	lista = abmLista->GetLista(idLista);
	cout << "\nCandidatos de la Lista ga:" << endl;
	vector<int> bylista = abmcan->GetByLista(idLista);

	for(int i = 0; i< bylista.size(); i++){
		cout << " " << bylista[i] << " - ";
		Candidato* c = abmcan->GetCandidato(bylista[i]);
		Votante* v = abmv.GetVotante(c->GetIdVotante());
		cout << " Candidato: " << v->GetNombreYApellido() << endl;
	}


	cout << "\n\nCandidatos de la Lista ga2:" << endl;
	bylista = abmcan->GetByLista(idLista2);

	for(int i = 0; i< bylista.size(); i++){

		cout << " " << bylista[i] << " - ";
		Candidato* c = abmcan->GetCandidato(bylista[i]);
		Votante* v = abmv.GetVotante(c->GetIdVotante());
		cout << " Candidato: " << v->GetNombreYApellido() << endl;
	}


	cout << endl;

	//Prueba reportes

	cout << "*************** Test de Reportes ******************************" << endl << endl;
	cout << "Reporte por Lista " << lista->GetNombre() << "(id:" << lista->GetId() << ")" << endl << endl;
	Reportes::reportePorLista(lista->GetId(), false, "");

	//PRUEBA CANDIDATO
/*	ABMCandidato* abm = new ABMCandidato();
	abm->Add("lista1",29839928,2450);
	cout << abm->GetCandidato(1)->GetIdLista() << endl;
	cout << abm->GetCandidato(1)->GetIdVotante() << endl;
	cout << abm->GetCandidato(1)->GetIdCargo() << endl;
*/


	//Menues::MenuInicial();
	cout<< endl << endl << " Bye!!!!!! " << endl;
	return 0;
}


