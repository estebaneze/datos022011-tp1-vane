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
#include "ABMs/ABMCandidato.h"
#include "ABMs/ABMLista.h"
#include "ABMs/ABMConteo.h"
#include "ABMs/ABMDistrito.h"
#include "ABMs/ABMVotante.h"

using namespace std;

void testABMDistrito()
{
	system("rm dis_lore.bpt");
	system("rm dis_lore.bpt.fs");

	cout <<endl<<endl;
	string d1 = "Esteban Echeverria";
	string d2 = "Lomas de zamora";
	ABMDistrito *abmDistrito = new ABMDistrito("dis_lore");

	cout << "Pruebo el alta de dos distritos:"<<endl;
	int id1 = abmDistrito->Add(d1);
	int id2 = abmDistrito->Add(d2);
	abmDistrito->mostrarDistritosPorPantalla();

	cout << "Pruebo el alter de uno:"<<endl;
	Distrito distrito2 = Distrito(id1, "Capital Federal");
	abmDistrito->Modify(distrito2);
	abmDistrito->mostrarDistritosPorPantalla();

	cout << "Pruebo eliminar uno:"<<endl;
	abmDistrito->Delete(id1);
	abmDistrito->mostrarDistritosPorPantalla();

}

void testConteo(){

	ABMConteo *abm = new ABMConteo();

	int idDistrito;
	int idLista;
	int idEleccion = 1;

	for (int i=0; i<100; i++)
	{
		idDistrito = i;

		for (int j=100; j<200; j++)
		{
			idLista = j;
			abm->Add(Helper::IntToString(idLista), idDistrito, idEleccion);
		}
	}

	abm->mostrarConteoPorPantalla();
	/*
	string idDistritoReporte = "3";
	vector<Conteo> conteos = abm->GetConteoByDistrito(Helper::StringToInt(idDistritoReporte));
	cout << "Conteos del distrito: " << idDistritoReporte << endl;
	for(int i = 0; i < conteos.size(); i++){
		cout << "Conteo:" <<conteos[i].GetId() << endl;
		cout << "Distrito:" << conteos[i].GetIdDistrito() << endl;
		cout << "Lista:" << conteos[i].GetIdLista() << endl;
		cout << "Eleccion:" << conteos[i].GetIdEleccion() << endl;
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

	ABMLista Listas = ABMLista("lista.ga", "indexLista.ix");

	Lista l1 = Lista("alonso8", 2);
	Lista l2 = Lista("dos", 3);
	Lista l3 = Lista("tres", 4);
	Lista l4 = Lista("cuatro", 2);
	Lista l5 = Lista("cinco", 3);
	Lista l6 = Lista("seis", 4);
	Lista l7 = Lista("siete", 4);
	Lista l8 = Lista("ocho", 4);
	Lista l9 = Lista("aa",9);
	Listas.Add(l1);
	Listas.Add(l2);
	Listas.Add(l3);
	Listas.Add(l4);
	Listas.Add(l5);
	Listas.Add(l6);
	Listas.Add(l7);
	Listas.Add(l8);
	Listas.Add(l9);

	cout << endl << endl;
	//Listas.Add(l8);
	cout << "Listas: " << endl;
	vector<Lista> ls = Listas.GetListas();
		for(int i = 0; i < ls.size(); i++){
			cout << ls[i].GetNombre() << " - Eleccion: " << ls[i].GetEleccion() << endl;
	}

	//Listas.mostrarListasPorPantalla();

/*	cout << endl << endl;
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
	}*/

}



