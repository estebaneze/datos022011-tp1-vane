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

#include "BPlusTreeTest.h"
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
//#include "Common/Common.h"
#include "ABMs/ABMCandidato.h"
//#include "Common/Entidades.h"
#include "ABMs/ABMLista.h"
#include "ABMs/ABMConteo.h"
#include "ABMs/ABMDistrito.h"
//#include "Entidades/Lista.h"

using namespace std;

void testABMDistrito()
{
	system("rm distri.lore");
	system("rm distri.lore.fs");

	Distrito d1 = Distrito(6,"Esteban Echeverria");
	Distrito d2 = Distrito(7,"Lomas de zamora");
	ABMDistrito *abmDistrito = new ABMDistrito("distri.lore");

	cout << "Pruebo el alta de dos distritos:"<<endl;
	abmDistrito->Add(d1);
	abmDistrito->Add(d2);
	abmDistrito->mostrarDistritosPorPantalla();

	cout << "Pruebo el alter de uno:"<<endl;
	d2.SetNombre("Capital Fereral");
	abmDistrito->Modify(d2);
	abmDistrito->mostrarDistritosPorPantalla();

	cout << "Pruebo eliminar uno:"<<endl;
	abmDistrito->Delete(d1.GetId());
	abmDistrito->mostrarDistritosPorPantalla();

}

void testConteo(){

	ABMConteo abm = ABMConteo("conteo.bt", "indexConteoDistrito.ix", "indexConteoEleccion.ix", "indexConteoLista.ix");

	cout << endl << "Nuevo registro de conteo" << endl;
	cout << "Id distrito: ";
	string idDistrito = "4";
	//cin >> idDistrito;

	cout << "Id Lista: ";
	string idLista = "4";
	//cin >> idLista;

	cout << "Id Eleccion: ";
	string idEleccion = "4";
	//cin >> idEleccion;

	abm.Add(Helper::StringToInt(idLista), Helper::StringToInt(idDistrito), Helper::StringToInt(idEleccion));

	/*cout << endl << endl;
	cout << "Ingrese id distrito a buscar: ";
	cin >> idDistrito;


	vector<Conteo> conteos = abm.GetConteoByDistrito(Helper::StringToInt(idDistrito));
	cout << "Conteos del distrito: " << idDistrito << endl;
	for(int i = 0; i < conteos.size(); i++){
		cout << conteos[i].GetId() << endl;
	}

	cout << endl << endl;
	cout << "Ingrese id Lista a buscar: ";
	cin >> idLista;

	conteos = abm.GetConteoByLista(Helper::StringToInt(idLista));
	cout << "Conteos del lista :" << idLista << endl;
	for(int i = 0; i < conteos.size(); i++){
		cout << conteos[i].GetId() << endl;
	}
	 */
}


void pruebaArbol()
{
	/*ABMConteo *abmConteo = new ABMConteo("lista.ri", "indexConteo.ix");
	abmConteo->Add(1, 1, 1);
	abmConteo->mostrarListasPorPantalla();*/

}

