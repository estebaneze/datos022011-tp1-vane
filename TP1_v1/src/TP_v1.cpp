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
#include "Common/Estructuras.h"

using namespace std;

int main() {

	HashExtensible hash = HashExtensible("Distritos.hs");

	vector<Field> Vf;

	string str = "301";
	Field F = Field(str);
	str = "302";
	Field F2 = Field(str);
	str = "303";
	Field F3 = Field(str);
	Vf.push_back(F);
	Vf.push_back(F2);
	Vf.push_back(F3);

	Key_Node K= Key_Node();
	//Agrego los campos al key node
	for (int i=0; i<Vf.size();i++){
		Field FAux=Vf.at(i);
		K.AddField(FAux);
	}

	ref auxRef2;
	auxRef2.posBloq=1;
	auxRef2.posReg=2;
	auxRef2.Key=F;

	Refs R = Refs();

	R.vRefs.push_back(auxRef2);

	K.ref = R;

	//Key_Node *pK=new Key_Node();
	//*pK=K;

	K.Print();
	cout << endl;
	hash.del(K);
	hash.add(K,R);

	vector<Field> Vf2;

	str = "401";
	Field F4= Field(str);
	str = "402";
	Field F5= Field(str);
	str = "403";
	Field F6= Field(str);
	Vf2.push_back(F4);
	Vf2.push_back(F5);
	Vf2.push_back(F6);

	Key_Node K2= Key_Node();

	for (int i=0; i<Vf2.size();i++){
		Field FAux=Vf2.at(i);
		K2.AddField(FAux);
	}

	ref auxRef22;
	auxRef22.posBloq=1;
	auxRef22.posReg=2;
	auxRef22.Key=F2;

	Refs R2=Refs();

	R2.vRefs.push_back(auxRef22);

	K2.ref =R2;

	K2.Print();
	cout << endl;

	hash.add(K2,R2);

	hash.save();

	/*
	string str2="185";
	Field F2= Field(INTEGER,str2);
	Vf2.push_back(F2);

	Key_Node K2= Key_Node();
	K2.ref.posBloq=1;
	K2.ref.posReg=1;

	for (int i=0; i<Vf2.size();i++){
		Field FAux=Vf2.at(i);
		K2.AddField(FAux);
	}
	cout<<"control"<<endl;
	tree.add_key(K2,true);

	system("PAUSE");
	return EXIT_SUCCESS;
*/
	int pepe = hash.fHash(K2);
	cout << "dsfsfs" << endl;
	cout << pepe << endl;

	system("PAUSE");
	return 0;
}


