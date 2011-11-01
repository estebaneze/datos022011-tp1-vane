/*
 * TestArbol.cpp
 *
 *  Created on: 21/10/2011
 *      Author: loo
 */
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


using namespace std;

#include "Test.h"

Test::Test() {
        // TODO Auto-generated constructor stub

}

void Test::testPersistorDistrito(){
        ABMDistrito *abmDistrito = new ABMDistrito();

        abmDistrito->Add("Distrito");
        abmDistrito->mostrarDistritosPorPantalla();
}

void Test::testPersistorConteo(){
        ABMConteo *abmConteo = new ABMConteo();

        abmConteo->Add("Lista1", 1, 1);
        abmConteo->mostrarConteoPorPantalla();
}

void Test::testABMDistrito(){

//      system("rm arboldistrito.bpt");
//      system("rm arboldistrito.bpt.fs");

        cout <<endl<<endl;

        int idDistrito;
        string distrito = "Distrito";
        ABMDistrito *abmDistrito = new ABMDistrito();

        int nroDist = 1;
        int maximoID=499;
        for (int i=1; i<500; i++)       {
                        string dato = distrito  +  Helper::IntToString(i);
                        maximoID=abmDistrito->Add(dato);
        }

        abmDistrito->mostrarDistritosPorPantalla();


        cout << endl<< endl;
  /*      Distrito * d = abmDistrito->GetDistrito(maximoID-50);
        cout << endl<< "Pruebo modificar Distrito  con ID: " << d->GetId() << d->GetNombre() << endl;
        d->SetNombre("OHHH AMI ME MODIFICARON");

       // abmDistrito->Modify(*d);
        abmDistrito->mostrarDistritosPorPantalla();
*/
        cout << endl<< endl;
        Distrito * d  = abmDistrito->GetDistrito(maximoID-5);
        cout << endl<< "Pruebo eliminar Distrito  con ID: " << d->GetId() << d->GetNombre() << endl;

        abmDistrito->Delete(d->GetId());
        abmDistrito->mostrarDistritosPorPantalla();

}

void Test:: testConteo(){

        ABMConteo *abm = new ABMConteo();

        int idDistrito;
        int idLista;

        int dia = 1;
                for (int j=100; j<120; j++)
                {
                        idLista = j;
                        abm->Add(Helper::IntToString(idLista), j-56, j+1);
                        dia++;
                }

        abm->mostrarConteoPorPantalla();
        cout << endl << endl << endl;

        vector<Conteo> c1 = abm->GetConteoByEleccion(101);
        vector<Conteo> c2 = abm->GetConteoByEleccion(102);
        vector<Conteo> c3 = abm->GetConteoByEleccion(103);

        cout << "Conteos de la eleccion: 45 1-1-2011:"<< endl;
        for(int i = 0; i < c1.size(); i++){
                cout << "Id de Conteo:" <<c1[i].GetId() << endl;
                cout << "Distrito:" << c1[i].GetIdDistrito() << endl;
                cout << "Lista:" << c1[i].GetIdLista() << endl;
                cout << "Eleccion:" << c1[i].GetIdEleccion() << endl;
        }

        cout<< endl << endl << "Conteos de la eleccion: 45 2-1-2011:"<< endl;
                for(int i = 0; i < c2.size(); i++){
                        cout << "Conteo:" << c2[i].GetId() << endl;
                        cout << "Distrito:" << c2[i].GetIdDistrito() << endl;
                        cout << "Lista:" << c2[i].GetIdLista() << endl;
                        cout << "Eleccion:" << c2[i].GetIdEleccion() << endl;
                }

                cout<< endl << endl << "Conteos de la eleccion: 45 3-1-2011:"<< endl;
                                for(int i = 0; i < c3.size(); i++){
                                        cout << "Conteo:" << c3[i].GetId() << endl;
                                        cout << "Distrito:" << c3[i].GetIdDistrito() << endl;
                                        cout << "Lista:" << c3[i].GetIdLista() << endl;
                                        cout << "Eleccion:" << c3[i].GetIdEleccion() <<endl;
                                }


                cout << endl << endl << endl;
                string distrito;
                cout << "Ingrese distrito: ";
                cin >> distrito;

                c3 = abm->GetConteoByDistrito(Helper::StringToInt(distrito));
                cout<< endl << endl << "Conteos del disrito: " << distrito << endl;
                for(int i = 0; i < c3.size(); i++){
                        cout << "Conteo:" << c3[i].GetId() << endl;
                        cout << "Distrito:" << c3[i].GetIdDistrito() << endl;
                        cout << "Lista:" << c3[i].GetIdLista() << endl;
                        cout << "Eleccion:" << c3[i].GetIdEleccion() << endl;
                }


}

