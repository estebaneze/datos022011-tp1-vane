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

				//menu votante
				MenuVotante();
				break;
			case 2:

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

						bool listo=false;
						ABMAdministrador *adm = new ABMAdministrador("administrador.ga");
						while (!listo){
							cout << endl << endl;
							cout << "Ingrese usuario: ";
							string usuario;
							cin >> usuario;

							if (adm->existKey(usuario)){
								cout << endl;
								cout << "Ingrese password: ";
								string pass;
								cin >> pass;

								if (adm->GetAdmin(usuario)->GetClave()==pass){

									MenuABM();
									listo=true;
								}
								else {
									cout << endl;
									cout << "Password incorrecta, presione una tecla para reintentar o [q] para volver" ;
									cin >> pass;
									if (pass=="q") listo=true;
								}
							}
							else{
								cout << "No existe el usuario ingresado, presione una tecla para reintentar o [q] para volver" ;

								cin >> usuario;
								if (usuario=="q") listo=true;
								break;
							}
						}
						delete adm;
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
								cin >> dni;


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
					MenuABMDistrito();

					break;
					}
			case 2:
					{
					MenuABMVotante();
					break;
					}
			case 3:
					{
					MenuABMEleccion();
					break;
					}
			case 4:
					{
					MenuABMCargo();
					break;
					}

			case 5:
					{
					MenuABMLista();
					break;
					}

			case 6:
					{
					MenuABMCandidato();
					break;
					}
			case 7:
					{
					Reportes();
					break;
					}

			case 8:
					{
					fin=1;

					break;
					}

			default:
					fin=0;
					break;

						}
				}


}

void Menues::MenuABMDistrito(){

int fin=0;
int opcion;

	while (fin==0){
		system("clear");
		printf("============\n");
		printf("ABM DISTRITO\n");
		printf("============\n\n");
		printf("\t1. Alta Distrito \n");
		printf("\t2. Baja Distrito \n");
		printf("\t3. Modificacion Distrito\n");
		printf("\t4. Volver\n\n");

		printf("\tIngrese una opcion: ");
		scanf("%i",&opcion);

		switch (opcion) {
					case 1:	{
							system("clear");
							bool listo=false;
							ABMDistrito *dis = new ABMDistrito("distrito");

							cout << "ALTA DISTRITO" << endl;
							cout << "-------------" << endl << endl;

							while (!listo){
								string nombre;

								cout << "Ingrese nuevo nombre de distrito: ";
								cin >> nombre;

								int ok = dis->Add(nombre);
								if (ok!=-1){
									cout << "Distrito agregado con ID: " << ok << endl << endl;
									cin >> nombre;
									listo = true;
								}
								else{
									cout << "Ya existe el distrito ingresado, presione una tecla para reintentar o [q] para volver";
									cin >> nombre;
									if (nombre=="q") listo=true;
								}

							}
							delete dis;

							break;
							}
					case 2:	{
							system("clear");
							bool listo=false;
							while (!listo){
								int id;
								cout << "BAJA DISTRITO" << endl;
								cout << "-------------" << endl << endl;
								cout << "Ingrese ID del distrito: ";
								cin >> id;
								ABMDistrito *dis = new ABMDistrito("distrito");

								cout << "Se elimino el distrito ID : " << dis->Delete(id) << endl << endl;
								cin >> id;
								listo = true;
								delete dis;
								}
							break;
							}
					case 3:
							{
							// FALTA SOLO ESTE CASO
							break;
							}
					case 4:
							{
							fin=1;
							break;
							}
					default:
							fin=0;
							break;
					}
		}





}