void pruebaListas2(){

	ABMLista Listas = ABMLista("lista.ga", "indexLista.ix");

	Lista l1 = Lista("alonso8", 2);
	Lista l2 = Lista("dos", 3);
	Lista l3 = Lista("tres", 4);
	Lista l4 = Lista("cuatro", 2);
	Lista l5 = Lista("cinco", 3);
	Lista l6 = Lista("seis", 4);
	Lista l7 = Lista("siete", 4);
	Lista l8 = Lista("ocho", 4);
	Lista l9 = Lista("aa",9);
	Listas.Add(l1);
	Listas.Add(l2);
	Listas.Add(l3);
	Listas.Add(l4);
	Listas.Add(l5);
	Listas.Add(l6);
	Listas.Add(l7);
	Listas.Add(l8);
	Listas.Add(l9);

	cout << endl << endl;
	//Listas.Add(l8);
	cout << "Listas: " << endl;
	vector<Lista> ls = Listas.GetListas();
		for(int i = 0; i < ls.size(); i++){
			cout << ls[i].GetNombre() << " - Eleccion: " << ls[i].GetEleccion() << endl;
	}

	//Listas.mostrarListasPorPantalla();

		cout << endl << endl << "------------------------------------------" << endl;;

		vector<Lista> ls2 = Listas.GetListasByEleccion(3);
			cout << "\nListas correspondientes a la elccion " << 3 << endl << endl;
			for(int i = 0; i < ls2.size(); i++){
					cout << ls2[i].GetNombre() << " - Eleccion: " << ls2[i].GetEleccion() << endl;
			}

			cout << endl << endl;

			ls2 = Listas.GetListasByEleccion(7);
				cout << "\nListas correspondientes a la elccion " << 7 << endl << endl;
				for(int i = 0; i < ls2.size(); i++){
						cout << ls2[i].GetNombre() << " - Eleccion: " << ls2[i].GetEleccion() << endl;
				}


	cout << endl << endl << "------------------------------------------" << endl << "Modificar lista " << endl << "Ingrese Nombre de Lista: ";
	string nombreLista;
	cin >> nombreLista;
	cout << "Ingrese id Eleccion: ";
	string idEleccion;
	cin >> idEleccion;


	cout << endl << endl << "Modificar lista - Nombre:" << nombreLista<< "- Eleccion: " << idEleccion<<endl;

	Lista l = Lista(nombreLista, Helper::StringToInt(idEleccion));
	Listas.Modify(l);

	//Listas.mostrarListasPorPantalla();

	cout << endl;
/*	cout << "Listas: " << endl;
	ls = Listas.GetListas();
	for(int i = 0; i < ls.size(); i++){
		cout << ls[i].GetNombre() << " - Eleccion: " << ls[i].GetEleccion() << endl;
	}
*/
	cout << endl << endl << "------------------------------------------" << endl;;
	 ls2 = Listas.GetListasByEleccion(7);
		cout << "\nListas correspondientes a la elccion " << 7 << endl << endl;
		for(int i = 0; i < ls2.size(); i++){
				cout << ls2[i].GetNombre() << " - Eleccion: " << ls2[i].GetEleccion() << endl;
		}

		cout << endl << endl << "------------------------------------------" << endl;;
		 ls2 = Listas.GetListasByEleccion(3);
			cout << "\nListas correspondientes a la elccion " << 3 << endl << endl;
			for(int i = 0; i < ls2.size(); i++){
					cout << ls2[i].GetNombre() << " - Eleccion: " << ls2[i].GetEleccion() << endl;
			}

}