void Test::pruebaListas(){

        ABMLista Listas = ABMLista();

        Lista *l1 = new Lista("aalonso8",2);
        Lista *l2 = new Lista("ados", 3);
        Lista *l3 = new Lista("atres", 4);
        Lista *l4 = new Lista("acuatro", 2);
        Lista *l5 = new Lista("acinco", 3);
        Lista *l6 = new Lista("aseis", 4);
        Lista *l7 = new Lista("saiete", 4);
        Lista *l8 = new Lista("oacho", 4);
        Lista *l9 = new Lista("aaa",9);
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

/*      cout << endl << endl;
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

void Test::pruebaListas2(){

        ABMLista Listas = ABMLista();

        Lista *l1 = new Lista("a", 2);
                Lista *l2 = new Lista("ados", 3);
                Lista *l3 = new Lista("atres", 4);
                Lista *l4 = new Lista("acuatro", 2);
                Lista *l5 = new Lista("acinco", 3);
                Lista *l6 = new Lista("aseis", 4);
                Lista *l7 = new Lista("asiete", 4);
                Lista *l8 = new Lista("aocho", 4);
                Lista *l9 = new Lista("aaa",9);
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
        int idEleccion;
        cin >> idEleccion;


        cout << endl << endl << "Modificar lista - Nombre:" << nombreLista<< "- Eleccion: " << idEleccion<<endl;

        Lista *l = new Lista(nombreLista, idEleccion);
        Listas.Modify(l);

        //Listas.mostrarListasPorPantalla();

        cout << endl;
/*      cout << "Listas: " << endl;
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


void Test::testCandidato2(){

      cout << endl;
        ABMCandidato abmc = ABMCandidato();
        cout << endl;

        for(int i = 5; i < 100; i++){

        	abmc.Add(Helper::IntToString(i),i,i);
        }

        vector<Candidato> cs = abmc.GetCandidatos();
        cout << "----------------ABMCandidato::GetCandidatos-----------------------" << endl;
        for(int i = 0; i < cs.size(); i++){
                cout << cs[i].GetId() << " - lista: " << cs[i].GetIdLista() << " - cargo: " << cs[i].GetIdCargo() << " - votante: " << cs[i].GetIdVotante() <<endl;
        }
        cout << "----------------ABMCandidato::GetCandidatos-----------------------" << endl;
        cout << "------------------------------------------------------------------" << endl;


}


void Test::testCandidato(){

        cout << endl;
        ABMCandidato abmc = ABMCandidato();

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

        Candidato *c3 = new Candidato("3", 3, 3, 3);
        Candidato *c4 = new Candidato("3", 3, 3, 4);
        Candidato *c5 = new Candidato("3", 3, 3, 5);
        Candidato *c10 = new Candidato("3", 3, 3, 10);
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
        Candidato *c1 = new Candidato(idLista, Helper::StringToLong(dni), Helper::StringToInt(idCargo), Helper::StringToInt(idCandidato));
        abmc.Modify(c1);
        cout << "Candidatos: "<< endl;
        abmc.mostrarCandidatosPorPantalla();

}

void Test::testLogging(){

        Log::WriteLog("Inserto algo", "log.txt");
        Log::WriteLog("Inserto algo","log.txt");
        Log::WriteLog("Inserto algo","log.txt");

}

void Test::firstSetTest() {

        system("rm testTree");
        system("rm testTree.fs");

        cout << endl << endl << ConfigurationMananger::getInstance()->getBufferSizeTree() << endl << endl;

        BPlusTree bp = BPlusTree(ConfigurationMananger::getInstance()->getBufferSizeTree(),"testTree");

        int i;
        //cout << "Insertamos los elementos 100, 101, 102,103,104 todos con 4 bytes de datos: total de cada registro en el nodo hoja= 12 bytes" << endl;

        for (i = 100; i < 105; i++) {
                cout << "Insertando el elemento: " << i << endl;

                KeyInt key =  i;
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

void Test::testConteo2(){

        //system("rm conteo.bt.bpt");
        //system("rm conteo.bt.bpt.fs");
/*
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
*/
}

