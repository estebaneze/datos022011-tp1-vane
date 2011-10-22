/*
 * Menues.cpp
 *
 *  Created on: 19/10/2011
 *      Author: gabriel
 */

#include "Menues.h"

Menues::Menues() {


}

void Menues::MenuPpal()
{
	int fin=0;
	char opcion;

	while (fin==0){
		system("clear");
		printf("\n\n");
		printf("Fecha Actual: ");
	    cout	<< this->fechaActual().getDia() << "-"<< this->fechaActual().getMes() <<"-"<<this->fechaActual().getAnio() <<endl;
		printf("==========================================\n");
		printf("Bienvenido al sistema electronico de votos\n");
		printf("==========================================\n\n");

		printf("\t1. Votante\n");
		printf("\t2. Administrador\n");
		printf("\t3. Salir\n\n");
		printf("\tIngrese una opcion: ");
		opcion=getchar();
		printf("\n\n");
		cout << endl << endl;
		switch (opcion) {
			case '1':

				//menu votante
				MenuVotante();
				break;
			case '2':

				//menu admin
				MenuAdmin();
				break;
			case '3':
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
char opcion;

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
		opcion=getchar();

		switch (opcion) {
				case '1':{

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
				case '2':	{
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
										cout << endl;
										if (op=="q") MenuAdmin();
										}

							}
							delete abmAdmin;
						break;
				}
				case '3':{
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

				case '4':
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
				case '5':
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
	char opcion;
	bool autenticado=false;	//para que no tenga que loguearse siempre

	ABMVotante *votantes = new ABMVotante();

	while (fin==0){
			system("clear");
			cout << endl << endl<< endl;
			printf("=======\n");
			printf("VOTANTE\n");
			printf("=======\n\n");
			printf("\t1. Ingresar al sistema\n");
			printf("\t2. Volver al menu principal\n\n");
			printf("\tIngrese una opcion: ");
			opcion=getchar();

			switch (opcion) {
							case '1':
								{
								if (!autenticado){
									//ABMVotante votantes = ABMVotante();

									printf("\n\n");
									printf("\tIngrese DNI: ");
									cin >> dni;

										if (votantes->existKey(dni)){
											Votante* votante = votantes->GetVotante(dni);

											printf("\tIngrese password: ");
											cin >> pass;

											if (votante->Authenticate(pass)){
												autenticado=true;

												VotanteLog::LogSuccess(Helper::LongToString(dni));
												Menu_EleccionesXDistrito_votante(votante);
											}
											else{
												printf("Password Incorreca\n");
												VotanteLog::LogPasswordInvalid(Helper::LongToString(dni));
												cin >> c;

											}
										}
										else{
											printf("No existe el usuario ingresado, presione ua tecla para continuar. \n\n\n");
											VotanteLog::LogUserInvalid(Helper::LongToString(dni));
											cin >> c;

										}
								}
								else{
									Votante* votante = votantes->GetVotante(dni);
									Menu_EleccionesXDistrito_votante(votante);
								}

								}
								break;
							case '2':
								fin=1;
								//this->MenuPpal();	//menu admin
								break;
							default:
								fin=0;
								break;

					}
			}

	delete votantes;
}

///FALTAN METODOS PARA QUE FUNCIONE
void Menues::Menu_EleccionesXDistrito_votante(Votante* votante)
{
	ABMEleccion es = ABMEleccion();
	ABMConteo cs = ABMConteo();

	system("clear");
	cout << endl << endl;
	cout << "Bienvenido " << votante->GetNombreYApellido() << ", usted pertenece al distrito: " << votante->GetDistrito() << endl;

	bool listoEleccion = false;

	Fecha fecha = this->fechaActual();

	vector<Eleccion*> elecciones = es.GetByFecha(&fecha);

	if (elecciones.size()==0){
		cout <<endl;
		cout << "Usted no tiene elecciones en el dia de la fecha." << endl;
		cout << "Presione cualquier tecla para salir ";
		string c;
		cin >> c;
		listoEleccion=true;
	}
	while(!listoEleccion){
		cout << "Usted puede votar en las siguientes elecciones: " << endl;

		//Le muestro las elecciones que no esten en su lista de elecciones ya votadas
		ABMCargo* cargos = new ABMCargo();
		for(unsigned int i = 0; i < elecciones.size(); i++){

			if(!votante->VotoEnEleccion(elecciones[i])){
				cout << " Cargo: " << cargos->GetCargo(elecciones[i]->GetIdCargo())->GetNombre() <<"(" << elecciones[i]->GetIdCargo() << ")" << endl;
			}
		}

		delete cargos;

		string idCargoSeleted;
		cout << "Ingrese la eleccion en la cual quiera votar (seleccione un número de arriba): ";
		cin >> idCargoSeleted;

		int idCargo = Helper::StringToInt(idCargoSeleted);

		//ME quedo con la que quiere votar. Busco las

		Eleccion* e = elecciones[0];

		bool founded = false;
		for(unsigned int i = 0; i < elecciones.size() && (!founded); i++){
			if(elecciones[i]->GetIdCargo() == idCargo){
				e = elecciones[i];
				founded = true;
			}
		}

		if(founded){

			vector<Conteo> conteos = cs.GetConteoByEleccion(e->GetId());
			bool listoLista=false;

			for(unsigned int i = 0; i < conteos.size(); i++){
				cout << "Lista " << conteos[i].GetIdLista() << endl;
			}


			while (!listoLista){

					int idConteoLista;
					string idLista;
					string idListaAnterior; //en caso de que cambie el voto
					bool cambioVoto=false;

					cout << "Ingrese lista a votar: ";
					cin >> idLista;


					bool listaFounded = false;;
					for(unsigned int i = 0; (i < conteos.size()) && (!listaFounded); i++){

						if(conteos[i].GetIdLista() == idLista) {
							listaFounded = true;
							idConteoLista=conteos[i].GetId(); //obtengo el id de conteo para usar en el ADD
						}

					}

					if(!listaFounded){
						cout << "Lista incorrecta, presione una tecla para reintentar o [q] para salir: ";
						string op;
						cin >> op;
						if (op=="q") {
							listoEleccion=true;
							listoLista=true;
						}
					}
					else{
						cout << "Esta seguro de votar la lista " << idLista << "? . [s]=Confirma u otra para cambiar voto.";
						string op;
						cin >> op;
						if (op=="s"){

							//logueo en caso de que haya cambiado voto
							if (idLista==idListaAnterior && cambioVoto){
								VotanteLog::LogChangeVoto(Helper::LongToString(votante->GetDni()),idLista,idListaAnterior);

							}

							cs.AddVoto(idConteoLista, votante); //debe hacerse una confirmacion aun
							listoEleccion=true;
							listoLista=true;
							VotanteLog::LogVoto(Helper::LongToString(votante->GetDni()),idLista);
							cout << "Votacion realizada con exito, presione una tecla para volver al menu";
							cin >> op;
						}
						else{
							cambioVoto=true;
							idListaAnterior=idLista;
						}
					}
			}
		}
		else{
			cout << "Eleccion inválida, presione una tecla para reintentar o [q] para salir: ";
			string op;
			cin >> op;
			if (op=="q") listoEleccion=true;
		}
	}

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
char opcion;

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
		cin >> opcion;

		switch (opcion) {
					case '1':	{
								system("clear");
								bool listo=false;
								ABMDistrito *dis = new ABMDistrito();

								cout << "ALTA DISTRITO" << endl;
								cout << "-------------" << endl << endl;

								while (!listo){
									string nombre;
									string input;
									cout << "Ingrese nombre de Distrito: ";
									cin >> nombre;

									int ok = dis->Add(nombre);
									if (ok!=-1){
										cout << "Distrito agregado con ID: " << ok << endl << endl;
										cin >> input;
										listo = true;
									}
									else{
										cout << "Ya existe el distrito ingresado, presione una tecla para reintentar o [q] para volver";
										cin >> input;
										if (input=="q") listo=true;
									}
								}
								delete dis;

								break;
							}
					case '2':	{
								system("clear");
								bool listo=false;
								while (!listo){
									int id;
									string input;
									cout << "BAJA DISTRITO" << endl;
									cout << "-------------" << endl << endl;
									cout << "Ingrese ID del distrito: ";
									cin >> id;
									ABMDistrito *dis = new ABMDistrito();

									if (dis->Delete(id)){
										cout << "Se elimino distrito" << endl << endl;
										cin >> input;
										listo = true;
									}
									else
									{
										cout << "No existe distrito ingresado, presione una tecla para reintentar o [q] para volver" << endl << endl;
										cin >> input;
										if (input=="q") listo=true;
									}

									delete dis;
								}
								break;
							}
					case '3':
							{
								system("clear");
								bool listo=false;
								while (!listo){
									int id;
									string nombre;
									string input;
									cout << "MODIFICACION DISTRITO" << endl;
									cout << "---------------------" << endl << endl;
									cout << "Ingrese ID del distrito: ";
									cin >> id;
									cout << "Ingrese nuevo nombre de distrito: ";
									cin >> nombre;

									ABMDistrito *dis = new ABMDistrito();
									Distrito *disModifica = dis->GetDistrito(id);

									if (disModifica != NULL){
										disModifica->SetNombre(nombre);

										dis->Modify(disModifica);

										cout << "Se modifico distrito" << endl << endl;
										cin >> input;
										listo = true;

									}
									else
									{
										cout << "No existe distrito, presione una tecla para reintentar o [q] para volver" << endl << endl;
										cin >> input;
										if (input=="q") listo=true;
									}

									delete disModifica;
									delete dis;
								}
								break;
							}
					case '4':
							{
								fin=1;
								break;
							}
					default:
							{
								fin=0;
								break;
							}
					}
		}
}

void Menues::MenuABMLista()
{
	int fin=0;
	char opcion;

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
			cin >> opcion;
			cout << endl;
			switch (opcion) {
						case '1':	{
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
									int eleccion;
									bool listo2=false;
									while (!listo2){
										cout << "Ingrese el ID_Eleccion asociada a la Lista: ";
										cin >> eleccion;
										cout << endl;
										if (abmEleccion->ExistsKey(eleccion)) {
											Lista *lista = new Lista(nombre,eleccion);
											abmLista->Add(lista);
											listo2=true;
											cout << "Lista " << nombre <<" creada con exito, presione una tecla para volver al menu.";
											string c;
											cin >> c;
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

						string c;
						cin >> c;
						if (c=="q") listo=true;

						delete abmLista;

						break;

						}
						case '2':{
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
						case '3':{
								//falta esto solo
								break;
								}
						case '4':{
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
	int fin=0;
	char opcion;

	while (fin==0){
		system("clear");
		printf("=========\n");
		printf("ABM CARGO\n");
		printf("=========\n\n");
		printf("\t1. Alta Cargo \n");
		printf("\t2. Baja Cargo \n");
		printf("\t3. Modificacion Cargo\n");
		printf("\t4. Volver\n\n");
		printf("\tIngrese una opcion: ");
		cin >> opcion;
		cout << endl;

		switch (opcion) {
					case '1':	{
						bool listo=false;
						ABMCargo *abmCargo = new ABMCargo();
						system("clear");
						printf("ALTA CARGO\n");
						printf("----------\n\n");

						while (!listo){
							string nombre;
							cout << "Ingrese nombre del cargo principal: ";
							cin >> nombre;
							cout << endl;

							vector<Cargo> vCargos = abmCargo->GetCargos();
							bool existe=false;

							for (unsigned int i=0;(i<vCargos.size() && (!existe));i++){

								if (vCargos.at(i).GetNombre()==nombre){
									existe=true;
								}
							}

							if (!existe){
								bool listo2=false;
								vector<int> vecCargosSec;

								while (!listo2){
									cout << "Desea ingresar cargo secundario? presione [s] u otra para terminar: ";
									string op;
									cin >> op;
									if (op=="s"){
										string sec;
										cout << "Ingrese nombre del cargo secundario: ";
										cin >> sec;
										cout << endl;
										bool existeSec=false;
										int idSec;
										for (unsigned int i=0;(i<vCargos.size() && (!existeSec));i++){

											if (vCargos.at(i).GetNombre()==sec){
											existeSec=true;
											idSec = vCargos.at(i).GetId();
											}

										}
										if (existeSec){
											vecCargosSec.push_back(idSec);
										}
										else{
											cout << "No existe el cargo secundario ingresado, ingrese [q] para salir u otra para reintentar: ";
											string op;
											cin >> op;
											if (op=="q") {
												listo2=true;
												listo=true;
											}
										}

									}
									else{
										//hay que chequear el add que me parece que no funciona bien
										abmCargo->Add(nombre,vecCargosSec);
										listo2=true;
										listo=true;
									}
								}
							}
							else{
								cout << "Ya existe el cargo ingresado, ingrese [q] para salir u otra para reintentar: ";
								string op;
								cin >> op;
								if (op=="q") listo=true;
							}


						}
						//delete abmCargo;
						break;

						}
					case '2':{
						break;
					}
					case '3':{
						break;
					}
					case '4':{
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

void Menues::MenuABMCandidato()
{
	int fin=0;
	char opcion;

	while (fin==0){
		system("clear");
		printf("=============\n");
		printf("ABM CANDIDATO\n");
		printf("=============\n\n");
		printf("\t1. Alta Candidato \n");
		printf("\t2. Baja Candidato \n");
		printf("\t3. Modificacion Candidato\n");
		printf("\t4. Volver\n\n");
		printf("\tIngrese una opcion: ");
		cin >> opcion;
		cout << endl;
		//Candidato (((lista)ie, (votante)ie, (cargo)ie)i): Hash
		switch (opcion) {
					case '1':	{
						bool listo=false;
						ABMCandidato *abm = new ABMCandidato();
						system("clear");
						printf("ALTA CANDIDATO\n");
						printf("----------\n\n");

						while (!listo){
							long dni;
							cout << "Ingrese DNI del candidato (debe existir como votante): ";
							cin >> dni;
							cout << endl;

							ABMVotante *abmVot = new ABMVotante();

							if (abmVot->existKey(dni)){
								//existe dni, ahora pregunto por la lista

								ABMLista *abmLista = new ABMLista();
								bool listoLista=false;

								while (!listoLista){
									string lista;
									cout << "Ingrese nombre de lista a pertenecer: ";
									cin >> lista;
									cout << endl;

									if (abmLista->existKey(lista)){
										//existe lista ahora pregunto por cargo

										//antes obtengo eleccion asociada la lista
										int id_eleccion = abmLista->GetLista(lista)->GetEleccion();

										ABMEleccion *abmEleccion = new ABMEleccion();
										//obtengo cargo principal asociada a la eleccion
										int id_cargo = abmEleccion->GetEleccion(id_eleccion)->GetIdCargo();

										ABMCargo *abmCargo = new ABMCargo();
										// obtengo los cargos secundarios
										vector<int>	vCargos = abmCargo->GetCargo(id_cargo)->GetCargosSecundarios();

										bool listoCargo=false;

										while (!listoCargo){
											int id;
											cout << "Ingrese IdCargo a postularse: ";
											cin >> id;
											cout << endl;

											bool valido=false;
											if (abmCargo->Exists(id)){
												//me fijo si el id es del cargo ppal
												if (id_cargo==id) valido=true;
												//busco en los cargos secundarios
												for (int i=0;i<vCargos.size() && !valido;i++){
													if (vCargos.at(i)==id){
														valido=true;
													}
												}

												//si el cargo es valido entonces creo el candidato
												if (valido){
													int ok = abm->Add(lista,dni,id);
													if (ok!=-1){
														cout<< endl;
														cout << "Candidato creado exitosamente, presione una tecla para volver.";
														string op;
														cin >> op;
														listo=true;
														listoCargo=true;
														listoLista=true;
													}
													else{
														cout<< endl;
														cout << "Candidato existente, presione una tecla para volver al menu.";
														string op;
														cin >> op;
														listo=true;
														listoCargo=true;
														listoLista=true;
													}
												}

											}
											else{
												cout << "No existe Idcargo ingresado, presione una tecla para reintentar o [q] para salir: ";
												string op;
												cin >> op;
												if (op=="q") {
													listoLista=true;
													listo=true;
													listoCargo=true;
												}
											}

										}
										delete abmCargo;
										delete abmEleccion;
									}
									else{
										cout << "No existe lista ingresada, presione una tecla para reintentar o [q] para salir: ";
										string op;
										cin >> op;
										if (op=="q") {
											listoLista=true;
											listo=true;
										}
									}
								}
								delete abmLista;
							}
							else{
								cout << "No existe DNI ingresado, presione una tecla para reintentar o [q] para salir: ";
								string op;
								cin >> op;
								if (op=="q") listo=true;
							}

							delete abmVot;
						}
						delete abm;
						break;

						}
					case '2':{
						break;
					}
					case '3':{
						break;
					}
					case '4':{
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

void Menues::Reportes()
{
int fin=0;
char opcion;

while (fin==0){
	system("clear");
	printf("========\n");
	printf("REPORTES\n");
	printf("========\n\n");
	printf("\t1. Reporte por Eleccion \n");
	printf("\t2. Reporte por Lista\n");
	printf("\t3. Reporte por Distrito\n");
	printf("\t4. Volver\n\n");
	printf("\tIngrese una opcion: ");
	cin >>opcion;
	cout << endl;

	switch (opcion) {
				case '1':	{

					cout << "Reporte por Eleccion" << endl << endl;
					cout << "Ingrese Fecha de la eleccion. " << endl;
					string anio;
					string mes;
					string dia;
					string idCargo;

					cout << "Anio: ";
					cin >> anio;
					cout << "Mes: ";
					cin >> mes;
					cout << "Dia: ";
					cin >> dia;

					Fecha* fecha = new Fecha(Helper::StringToInt(dia), Helper::StringToInt(mes),Helper::StringToInt(anio));

					ABMCargo* abmCargos = new ABMCargo();
					vector<Cargo> cargos = abmCargos->GetCargos();

					cout << "Cargos: " << endl;
					for(int i = 0; i < cargos.size(); i++){
						cout << cargos[i].GetNombre() << " - Id: " << cargos[i].GetId() << endl;
					}

					cout << "Ingrese Id de Cargo:";
					cin >> idCargo;

					string cargoSelected;
					bool founded = false;
					for(int i = 0; i < cargos.size() && !founded; i++){

						if(cargos[i].GetId() == Helper::StringToInt(idCargo)){
							cargoSelected = cargos[i].GetNombre();
							founded = true;
						}
					}

					delete abmCargos;

					if(founded){
						ABMEleccion* abmEleccion = new ABMEleccion();
						vector<Eleccion*> elecciones = abmEleccion->GetByFechaYCargo(fecha, Helper::StringToInt(idCargo));

						delete abmEleccion;

						if(elecciones.size() > 0 && elecciones[0] != NULL){
							Reportes::reportePorEleccion(elecciones[0]->GetId());
						}
						else{
							cout << endl << "No se encontro la eleccion para la Fecha y el Cargo indicado" << endl;
						}
					}
					else{
						cout << endl << "No se encontro la eleccion para la Fecha y el Cargo indicado" << endl;
					}

					cout << endl <<  "Presione cualquier tecla para continuar" << endl;
					string c;
					cin >> c;
					//if (c=="q") listo=true;

					break;

				}
				case '2':{

					cout << "Reporte por Lista" << endl << endl;

					ABMLista* abmLista = new ABMLista();

					cout << "Listas disponibles:" << endl;
					vector<Lista> listas = abmLista->GetListas();
					for(int i = 0; i < listas.size(); i++){
						cout << listas[i].GetNombre() << endl;
					}

					cout << "Ingrese la lista: " << endl;
					string listaSelected;
					cin >> listaSelected;

					//Busco la lista seleccionada
					bool founded = false;
					for(int i = 0; i < listas.size(); i++){
						if(listas[i].GetNombre() == listaSelected)
							founded = true;
					}

					delete abmLista;
					if(founded){
						Reportes::reportePorLista(listaSelected);
					}
					else{
						cout << "La Lista ingresada es incorrecta." << endl;
					}


					cout << endl <<  "Presione cualquier tecla para continuar" << endl;
					string c;
					cin >> c;
					//if (c=="q") listo=true;

					break;
				}
				case '3':{

					cout << "Reporte por Distrito" << endl << endl;

					ABMDistrito* abmDistrito = new ABMDistrito();

					cout << "Distritos disponibles:" << endl;
					vector<Distrito> distritos = abmDistrito->GetDistritos();

					for(int i = 0; i < distritos.size(); i++){
						cout << distritos[i].GetNombre() << endl;
					}

					cout << "Ingrese el Distrito: " << endl;
					string distritoSelected;
					cin >> distritoSelected;

					//Busco la lista seleccionada
					bool founded = false;
					int idDistrito = 0;
					for(int i = 0; i < distritos.size(); i++){
						if(distritos[i].GetNombre() == distritoSelected)
							founded = true;
					}

					delete abmDistrito;

					if(founded){
						Reportes::reportePorDistrito(idDistrito);
					}
					else{
						cout << "La Lista ingresada es incorrecta." << endl;
					}


					cout << endl <<  "Presione cualquier tecla para continuar" << endl;
					string c;
					cin >> c;
					//if (c=="q") listo=true;

					break;
				}

				default:{
					fin=0;
					break;
				}
	}
}

}

void Menues::MenuABMVotante()
{
int fin=0;
char opcion=1;

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
		cin >> opcion;

		switch (opcion) {

					case '1':	{
						bool listo=false;
						ABMVotante *vot = new ABMVotante();
						Votante* votante;

						while (!listo){
							string dni;
							system("clear");
							printf("ALTA VOTANTE\n");
							printf("------------\n\n");

							cout << "Ingrese DNI del usuario: ";
							cin >> dni;

							if (!vot->existKey(Helper::StringToLong(dni))){

								votante = EditaVotante(dni);

								if (votante != NULL)
								{

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
					case '2':	{
							bool listo=false;
							ABMVotante *vot = new ABMVotante();
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
					case '3':
							{
								bool listo=false;
								ABMVotante *vot = new ABMVotante();
								Votante* votante;

								while (!listo){
									string dni;
									system("clear");
									printf("MODIFICACION VOTANTE\n");
									printf("--------------------\n\n");

									cout << "Ingrese DNI del usuario: ";
									cin >> dni;

									if (vot->existKey(Helper::StringToLong(dni))){

										votante = EditaVotante(dni);

										if (votante != NULL)
										{

											vot->Modify(votante);
											delete votante;
											listo=true;
											cout << endl << endl;
											cout << "votante modificado satisfactoriamente.";
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
										cout << "No existe el DNI ingresado, presione una tecla para reintentar o [q] para volver";
										cin >> dni;
										if (dni=="q") listo=true;
									}
								}
								delete vot;
								break;
							}
					case '4':
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

Votante* Menues::EditaVotante(string dni)
{
	Votante *votante = NULL;
	string _nombreYApellido;
	string _clave;
	string _domicilio;

	cout << "Ingrese Nombre y Apellido: ";
	cin >> _nombreYApellido;
	cout << endl;

	cout << "Ingrese domicilio: ";
	cin >> _domicilio;
	cout << endl;

	cout << "Ingrese clave:";
	cin>>_clave;
	cout << endl;

	string distrito;
	int id_distrito;
	cout << "Ingrese IdDistrito: ";
	cin >> distrito;
	id_distrito = Helper::StringToInt(distrito);

	ABMDistrito *dis = new ABMDistrito();
	if (dis->Exists(id_distrito)){
		votante = new Votante(Helper::StringToLong(dni),_nombreYApellido,_clave,_domicilio,id_distrito);
	}

	return votante;
}

void Menues::MenuABMEleccion()
{
	int fin=0;
	char opcion;

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
			cin >>opcion;

			switch (opcion) {
						case '1':	{
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


									//busco si existe el nombre
									ABMCargo *abmCargo = new ABMCargo();

									cout << "Cargos disponibles: " << endl;
									vector<Cargo> vecCargos = abmCargo->GetCargos();

									for (unsigned int i=0;i<vecCargos.size();i++){
										cout << "Cargo: " << vecCargos.at(i).GetNombre() << endl;
									}

									cout << endl;
									cout << "Ingrese nombre cargo principal: ";
									cin >> nombre;

									bool existNombre=false;

									for (unsigned int i=0;((i<vecCargos.size()) && (!existNombre));i++){
										if ((vecCargos.at(i).GetNombre()) == nombre){
											existNombre=true;
											idCargo= vecCargos.at(i).GetId();
										}
									}
									delete abmCargo;

									if (!existNombre){
										cout << endl << endl;
										cout << "El cargo no existe, presione una tecla para reintentar o [q] para volver";
										string op;
										cin >> op;
										if (op=="q") {
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
											ABMDistrito *dis = new ABMDistrito();
											vector<int> distritos;

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
														distritos.push_back(id_distrito);
														cout << "Id distrito "<< id_distrito << " cargado con exito" << endl;

														}
													else {
														cout << "No existe el IdDistrito " << id_distrito << " , presione una tecla para reintentar o [q] para terminar";
														string c;
														cin >> c;
														if (c=="q") {
															finCargaDistrito=true;
															listo2=true;
															listo=true;

														}

														}
												}
												else {
													//termine de cargar la eleccion, vuelvo al menu
													finCargaDistrito=true;
													listo2=true;
													listo=true;

												}
											}//fin de carga de distritos

										delete dis;

										//guardo eleccion
										for (int i=0;i<distritos.size();i++){
											eleccion->AddDistrito(distritos[i]);
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
											listo2=true;
										}
										delete eleccion;
									}

								}
							}



							delete el;
							break;
								}
						case '2':	{
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
						case '3':
								{
									//FALTA SOLO ESTE CASO
									break;
								}
						case '4':
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

Fecha Menues::fechaActual()
{
	time_t tSac =time(NULL);
	tm tms = *localtime(&tSac);

	Fecha fecha = Fecha((short)tms.tm_mday, (short)tms.tm_mon+1, (short)tms.tm_year+1900);

	return fecha;

}