void testCandidato2(){

	cout << endl;
	ABMCandidato abmc = ABMCandidato("candidato.ga");
	cout << endl;

	for(int i = 1; i < 5; i++){
		abmc.Add(i,i,i);
	}

	vector<Candidato> cs = abmc.GetCandidatos();
	cout << "----------------ABMCandidato::GetCandidatos-----------------------" << endl;
	for(int i = 0; i < cs.size(); i++){
		cout << cs[i].GetId() << " - lista: " << cs[i].GetIdLista() << " - cargo: " << cs[i].GetIdCargo() << " - votante: " << cs[i].GetIdVotante() <<endl;
	}
	cout << "----------------ABMCandidato::GetCandidatos-----------------------" << endl;
	cout << "------------------------------------------------------------------" << endl;


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

void testConteo2(){

	//system("rm conteo.bt.bpt");
	//system("rm conteo.bt.bpt.fs");

	ABMConteo abm = ABMConteo();

	cout << endl << "Nuevo registro de conteo" << endl;
	cout << "Id distrito: ";
	string idDistrito = "4";
	cin >> idDistrito;

	cout << "Id Lista: ";
	string idLista = "4";
	cin >> idLista;

	cout << "Id Eleccion: ";
	string idEleccion = "4";
	cin >> idEleccion;

	abm.Add(idLista, Helper::StringToInt(idDistrito), Helper::StringToInt(idEleccion));

	cout << endl << endl;
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

	conteos = abm.GetConteoByLista(idLista);
	cout << "Conteos del lista :" << idLista << endl;
	for(int i = 0; i < conteos.size(); i++){
		cout << conteos[i].GetId() << endl;
	}

}

void Votar(Votante* votante){

	cout << "--------------------------------------------------------------------" << endl;
	cout << "--------------------------------------------------------------------" << endl;
	ABMConteo *abm = new ABMConteo();

	int idDistrito;
	string idLista;
	int idEleccion = 1;

	//for (int i=0; i<100; i++)
	//{
		//idDistrito = i;

		for (int j = 1; j < 10; j++)
		{
			idLista = Helper::IntToString(j);
			if(j > 6){
				abm->Add(idLista, votante->GetDistrito(), 17);	//Le asigno algunas listas al distrito del votante para probar
			}
			else{
				abm->Add(idLista, j+2, j+1);
			}
		}
	//}

		cout << "\n\n\nRegistros de Conteo:\n\n";
		abm->mostrarConteoPorPantalla();
		cout << "\n\n\n";

		cout << "--------------------------------------------------------------------" << endl;
		cout << "Usted va a votar en la elección número: 17" << endl;	//ACA HAY QUE SELECCIONAR LA ELECCION POR LA FECHA DE HOY, FALTAN HACER LOS INDICES DE ELECCION POR FECHA
		cout << "--------------------------------------------------------------------\n\n\n" << endl;

	string continuar = "yes";

	while(continuar == "yes"){


		cout << "Listas disponibles en su distrito(" << votante->GetDistrito() <<  "): " << endl;
		vector<Conteo> byDistrito = abm->GetConteoByDistrito(votante->GetDistrito());
		for(int i = 0; i < byDistrito.size(); i++){

			if(byDistrito[i].GetIdEleccion() == 17)	{//17 es la eleccion que le toca votar (HAY QUE SELECCIONAR LA ELECCION POR LA FECHA DE HOY)
				cout << "	Lista: " << byDistrito[i].GetIdLista() << endl;
			}

		}

		idLista;
		cout << endl << endl << endl << "Ingrese la lista que desee votar: ";
		cin >> idLista;

		//Votar:
		bool founded = false;
		for(int i = 0; i < byDistrito.size(); i++){

			if(byDistrito[i].GetIdLista() == idLista && byDistrito[i].GetIdEleccion() == 17){
				//Encontre el registro en el cual tengo que votar
				Conteo c = byDistrito[i];
				int cantidadVotos = abm->AddVoto(c.GetId());
				cout <<endl<<endl<<endl <<  "Usted voto la Lista " << c.GetIdLista() << ". Tiene un total del votos de: " << cantidadVotos << endl;
				founded = true;
			}
		}
		if(!founded){
			cout << endl<<endl << "La lista ingresada no fue encontrada -----------------------" << endl;
		}

		/***************************************
		 * ESTO ES PARA PROBAR QUE SE VAYAN SUMANDO LOS VOTOS - NO VA A ESTAR ASI POR QUE CADA PERSONA TIENE QUE VOTAR UNA SOLA VEZ
		 * ADEMAS ME FALTA ANOTAR EN CADA ELECCION QUE LA PERSONA YA VOTO
		*/

		cout << "Votar de nuevo (yes/no):";
		cin >> continuar;
	}

	cout << endl << endl << "Adios!!! --------------------------------------------------------------------" << endl << endl;
}

void Ingresar(){

	cout << endl;
	cout << "Ingrese dni:";
	string dni;// = "377";
	cin >> dni;

	cout << "Ingrese clave:";
	string clave;// = "password377";
	cin >> clave;

	ABMVotante abm = ABMVotante("votantes.ga");
	Votante* votante = abm.GetVotante(Helper::StringToLong(dni));
	bool login = votante->Authenticate(clave);
	if(login){
		cout << "\n\n\nBienvenido " << votante->GetNombreYApellido() << ". Usted pertenece al distrito: " << votante->GetDistrito() << endl<< endl<< endl;
		Votar(votante);
	}
	else{
		cout << "La clave ingresada es incorrecta" << endl;
	}
}



void agregarVotantes(){

	ABMVotante votantes = ABMVotante("votantes.ga");

	for(int i = 1; i < 400; i++){

		string nombre = "Votante ";
		string clave = "password";
		Votante votante = Votante(i, nombre.append(Helper::IntToString(i)), clave.append(Helper::IntToString(i)), "domicilio", i+1);
		votantes.Add(votante);
	}

	cout << endl << endl;
	cout << "--------------------- Votantes ---------------------------" << endl << endl;
	vector<Votante> lista = votantes.GetVotantes();
	for(int i = 0; i < lista.size(); i++){
		Votante v = lista[i];
		cout << "Dni: "<< v.GetDni() << ". Nombre" << v.GetNombreYApellido() << ". Clave: " << v.GetClave() << endl;
	}
}

void agregarDistritos(){

	system("rm distritos.ga.bpt");
	system("rm distritos.ga.bpt.fs");

	ABMDistrito abm = ABMDistrito("distritos.ga");

	for(int i = 1; i < 50	; i++){
		string distrito = "Distrito ";
		distrito.append(Helper::IntToString(i));
		abm.Add(distrito);
	}

	cout << endl << endl;
	cout << "--------------------- Disritos ---------------------------" << endl << endl;
	vector<Distrito> lista = abm.GetDistritos();
	for(int i = 0; i < lista.size(); i++){
		Distrito d = lista[i];
		cout << "Id: " << d.GetId() << ". Nombre: " << d.GetNombre() << endl;
	}
}


int main( int arg, char *argv[] ){

	//agregarDistritos();

	agregarVotantes();
	Ingresar();
	//testCandidato2();

//	BPlusTreeTest btest = BPlusTreeTest();
//	btest.run();

	//testConteo2();

//	testConteo();
	//pruebaListas();
//	pruebaListas2();
//	testABMDistrito();
	//pruebaArbol();

	//testLogging();
	cout << endl;
	return system("");
}