void Test::Votar(Votante* votante){

        cout << "--------------------------------------------------------------------" << endl;
        cout << "--------------------------------------------------------------------" << endl;
        ABMConteo *abm = new ABMConteo();

        int idDistrito;
        string idLista;
        int idEleccion = 1;

        Eleccion* e1 = new Eleccion(1, Fecha(2,3,2010));
        Eleccion* e2 = new Eleccion(1, Fecha(2,2,2010));
        //for (int i=0; i<100; i++)
        //{
                //idDistrito = i;

                for (int j = 1; j < 10; j++)
                {
                        idLista = Helper::IntToString(j);
                        if(j > 6){
                                abm->Add(idLista, votante->GetDistrito(), e1->GetId()); //Le asigno algunas listas al distrito del votante para probar
                        }
                        else{
                                abm->Add(idLista, j+2, e2->GetId());
                        }
                }
        //}

                cout << "\n\n\nRegistros de Conteo:\n\n";
                abm->mostrarConteoPorPantalla();
                cout << "\n\n\n";

                cout << "--------------------------------------------------------------------" << endl;
                cout << "Usted va a votar en la elecci�n n�mero: 17" << endl;   //ACA HAY QUE SELECCIONAR LA ELECCION POR LA FECHA DE HOY, FALTAN HACER LOS INDICES DE ELECCION POR FECHA
                cout << "--------------------------------------------------------------------\n\n\n" << endl;

        string continuar = "yes";

        while(continuar == "yes"){


                cout << "Listas disponibles en su distrito(" << votante->GetDistrito() <<  "): " << endl;
                vector<Conteo> byDistrito = abm->GetConteoByDistrito(votante->GetDistrito());
                for(int i = 0; i < byDistrito.size(); i++){

                        if(byDistrito[i].GetIdEleccion() == 17) {//17 es la eleccion que le toca votar (HAY QUE SELECCIONAR LA ELECCION POR LA FECHA DE HOY)
                                cout << "       Lista: " << byDistrito[i].GetIdLista() << endl;
                        }

                }


                cout << endl << endl << endl << "Ingrese la lista que desee votar: ";
                cin >> idLista;

                //Votar:
                bool founded = false;
                for(int i = 0; i < byDistrito.size(); i++){

                        if(byDistrito[i].GetIdLista() == idLista && byDistrito[i].GetIdEleccion() == 17){
                                //Encontre el registro en el cual tengo que votar
                                Conteo c = byDistrito[i];
                                abm->AddVoto(c.GetId(), votante);
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

void Test::Ingresar(){

        cout << endl;
        cout << "Ingrese dni:";
        string dni;// = "377";
        cin >> dni;

        cout << "Ingrese clave:";
        string clave;// = "password377";
        cin >> clave;

        ABMVotante abm = ABMVotante();
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



void Test::agregarVotantes(){

        ABMVotante votantes = ABMVotante();

        for(int i = 1; i < 400; i++){

                string nombre = "Votante ";
                string clave = "password";
                Votante *votante = new Votante(i, nombre.append(Helper::IntToString(i)), clave.append(Helper::IntToString(i)), "domicilio", i+1);
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

void Test::agregarDistritos(){

        system("rm distritos.ga.bpt");
        system("rm distritos.ga.bpt.fs");

        ABMDistrito abm = ABMDistrito();

        for(int i = 1; i < 50   ; i++){
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

void Test::testReportes(){

        agregarVotantes();

        Votante* votante;
        ABMVotante abmv = ABMVotante();
        votante = abmv.GetVotante(399);

        /* initialize random seed: */
        srand ( time(NULL) );
        cout << endl << endl;

        int number;

        ABMConteo abmc = ABMConteo();

        ABMEleccion abme = ABMEleccion();
        Eleccion* e1 = new Eleccion(1, Fecha(2,3,2010));
        Eleccion* e2 = new Eleccion(1, Fecha(22,3,2010));
        Eleccion* e3 = new Eleccion(1, Fecha(23,3,2010));
        Eleccion* e4 = new Eleccion(1, Fecha(23,3,2009));

        abme.Add(e1);
        abme.Add(e2);
        abme.Add(e3);
        abme.Add(e4);

        string lista = "1";
        for(int i = 0; i < 5; i++){

                number = rand() % 100;
                Conteo c;
          if(i > 3)
                  c = Conteo(lista, 12, e1->GetId(), 1, number);
          else
                  c = Conteo(lista, 23, e2->GetId(), 1, number);

          int idConteo = abmc.Add(c.GetIdLista(), c.GetIdDistrito(), c.GetIdEleccion());

          int cant = 2 * i;
          for(int j = 1; j <= cant; j++){
                  abmc.AddVoto(idConteo, votante);
          }
        }

        lista = "12";
        for(int i = 0; i < 5; i++){

                number = rand() % 100;
                Conteo c;
          if(i > 3)
                  c = Conteo(lista, 12, e3->GetId(), 3, number);
          else
                  c = Conteo(lista, 23, e4->GetId(), 4, number);

          int idConteo = abmc.Add(c.GetIdLista(), c.GetIdDistrito(), c.GetIdEleccion());

          int cant = 2 * i;
          for(int j = 1; j <= cant; j++){
                  abmc.AddVoto(idConteo, votante);
          }
        }

        lista = "11";
        for(int i = 0; i < 5; i++){

                number = rand() % 100;
                Conteo c;
          if(i > 3)
                  c = Conteo(lista, 12, e2->GetId(), 3, number);
          else
                  c = Conteo(lista, 23, e3->GetId(), 3, number);

          int idConteo = abmc.Add(c.GetIdLista(), c.GetIdDistrito(), c.GetIdEleccion());

          int cant = 2 * i;
          for(int j = 1; j <= cant; j++){
                  abmc.AddVoto(idConteo, votante);
          }
        }

        vector<Conteo> resultados = abmc.GetConteoByLista("11");

        for(int i = 0; i < resultados.size(); i++){
                cout << "eleccion: " << resultados[i].GetIdDistrito() << ". Votos:  " << resultados[i].GetCountVotos() << endl;
        }
}

void Test::testEleccionesIndex(){


        ABMEleccion cs = ABMEleccion();
        cs.Add(new Eleccion(1, Fecha(1,1,2003)));
        cs.Add(new Eleccion(1, Fecha(1,6,2003)));
        cs.Add(new Eleccion(5, Fecha(1,6,2003)));
        cs.Add(new Eleccion(6, Fecha(1,7,2003)));
        cs.Add(new Eleccion(7, Fecha(1,7,2003)));
        cs.Add(new Eleccion(19, Fecha(1,7,2003)));

        cs.Add(new Eleccion(46, Fecha(1,7,2003)));
        cs.Add(new Eleccion(75, Fecha(1,7,2003)));
        cs.Add(new Eleccion(7, Fecha(1,7,2003)));

        cs.Delete(new Eleccion(7, Fecha(1,7,2003)));

        Eleccion * e = new Eleccion(46, Fecha(1,7,2003));
        e->AddDistrito(5);
        cs.Modify(e);
        cout << endl << endl << "Done!!!!!!!!!!" << endl;
}


void Test::testArbolVane(){

        //system("del testTree.bpt");
        //system("del testTree.bpt.fs");

        int bufferSize = ConfigurationMananger::getInstance()->getBufferSizeTree();
        BPlusTree* tree = new BPlusTree(bufferSize,Helper::concatenar("testTree","bpt","."));

        //BNode* e = tree->find("2344");
        Element* e = tree->findExact(2344) ;
        cout << "sdsdsd   ---- " <<  e->getData() << endl;

        for(int i = 0; i < 200; i++){

                string key = Helper::IntToString(i);

                string str = "data";
                str.append(Helper::IntToString(i+1));
                str.append("|data");
                str.append(Helper::IntToString(i+2));
                str.append("|data");
                str.append(Helper::IntToString(i+3));

                Data data = (Data)str.c_str();
                int longData = str.length();

                Element * element=new Element(i, data, longData);

                try{
                        tree->insert(element);
                }
                catch(ElementAlreadyExists)
                {
                        cout << "ya existe " << i << endl;
                }

        }

        cout << endl << endl << "---------------------------------" << endl;
        cout << "Export tree:" << endl << endl;
        tree->exportTree();

        cout << endl << endl << "---------------------------------" << endl << endl;

        string key;

        while(key != "q"){

                cout << "Ingrese key (para salir ingrese q): ";

                cin >> key;
                //key = "99";
                //for(int i = 0; i < 50; i++){

                        //string key = "key";
                        //key.append(Helper::IntToString(i));

                        Element* r = tree->findExact(Helper::StringToInt(key));

                        if(r != NULL){

                                /*vector<string> data  = Helper::split(r->exportNode(), '|');
                                cout << "            ";
                                for(int j = 0; j < data.size(); j++){
                                        cout << data[j] << " - ";
                                }
*/
                                cout << r->getData();
                                cout << endl << endl;
                        }
                //}
                        //key = "q";
        }

}

void Test::testConteo3(){

        ABMConteo c = ABMConteo();
        Eleccion* e1 = new Eleccion(1, Fecha(12,12,2010), 1);
        Eleccion* e2 = new Eleccion(1, Fecha(13,12,2010), 2);
        Eleccion* e3 = new Eleccion(1, Fecha(14,12,2010), 3);
        Eleccion* e4 = new Eleccion(1, Fecha(1,1,2011), 4);

        string lista1 = "lista1";
        string lista2 = "lista2";
        string lista3 = "lista3";
        string lista4 = "lista4";

        int dist1 = 1;
        int dist2 = 2;
        int dist3 = 3;
        int dist4 = 4;

        vector<int> conteos;
        for(int i = 1; i < 200; i++){
                int idConteo = c.Add(Helper::IntToString(i), i, i);
                conteos.push_back(idConteo);
        }

        c.mostrarConteoPorPantalla();
        cout << "peperulo " << endl;
        c.AddVoto(conteos[0], new Votante(3, "3", "sdsd", "sdsd", 1));
        c.AddVoto(conteos[1], new Votante(4, "3", "sdsd", "sdsd", 2));
        c.AddVoto(conteos[2], new Votante(5, "3", "sdsd", "sdsd", 3));





                //De 101 a 199 voto dos veces
                /*      for(int i = 101; i < conteos.size(); i++){
                                c.AddVoto(conteos[i], new Votante(3, "3", "sdsd", "sdsd", i));
                                c.AddVoto(conteos[i], new Votante(55, "3", "sdsd", "sdsd", i));
                        }
        */

        for(int i = 0; i < 200; i++){
                Conteo* c1 = c.GetConteo(i);
                cout << "Votos: " << c1->GetCountVotos() << endl;
        }

        cout << endl << endl << "Done" << endl;

}

Test::~Test() {
        // TODO Auto-generated destructor stub
}
