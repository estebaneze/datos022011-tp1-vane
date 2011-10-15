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
#include "Logging/Log.h"
#include <stdio.h>
#include "Common/Common.h"
#include "ABMs/ABMCandidato.h"
#include "Common/Entidades.h"
#include "ABMs/ABMLista.h"
#include "Entidades/Lista.h"
using namespace std;

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


void testCandidato(){

	cout << endl;
	Candidato c1 = Candidato(45, 13, 41);
	Candidato c2 = Candidato(2, 2, 2);
	Candidato c3 = Candidato(3, 3, 3);
	Candidato c4 = Candidato(33, 4, 23);
	cout << "Candidato - id: " << c1.GetId() << " - idLista: " << c1.GetIdLista() << " - idEleccion: " << c1.GetIdEleccion() << " - idVotante: " << c1.GetIdVotante() << endl;
	//ABMCandidato abmCandidato = ABMCandidato("Candidatos.hs");
	//abmCandidato.Add(c1);
	//abmCandidato.Add(c2);
	//abmCandidato.Add(c3);

	//abmCandidato.GetCandidato(34);

	//Candidato candidato = abmCandidato.GetCandidato(c1.GetId());

}

void testCandidato2(){

	/*cout << endl;
	Candidato c1 = Candidato(1, 1, 1);
	Candidato c2 = Candidato(2, 2, 2);
	Candidato c3 = Candidato(3, 3, 3);
	Candidato c4 = Candidato(33, 4, 23);

	HashExtensible hash = HashExtensible("Candidatos.hs");

	Key_Node K = Key_Node();
	Key_Node K2 = Key_Node();

	//Agrego los campos al key node

	string id1 = Helper::IntToString(c1.GetId());
	Field F1 = Field(id1);
	K.AddField(F1);

	string id2 = Helper::IntToString(c2.GetId());
	Field F2 = Field(id2);
	K.AddField(F2);

	string id3 = Helper::IntToString(c3.GetId());
	Field F3 = Field(id3);
	K.AddField(F3);

	string id4 = Helper::IntToString(c4.GetId());
	Field F4 = Field(id4);
	K2.AddField(F4);	//Este lo agrego en la clave dos (K2)


	//Lista de "Refs"
	Refs R = Refs();
	Refs R2 = Refs();

	//Creo el Ref
	ref auxRef1;
	auxRef1.posBloq=1;
	auxRef1.posReg=1;
	auxRef1.Key=F1;

	ref auxRef2;
	auxRef2.posBloq=1;
	auxRef2.posReg=2;
	auxRef2.Key=F2;

	ref auxRef3;
	auxRef3.posBloq=1;
	auxRef3.posReg=3;
	auxRef3.Key=F3;

	ref auxRef4;
	auxRef4.posBloq =31;
	auxRef4.posReg =31;
	auxRef4.Key=F4;

	R.vRefs.push_back(auxRef1);	//Agrego el "auxRef2" al vector de refs de R.
	R.vRefs.push_back(auxRef2);	//Agrego el "auxRef2" al vector de refs de R.
	R.vRefs.push_back(auxRef3);	//Agrego el "auxRef2" al vector de refs de R.

	R2.vRefs.push_back(auxRef4);

	K.ref = R;	//El key_node tiene referencia al R (los Refs, que tienen una referencia al )
	K2.ref = R2;

	K.Print();
	cout << "----------------" << endl;
	K2.Print();

	cout << endl;
	hash.add(K,R);	//Agrego el key_node al hash
	hash.add(K2, R2);
	hash.save();

	cout  << endl;
	bool containsKey = hash.contains(K);

	if(containsKey){

		cout << "Clave " << K.toInt() << ": " << endl;
		vector<Field>::iterator it = K.GetIterator();
		for(int i = 0; i < K.GetFieldCount(); i++){
			Field actual = it[i];
			cout << actual.Serialize() << endl;
		}
	}
	else
		cout << K.toInt() << " no esta en el hash " << endl;


	containsKey = hash.contains(K2);
	if(containsKey){

		cout << "Clave " << K2.toInt() << ": " << endl;
		vector<Field>::iterator it = K2.GetIterator();
		for(int i = 0; i < K2.GetFieldCount(); i++){
			Field actual = it[i];
			cout << actual.Serialize() << endl;
		}
	}
	else
		cout << K2.toInt() << " no esta en el hash " << endl;


	cout << "Borro la clave K2 " << K2.toInt() << endl;
	hash.del(K2);
	containsKey = hash.contains(K2);
	if(containsKey){

		cout << "Clave " << K2.toInt() << ": " << endl;
		vector<Field>::iterator it = K2.GetIterator();
		for(int i = 0; i < K2.GetFieldCount(); i++){
			Field actual = it[i];
			cout << actual.Serialize() << endl;		}
	}
	else
		cout << K2.toInt() << " no esta en el hash " << endl;
*/
}

void testLogging(){

	Log::WriteLog("Inserto algo");
	Log::WriteLog("Inserto algo");
	Log::WriteLog("Inserto algo");

}

int main( int arg, char *argv[] ){

/*	cout << Identities::GetNextIdCandidato() << endl;
	cout << Identities::GetNextIdCandidato() << endl;
	cout << Identities::GetNextIdCandidato() << endl;
	cout<< endl;
	cout<< endl;
	cout<< endl;
	cout << Identities::GetNextIdCargo() << endl;
		cout << Identities::GetNextIdCargo() << endl;
		cout << Identities::GetNextIdCargo() << endl;
		cout<< endl;
		cout<< endl;

		cout << Identities::GetNextIdDistrito() << endl;
			cout << Identities::GetNextIdDistrito() << endl;
			cout << Identities::GetNextIdDistrito() << endl;
			*/

	//testCandidato();

	pruebaListas();

	//testLogging();
	cout << endl;
	return system("");
}
