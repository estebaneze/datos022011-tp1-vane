/*
 * Menues.cpp
 *
 *  Created on: 19/10/2011
 *      Author: gabriel
 */

#include "Menues.h"

Menues::Menues() {
	// TODO Auto-generated constructor stub

}

void Menues::MenuPpal()
{
	int fin=0;
	int opcion;

	while (fin==0){
		system("clear");
		printf("\n\n");
		printf("==========================================\n");
		printf("Bienvenido al sistema electronico de votos\n");
		printf("==========================================\n\n");
		printf("\t1. Votante\n");
		printf("\t2. Administrador\n");
		printf("\t3. Salir\n\n");
		printf("\tIngrese una opcion: ");
		scanf("%i",&opcion);
		printf("\n\n");
		switch (opcion) {
			case 1:
				fin=1;
				//menu votante
				MenuVotante();
				break;
			case 2:
				fin=1;
				//menu admin
				MenuAdmin();
				break;
			case 3:
				fin=1;
				break;
			default:
				fin=0;
				break;
		}
	}


}

void Menues::MenuAdmin()
{
	int fin=0;
		int opcion;

		while (fin==0){

			system("clear");
			printf("=============\n");
			printf("ADMINISTRADOR\n");
			printf("=============\n\n");
			printf("\t1. Ingresar al sistema\n");
			printf("\t2. Crear Administrador\n");
			printf("\t3. Modificar Administrador\n");
			printf("\t4. Borrar Administrador\n");
			printf("\t5. Volver al menu principal\n\n");
			printf("\tIngrese una opcion: ");
			scanf("%i",&opcion);
			switch (opcion) {
				case 1:{

					cout << endl << endl;
					cout << "Ingrese usuario: ";
					string usuario;
					cin >> usuario;

					ABMAdministrador *adm = new ABMAdministrador("administrador.ga");

					if (adm->existKey(usuario)){
						cout << endl;
						cout << "Ingrese password: ";
						string pass;
						cin >> pass;

						if (adm->GetAdmin(usuario)->GetClave()==pass){
							MenuABM();
						}
						else {
							cout << endl;
							cout << "Password incorrecta, presione una tecla para reintentar o [q] para volver" ;
							cin >> pass;
							if (pass=="q") MenuPpal();
						}
					}
					else{
						cout << "No existe el usuario ingresado" << endl;
						cin >> usuario;
						break;
					}

					break;
				}
				case 2:	{
						ABMAdministrador *abmAdmin = new ABMAdministrador("administrador.ga");
						bool listo = false;

						while (!listo){
								string nombre,pass;
								cout << endl << endl;
								cout << "Ingrese nombre: ";
								cin >> nombre;
								cout << endl << "Ingrese password: ";
								cin >> pass;

								cout << endl;

								if (!abmAdmin->existKey(nombre)){
										Administrador *adm = new Administrador(nombre,pass);

										abmAdmin->Add(adm);
										cout << "Administrador registrado." << endl << endl;
										cin >> nombre;
										listo=true;
								}
								else {
										cout << "Ya existe el usuario, presione cualquier tecla para reintentar o [q]=volver"<< endl << endl;
										string op;
										cin >> op;
										if (op=="q") MenuAdmin();
										}

							}
							delete abmAdmin;
						break;
				}
				case 3:{
						ABMAdministrador *abmAdmin = new ABMAdministrador("administrador.ga");
						bool listo = false;

						while (!listo){
						string nombre;
						cout << endl << endl;
						cout << "Ingrese nombre del administrador: ";
						cin >> nombre;
						cout << endl;

						if (abmAdmin->existKey(nombre)){
							string pass;
							cout << "Ingrese nueva password: ";
							cin >> pass;
							cout << endl;

							Administrador *adm = new Administrador(nombre,pass);

							abmAdmin->ModifyPassword(adm);
							listo=true;

							cout << "Administrador modificado." << endl << endl;
							cin >> nombre;
						}
						else {
							cout << "No existe el administrador ingresado, presione cualquier tecla para reintentar o [q]=volver"<< endl << endl;
							string op;
							cin >> op;
							if (op=="q") MenuAdmin();
						}

					}
					delete abmAdmin;
					//menu admin

					break;
					}

				case 4:
					{
						ABMAdministrador *abmAdmin = new ABMAdministrador("administrador.ga");
						bool listo = false;

						while (!listo){
							string nombre;
							cout << endl << endl;
							cout << "Ingrese nombre del administrador a eliminar: ";
							cin >> nombre;
							cout << endl;

							if (abmAdmin->existKey(nombre)){
								listo = abmAdmin->Delete(abmAdmin->GetAdmin(nombre));

								cout << "Administrador eliminado." << endl << endl;

							}
							else {
								cout << "No existe el administrador ingresado, presione cualquier tecla para reintentar o [q]=volver"<< endl << endl;
								string op;
								cin >> op;
								if (op=="q") MenuAdmin();
							}

						}
						delete abmAdmin;
						//menu admin

						break;
					}
				case 5:
					fin=1;
					this->MenuPpal();
					break;
				default:
					fin=0;
					break;
			}
		}

}