void pruebaListas(){

	ABMLista Listas =	ABMLista("lista.ga", "indexLista.ix");

	Lista l1 = Lista("uno", 2);
	Lista l2 = Lista("dos", 3);
	Lista l3 = Lista("tres", 4);
	Lista l4 = Lista("cuatro", 2);
	Lista l5 = Lista("cinco", 3);
	Lista l6 = Lista("seis", 4);
	Lista l7 = Lista("siete", 4);
	Lista l8 = Lista("ocho", 4);

	Listas.Add(l1);
	Listas.Add(l2);
	Listas.Add(l3);
	Listas.Add(l4);
	Listas.Add(l5);
	Listas.Add(l6);
	Listas.Add(l7);
	Listas.Add(l8);
	Listas.Add(l8);

	cout << endl << endl;
	//Listas.Add(l8);
	cout << "Listas: " << endl;
	vector<Lista> ls = Listas.GetListas();
		for(int i = 0; i < ls.size(); i++){
			cout << ls[i].GetNombre() << " - Eleccion: " << ls[i].GetEleccion() << endl;
	}

	cout << endl << endl;
	cout << "Modificar lista - Nombre: ";
	string nombreLista;
	cin >> nombreLista;
	cout << "Eleccion: ";
	string idEleccion;
	cin >> idEleccion;
	Lista l = Lista(nombreLista, Helper::StringToInt(idEleccion));
	Listas.ModifyEleccion(l);

	//Listas.mostrarListasPorPantalla();

	cout << endl;
	cout << "Listas: " << endl;
	ls = Listas.GetListas();
	for(int i = 0; i < ls.size(); i++){
		cout << ls[i].GetNombre() << " - Eleccion: " << ls[i].GetEleccion() << endl;
	}

	cout << "-----------------------------------------------------------------------" << endl;
	cout << "Ingrese id eleccion: ";
	cin >> idEleccion;
	vector<Lista> ls2 = Listas.GetListasByEleccion(Helper::StringToInt(idEleccion));
	cout << "\nListas correspondientes a la elccion " << idEleccion << endl << endl;
	for(int i = 0; i < ls2.size(); i++){
			cout << ls2[i].GetNombre() << " - Eleccion: " << ls2[i].GetEleccion() << endl;
	}

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
	vector<Candidato> cs = abmc.GetCandidatos();

	cout << "----------------ABMCandidato::GetCandidatos-----------------------" << endl;
	for(int i = 0; i < cs.size(); i++){
		cout << cs[i].GetId() << " - lista: " << cs[i].GetIdLista() << " - cargo: " << cs[i].GetIdCargo() << " - votante: " << cs[i].GetIdVotante() <<endl;
	}
	cout << "----------------ABMCandidato::GetCandidatos-----------------------" << endl;


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

void firstSetTest() {

	system("rm testTree");
	system("rm testTree.fs");

	cout << endl << endl << ConfigurationMananger::getInstance()->getBufferSizeTree() << endl << endl;

	BPlusTree bp = BPlusTree(ConfigurationMananger::getInstance()->getBufferSizeTree(),"testTree");

	int i;
	//cout << "Insertamos los elementos 100, 101, 102,103,104 todos con 4 bytes de datos: total de cada registro en el nodo hoja= 12 bytes" << endl;

	for (i = 100; i < 105; i++) {
		cout << "Insertando el elemento: " << i << endl;

		Key key =  Helper::IntToString(i);
		string str = Helper::IntToString(i).append("XXX");
		Data data = (Data)str.c_str();

		bp.insert(new Element(key, data, 4));

		//bplus.exportTree();
		//getchar();
	}
	cout << endl;

	bp.exportTree();

	/*
	cout << "Buscando el elemento 104" << endl;
	Element& element = *bplus.findExact(104);
	cout << "************Elemento encontrado: " << element << endl << endl;

	cout << "Modificando elemento elmentos 101 y 103 sin split" << endl;
	bp.modify(new Element(101, "12xxxxxxxxxx", 12));
	bp.modify(new Element(102, "12xxxxxxxxxx", 12));
	bp.exportTree();

	cout << "Modificando elemento elmento 103 generando split" << endl;
	bp.modify(new Element(103, "9xxxxxxxx", 9));
	bplus.exportTree();
	cout << "Eliminamos el elemento 103" << endl;
	bp.remove(103);
	bp.exportTree();
	cout << "Modificamos el elemento 102" << endl;
	bp.modify(new Element(102, "1", 1));
	bp.exportTree();
	cout << "eliminamos la clave 104 y se produce un balanceo" << endl;
	bp.remove(104);
	bp.exportTree();
	cout << "eliminamos la clave 100" << endl;
	bp.remove(100);
	bp.exportTree();
	cout << "eliminamos la clave 101" << endl;
	bp.remove(101);
	bp.exportTree();
	cout << "eliminamos la clave 102" << endl;
	bp.remove(102);
	bp.exportTree();
*/
	cout << "end..........." << endl;

}


int main( int arg, char *argv[] ){

//	testCandidato2();

//	BPlusTreeTest btest = BPlusTreeTest();
//	btest.run();

//	testConteo();
	//pruebaListas();
	testABMDistrito();
	//pruebaArbol();

	//testLogging();
	cout << endl;
	return system("");
}