void Menues::MenuABMLista()
{
	int fin=0;
	int opcion;

		while (fin==0){
			system("clear");
			printf("=========\n");
			printf("ABM LISTA\n");
			printf("=========\n\n");
			printf("\t1. Alta Lista \n");
			printf("\t2. Baja Lista \n");
			printf("\t3. Modificacion Lista\n");
			printf("\t4. Volver\n\n");
			printf("\tIngrese una opcion: ");
			scanf("%i",&opcion);
			cout << endl;
			switch (opcion) {
						case 1:	{
							bool listo=false;
							ABMLista *abmLista = new ABMLista();
							system("clear");
							printf("ALTA LISTA\n");
							printf("------------\n\n");

							while (!listo){
								string nombre;
								cout << "Ingrese nombre de la Lista: ";
								cin >> nombre;
								cout << endl;

								if (!abmLista->existKey(nombre)){

									ABMEleccion *abmEleccion = new ABMEleccion();
									string eleccion;
									bool listo2=false;
									while (!listo2){
										cout << "Ingrese el ID_Eleccion asociada a la Lista: ";
										cin >> eleccion;
										cout << endl;
										if (abmEleccion->ExistsKey(eleccion)) {
											Lista *lista = new Lista(nombre,eleccion);
											abmLista->Add(lista);
											listo2=true;

											delete lista;
										}
										else{
											cout << "No existe el ID Eleccion, presione una tecla para reintentar o [q] para salir";
											string c;
											cin >> c;
											if (c=="q") {

												listo2=true;
											}
										}
									}
									listo=true;
								}
								else{
									//existe
									cout << "La lista ingresada ya existe, presione una tecla para reintentar o [q] para salir";
									string c;
									cin >> c;
									if (c=="q") listo=true;
								}

							}
							delete abmLista;
							break;

						}
						case 2:{
							bool listo=false;
							ABMLista *abmLista = new ABMLista();
							system("clear");
							printf("BAJA LISTA\n");
							printf("----------\n\n");

							while (!listo){
								string nombre;
								cout << "Ingrese nombre de la Lista: ";
								cin >> nombre;
								cout << endl;

								if (!abmLista->existKey(nombre)){

									listo = abmLista->Delete(abmLista->GetLista(nombre));
									}
								else{
									cout << "No existe la lista "<< nombre << ", presione una tecla para reintentar o [q] para salir";
									string c;
									cin >> c;
									if (c=="q") listo=true;
									}
							}
							delete abmLista;
							break;
						}
						case 3:{
								//falta esto solo
								break;
								}
						case 4:{
								fin=1;
								break;
								}
						default:{
							fin=0;
							break;
						}
			}
		}
}

void Menues::MenuABMCargo()
{
}

void Menues::MenuABMCandidato()
{
}

void Menues::Reportes()
{
}