void Menues::MenuVotante()
{
	long dni;
	string pass;
	char c; //auxiliar

	int fin=0;
	int opcion;

	while (fin==0){
			system("clear");
			printf("=======\n");
			printf("VOTANTE\n");
			printf("=======\n\n");
			printf("\t1. Ingresar al sistema\n");
			printf("\t2. Volver al menu principal\n\n");
			printf("\tIngrese una opcion: ");
			scanf("%i",&opcion);

			switch (opcion) {
							case 1:
								{
								fin=1;

								ABMVotante votantes = ABMVotante("votantes.ga");


								printf("\n\n");
								printf("\tIngrese DNI: ");
								scanf("\t%d",&dni);


									if (votantes.existKey(dni)){
										Votante* votante = votantes.GetVotante(dni);

										printf("\tIngrese password: ");
										cin >> pass;

										if (votante->Authenticate(pass)){

											Menu_EleccionesXDistrito_votante(votante);
										}
										else{
											printf("Password Incorreca\n");
											cin >> c;
											this->MenuVotante();
											}
									}
									else{
										printf("No existe el usuario ingresado\n\n\n");
										cin >> c;
										this->MenuVotante();
									}


								}
								break;
							case 2:
								fin=1;
								this->MenuPpal();	//menu admin
								break;
							default:
								fin=0;
								break;

					}
			}

}

///FALTAN METODOS PARA QUE FUNCIONE
void Menues::Menu_EleccionesXDistrito_votante(Votante* votante)
{
	system("clear");
	cout << endl << endl;
	cout << "Bienvenido " << votante->GetNombreYApellido() << ", usted pertenece el distrito: " << votante->GetDistrito() << endl;

}


void Menues::Menu_ListasXEleccion(Eleccion *eleccion)
{
	/*cout << "Listas de las eleccion " << eleccion->GetId() << endl << endl;

	ListaIndex indexlistas = ListaIndex("indexLista.ix");
	vector<Lista> listas = indexListas.GetListasByIdEleccion(eleccion->GetId());

	if (!listas.empty()){
		string listaElegida;
		for (int i=0; i<listas.size();i++){
			cout << i+1 << ". " << listas.at(i).GetNombre() << endl;
		}

		cout << "Ingrese nombre de la lista que desea votar: ";
		cin >> listaElegida;

		cout << endl << endl;
		string opcion;
		cout << "Esta seguro que desea votar la lista[S/n]: " << listaElegida;
		cin >> opcion;

		switch (opcion){
			case 's':

				break;
			case 'n':
					system("clear");
					this->Menu_ListasXEleccion(eleccion);
				break;
		}


	}
	else {
		cout << "Error, No hay listas disponibles" << endl;
	}

*/
}

void Menues::MenuABM(){
	int fin=0;
	int opcion;

	while (fin==0){
		system("clear");
		printf("=========\n");
		printf("MENU ABMS\n");
		printf("=========\n\n");
		printf("\t1. ABM Distrito \n");
		printf("\t2. ABM Votante\n");
		printf("\t3. ABM Eleccion\n");
		printf("\t4. ABM Cargo\n");
		printf("\t5. ABM Lista\n");
		printf("\t6. ABM Candidato\n");
		printf("\t7. Reportes\n");
		printf("\t8. Volver menu administrador\n");

		printf("\tIngrese una opcion: ");
		scanf("%i",&opcion);

		switch (opcion) {
			case 1:	{

					bool listo=false;

					while (!listo){
						string nombre;
						cout << "Ingrese nuevo nombre de distrito: ";
						cin >> nombre;

						ABMDistrito *dis = new ABMDistrito("distrito");

						cout << "Distrito agregado con ID: " << dis->Add(nombre) << endl << endl;
						cin >> nombre;
						listo = true;
						delete dis;
						}

					break;
					}
			case 2:
					{
						bool listo=false;

						while (!listo){
							string dni;
							cout << "Ingrese DNI del usuario: ";
							cin >> dni;
							ABMVotante *vot = new ABMVotante("votante");

							if (!vot->existKey(Helper::StringToLong(dni))){

								string _nombreYApellido;
								string _clave;
								string _domicilio;

								cout << "Ingrese Nombre y Apellido: ";
								cin >> _nombreYApellido;
								cout << endl;
								cout << "Ingrese clave: ";
								cin >> _clave;
								cout << endl;
								cout << "Ingrese domicilio: ";
								cin >> _domicilio;
								cout << endl;

								int id_distrito;
								cout << "Ingrese IdDistrito: ";
								cin >> id_distrito;

								ABMDistrito *dis = new ABMDistrito("distrito");
								if (dis->Exists(id_distrito)){
									Votante *votante = new Votante(Helper::StringToLong(dni),_nombreYApellido,_clave,_domicilio,id_distrito);
									vot->Add(votante);
									delete vot;
									delete votante;
									listo=true;
								}
								else {
									cout << "No existe el IdDistrito ingresado, presione una tecla para reintentar o [q] para volver";
									string c;
									cin >> c;
									if (c=="q") listo=true;
									break;
								}
							}
							else{
								cout << endl;
								cout << "Ya existe el DNI ingresado, presione una tecla para reintentar o [q] para volver";
								cin >> dni;
								if (dni=="q") listo=true;
							}
						}

					break;
					}
			case 3:
					{
					fin=1;
					break;
					}
			case 4:
					{
					fin=1;
					break;
					}

			case 5:
					{
					fin=1;
					break;
					}

			case 6:
					{
					fin=1;
					break;
					}
			case 7:
					{
					fin=1;
					break;
					}

			case 8:
					{
					fin=1;
					MenuAdmin();
					break;
					}

			default:
					fin=0;
					break;

						}
				}


}

Menues::~Menues() {
	// TODO Auto-generated destructor stub
}







