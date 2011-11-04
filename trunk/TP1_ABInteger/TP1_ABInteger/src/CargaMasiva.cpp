/*
 * CargaMasiva.cpp
 *
 *  Created on: 01/11/2011
 *      Author: loo
 */

#define MAX_ID_TEST 3

#include "CargaMasiva.h"

vector<int> CargaMasiva::GetIdsConteos(vector<Conteo> cs){

	vector<int> ids;
	for(int i = 0; i < cs.size(); i++){
		ids.push_back(cs[i].GetId());
	}

	return ids;
}

int CargaMasiva::GetRandom(int maxNumber){

    srand((unsigned)time(0));
    int random_integer;

    random_integer = (rand() % maxNumber) + 1;
    return random_integer;
}

int CargaMasiva::GetRandomFromNumbers(vector<int> posibleNumbers){

	if(posibleNumbers.size() == 0)
		return NULL;

	if(posibleNumbers.size() == 1)
		return posibleNumbers[0];

	return posibleNumbers[GetRandom(posibleNumbers.size() - 1)];
}

void CargaMasiva::CargarDistritos(){

	//Borro el archivo de distrito
	string archivo = ConfigurationMananger::getInstance()->getDistritoFile();
	archivo = "rm " + archivo;
	system(archivo.c_str());
	archivo = archivo + ".fs";
	system(archivo.c_str());

	//Cargo CANT_Distrito distritos
	ABMDistrito abmDistrito = ABMDistrito();

    for(int i = 1; i <= CANT_DISTRITOS; i++){
            string distrito = "Distrito ";
            distrito.append(Helper::IntToString(i));
            abmDistrito.Add(distrito);
    }
}


void CargaMasiva::CargarVotantes(){

	//Borro el archivo de votantes
	string archivo = ConfigurationMananger::getInstance()->getVotanteFile();
	string archivobk = "rm " + archivo + ".bk";
	system(archivobk.c_str());
	archivobk = archivobk + ".fs";
	system(archivobk.c_str());
	string archivodir = "rm " + archivo + ".dir";
	system(archivodir.c_str());
	archivodir = archivodir + ".fs";
	system(archivodir.c_str());

	//Cargo CANT_VOTANTES votantes
	ABMVotante abmVotante = ABMVotante();

    for(int i = 1; i <= CANT_VOTANTES; i++){

			string nombreApellido = "Nombre Apellido ";
			nombreApellido = nombreApellido.append(Helper::IntToString(i));

			string clave = "Clave";
			clave.append(Helper::IntToString(i));

			string domicilio = "Domicilio ";
			domicilio.append(Helper::IntToString(i));

			long dni = (long)GetRandom(99999) * 1000;

			int idDistrito = GetRandom(CANT_DISTRITOS);

			Votante  * vot = new Votante(dni, nombreApellido, clave, domicilio, idDistrito);
            abmVotante.Add(vot);
    }
}

void CargaMasiva::CargarCargos(){

	//Borro el archivo de cargos
	string archivo = ConfigurationMananger::getInstance()->getCargoFile();
	string archivobk = "rm " + archivo + ".bk";
	system(archivobk.c_str());
	archivobk = archivobk + ".fs";
	system(archivobk.c_str());
	string archivodir = "rm " + archivo + ".dir";
	system(archivodir.c_str());
	archivodir = archivodir + ".fs";
	system(archivodir.c_str());

	//Cargo CANT_CARGOS cargos
	ABMCargo abmCargo = ABMCargo();

    for(int i = 1; i <= CANT_CARGOS; i++){
			string cargo = "Cargo ";
			cargo.append(Helper::IntToString(i));
			vector<int> cargosSecundarios;
			if (i>1) cargosSecundarios.push_back(GetRandom(i-1));

            abmCargo.Add(cargo, cargosSecundarios);
    }
}


void CargaMasiva::CargarElecciones(){

	//Borro el archivo de elecciones
	string archivo = ConfigurationMananger::getInstance()->getEleccionFile();
	archivo = "rm " + archivo;
	system(archivo.c_str());
	archivo = archivo + ".fs";
	system(archivo.c_str());

	//Cargo CANT_ELECCIONES elecciones
	ABMEleccion abmEleccion = ABMEleccion();

	for(int i = 1; i <= CANT_ELECCIONES; i++){

			Fecha fecha = Fecha(1, 1, 1000+i);

			int idCargo = GetRandom(CANT_CARGOS);

			Eleccion  * ele = new Eleccion(idCargo, fecha);
            abmEleccion.Add(ele);
    }
}