void Menues::MenuABMVotante()
{
int fin=0;
int opcion;

	while (fin==0){
		system("clear");
		printf("============\n");
		printf("ABM VOTANTE\n");
		printf("============\n\n");
		printf("\t1. Alta votante \n");
		printf("\t2. Baja votante \n");
		printf("\t3. Modificacion votante\n");
		printf("\t4. Volver\n\n");
		printf("\tIngrese una opcion: ");
		scanf("%i",&opcion);

		switch (opcion) {
					case 1:	{
						bool listo=false;
						ABMVotante *vot = new ABMVotante("votante");

						while (!listo){
							string dni;
							system("clear");
							printf("ALTA VOTANTE\n");
							printf("------------\n\n");

							cout << "Ingrese DNI del usuario: ";
							cin >> dni;

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

									delete votante;
									listo=true;
									cout << endl << endl;
									cout << "votante agregado satisfactoriamente.";
									cin >> dni;

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
						delete vot;
						break;
							}
					case 2:	{
							bool listo=false;
							ABMVotante *vot = new ABMVotante("votante");
							while (!listo){
								system("clear");
								printf("BAJA VOTANTE\n");
								printf("------------\n\n");

								string dni;
								cout << "Ingrese DNI del usuario: ";
								cin >> dni;

								if (vot->existKey(Helper::StringToLong(dni))){
									vot->Delete(vot->GetVotante(Helper::StringToLong(dni)));

									cout << endl << endl;
									cout << "votante eliminado." << endl;
									cout << "Presione una tecla para eliminar otro o [q] para volver";
									cin >> dni;
									listo =true;
								}
								else{
									cout << endl << endl;
									cout << "No existe el votante, presione una tecla para reintentar o [q] para volver";
									cin >> dni;
									if (dni=="q") listo=true;
								}

							}
							delete vot;
							break;
							}
					case 3:
							{
								//FALTA SOLO ESTE CASO
								break;
							}
					case 4:
							{
							fin=1;
							break;
							}
					default:
							fin=0;
							break;
					}
		}

}

void Menues::MenuABMEleccion()
{
	int fin=0;
	int opcion;

		while (fin==0){
			system("clear");
			printf("============\n");
			printf("ABM ELECCION\n");
			printf("============\n\n");
			printf("\t1. Alta eleccion \n");
			printf("\t2. Baja eleccion \n");
			printf("\t3. Modificar eleccion\n");
			printf("\t4. Volver\n\n");
			printf("\tIngrese una opcion: ");
			scanf("%i",&opcion);

			switch (opcion) {
						case 1:	{
							bool listo=false;
							ABMEleccion *el = new ABMEleccion();

							while (!listo){
								string dni;
								system("clear");
								printf("ALTA ELECCION\n");
								printf("------------\n\n");

								short dia,mes,anio;
								cout << "Ingrese fecha de la eleccion: "<<endl;
								cout << "Año: ";
								cin >> anio;
								cout << endl << "Mes: ";
								cin >> mes;
								cout << endl << "Dia: ";
								cin >> dia;
								cout << endl << endl;
								//habria que validar fecha
								Fecha fecha = Fecha(dia,mes,anio);

								bool listo2=false;
								while (!listo2){
									string nombre;
									int idCargo;
									cout << "Ingrese nombre cargo principal: ";
									cin >> nombre;


									//busco si existe el nombre
									ABMCargo *abmCargo = new ABMCargo();

									bool existNombre=false;
									vector<Cargo> vecCargos = abmCargo->GetCargos();

									for (unsigned int i=0;((i<vecCargos.size()) && (!existNombre));i++){

										if ((vecCargos.at(i).GetNombre())==nombre){
											existNombre=true;
											idCargo= vecCargos.at(i).GetId();
										}
									}
									delete abmCargo;

									if (!existNombre){
										cout << endl << endl;
										cout << "El cargo no existente, presione una tecla para reintentar o [q] para volver";
										cin >> nombre;
										if (nombre=="q") {
											listo2=true;
											listo=true;
										}
									}
									else{

										//verifico que la eleccion (fecha_idcargo) no exista
										Eleccion *eleccion = new Eleccion(idCargo,fecha);
										int existe = el->Add(eleccion);

										if (existe==0){
											bool finCargaDistrito=false;
											ABMDistrito *dis = new ABMDistrito("distrito");
											IntegerList distritos;

											//cargo lista de distritos para la eleccion
											while(!finCargaDistrito){
												int id_distrito;
												string op;
												cout << "Desea carga un IDDistrito a la eleccion, escriba [s]=SI o [n]=terminar: ";
												cin >> op;

												if (op=="s"){

													cout << endl;
													cout << "Ingrese ID del distrito: ";
													cin >> id_distrito;
													cout << endl;

													if (dis->Exists(id_distrito)){
														distritos.Add(id_distrito);
														cout << "Id distrito "<< id_distrito << " cargado con exito" << endl;

														}
													else {
														cout << "No existe el IdDistrito " << id_distrito << " , presione una tecla para reintentar o [q] para terminar";
														string c;
														cin >> c;
														if (c=="q") finCargaDistrito=true;

														}
												}
												else {
													//termine de cargar la eleccion, vuelvo al menu
													finCargaDistrito=true;
												}
											}//fin de carga de distritos

										delete dis;

										//guardo eleccion
										for (int i=0;i<distritos.GetSize();i++){
											eleccion->AddDistrito(distritos.Get(i));
										}

										el->Modify(eleccion);
										listo2=true;
										listo=true;

										}
										else{
											cout << endl;
											cout << "Ya existe la eleccion (Fecha y Cargo) ingresa, presione una tecla para volver."<< endl;
											char c;
											cin >> c;
											listo=true;
										}
										delete eleccion;
									}

								}
							}



							delete el;
							break;
								}
						case 2:	{
								bool listo = false;
								ABMEleccion *el = new ABMEleccion();

								while (!listo){
									string dni;
									system("clear");
									printf("BAJA ELECCION\n");
									printf("------------\n\n");

									short dia,mes,anio;
									cout << "Ingrese fecha de la eleccion: "<<endl;
									cout << "Año: ";
									cin >> anio;
									cout << endl << "Mes: ";
									cin >> mes;
									cout << endl << "Dia: ";
									cin >> dia;
									cout << endl << endl;
									//habria que validar fecha
									Fecha fecha = Fecha(dia,mes,anio);

									bool listo2=false;
									while (!listo2){
										string nombre;
										int idCargo;
										cout << "Ingrese nombre cargo principal: ";
										cin >> nombre;


										//busco si existe el nombre
										ABMCargo *abmCargo = new ABMCargo();

										bool existNombre=false;
										vector<Cargo> vecCargos = abmCargo->GetCargos();

										for (unsigned int i=0;((i<vecCargos.size()) && (!existNombre));i++){

											if ((vecCargos.at(i).GetNombre())==nombre){
												existNombre=true;
												idCargo= vecCargos.at(i).GetId();
											}
										}
										delete abmCargo;
										if (!existNombre){
											cout << endl << endl;
											cout << "El cargo no existente, presione una tecla para reintentar o [q] para volver";
											cin >> nombre;
											if (nombre=="q") {
												listo2=true;
												listo=true;
											}
										}
										else{
											//verifico que la eleccion (fecha_idcargo) no exista
											Eleccion *eleccion = new Eleccion(idCargo,fecha);

											if (el->Delete(eleccion)){
												cout <<endl;
												cout << "Eleccion eliminada, presione una teclado para volver al menu"<< endl;
												char c;
												cin >> c;
												listo=true;
												listo2=true;
											}
											else{
												cout <<endl;
												cout << "No existe eleccion ingresada, presione una teclado para volver al menu"<< endl;
												char c;
												cin >> c;
												listo=true;
												listo2=true;
											}
										}
									}
								}
								break;
								}
						case 3:
								{
									//FALTA SOLO ESTE CASO
									break;
								}
						case 4:
								{
								fin=1;
								break;
								}
						default:
								fin=0;
								break;
						}
			}
}



Menues::~Menues() {

}