void CargaMasiva::CargarListas(){
	//Borro el archivo de listas
	string archivo = ConfigurationMananger::getInstance()->getListaFile();
	string archivobk = "rm " + archivo + ".bk";
	system(archivobk.c_str());
	archivobk = archivobk + ".fs";
	system(archivobk.c_str());
	string archivodir = "rm " + archivo + ".dir";
	system(archivodir.c_str());
	archivodir = archivodir + ".fs";
	system(archivodir.c_str());

	//Cargo CANT_LISTAS listas
	ABMLista abmLista = ABMLista();

    for(int i = 1; i <= CANT_LISTAS; i++){
			string lista = "Lista ";
			lista.append(Helper::IntToString(i));

			int idEleccion = GetRandom(CANT_ELECCIONES);

			Lista * lis = new Lista(lista, idEleccion);
            abmLista.Add(lis);
    }
}

void CargaMasiva::CargarCandidatos(){
	//Borro el archivo de candidatos
	string archivo = ConfigurationMananger::getInstance()->getCandidatoFile();
	string archivobk = "rm " + archivo + ".bk";
	system(archivobk.c_str());
	archivobk = archivobk + ".fs";
	system(archivobk.c_str());
	string archivodir = "rm " + archivo + ".dir";
	system(archivodir.c_str());
	archivodir = archivodir + ".fs";
	system(archivodir.c_str());

	//Cargo CANT_CANDIDATOS cargos
	ABMCandidato abmCandidato = ABMCandidato();

    for(int i = 1; i <= CANT_CANDIDATOS; i++){
			string idLista = Helper::IntToString(GetRandom(CANT_LISTAS));
			long int idVotante = (long int) GetRandom(CANT_VOTANTES);
			int idCargo = (int) GetRandom(CANT_CARGOS);
            abmCandidato.Add(idLista, idVotante, idCargo);
    }
}

void CargaMasiva::CargarAdministradores(){

	//Borro el archivo de administradores
	string archivo = ConfigurationMananger::getInstance()->getAdminFile();
	string archivobk = "rm " + archivo + ".bk";
	system(archivobk.c_str());
	archivobk = archivobk + ".fs";
	system(archivobk.c_str());
	string archivodir = "rm " + archivo + ".dir";
	system(archivodir.c_str());
	archivodir = archivodir + ".fs";
	system(archivodir.c_str());

	//Cargo CANT_ADMINISTRADORES administradores
	ABMAdministrador abmAdministrador = ABMAdministrador();

    for(int i = 1; i <= CANT_ADMINISTRADORES; i++){
			string admin = "Admin";
			admin.append(Helper::IntToString(i));
			Administrador  * adm = new Administrador(admin,admin);
            abmAdministrador.Add(adm);
    }
}

//Carga todas las entidades
void CargaMasiva::CargarEntidades(){
	//Inicializo los ids en 1
	Identities::InitializeFile();
	//Carga masiva de todas las entidades
	CargarDistritos();
	CargarVotantes();
	CargarCargos();
	CargarElecciones();
	CargarListas();
	CargarCandidatos();
	CargarAdministradores();
}


void CargaMasiva::GenerarVotosAutomaticos(){

	ABMVotante* vots = new ABMVotante();
	ABMEleccion* elecc = new ABMEleccion();
	ABMConteo* cont = new ABMConteo();

	//Recorro todos los votantes
	for(int idV = 1 ; idV <= 100; idV++) {

		Votante* votante = vots->GetVotante(idV);

		if(votante != NULL){

			//Recorro todas las elecciones t me fijo en cual le corresponde votar --> Si el distrito del votante esta en la eleccion
			for (int i = 1; i <= MAX_ID_TEST; i++) {

				Eleccion* e = elecc->GetEleccion(i);
				vector<int> ds = e->GetDistritos();
				for(int j = 0; j < ds.size(); j++){

					if(ds[j] == votante->GetDistrito()){

						//Busco las listas de esta eleccion en los registros de conteo
						vector<Conteo> cs = cont->GetConteoByEleccion(i);

						vector<int> posiblesConteos = CargaMasiva::GetIdsConteos(cs);

						//cout << "El Votante" <<  idV << " pertenece al distrito " << votante->GetDistrito() << ", va a votar en la eleccion " << e->GetDate().getStrFecha() << " - Cargo " << e->GetIdCargo() << endl;

						//Elijo al azar una lista
						int idConteo = CargaMasiva::GetRandomFromNumbers(posiblesConteos);
						//cout << endl << endl << "idConteo: " << idConteo << endl << endl << endl;

						cout << endl << endl ;
						cont->AddVoto(idConteo, votante);

					}
				}
			}
		}
	}
}
