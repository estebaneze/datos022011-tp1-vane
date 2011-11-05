/*
 * CargaMasiva.cpp
 *
 *  Created on: 01/11/2011
 *      Author: loo
 */

#include "CargaMasiva.h"

vector<int> CargaMasiva::GetIdsConteos(vector<Conteo> cs){

	vector<int> ids;
	for(int i = 0; i < cs.size(); i++){
		ids.push_back(cs[i].GetId());
	}

	return ids;
}

int CargaMasiva::GetRandom(int maxNumber){

    return (rand() % maxNumber) + 1;
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
		int idDistrito =  abmDistrito.Add(distrito);

        //cout << "Distrito (" << idDistrito << "): " << distrito << endl;
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

            //  cout << "Votante " << vot->GetDni() << endl;
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

			int idCargo = abmCargo.Add(cargo, cargosSecundarios);

			//cout << "Cargo (" << idCargo << "): " << cargo << endl;
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

		if(CANT_DISTRITOS / 10 < 1){

			//Agrego un solo distrito a la elccion
			ele->AddDistrito(GetRandom(CANT_DISTRITOS));
		}
		else{

			//Agrego CANT_DISTRITOS/10 distritos a la eleccion
			vector<int> distritosAgregados;

			for(int i = 0; i < CANT_DISTRITOS/10; i++){

				int idDistrito;
				if(distritosAgregados.size() == 0){
					idDistrito = GetRandom(CANT_DISTRITOS);
					ele->AddDistrito(idDistrito);
				}
				else{

					//Me fijo que el id distrito no se haya ya agregado a la eleccion
					bool founded = true;

					while(founded){

						idDistrito = GetRandom(CANT_DISTRITOS);
						vector<int>::iterator it;
						it = find(distritosAgregados.begin(), distritosAgregados.end(), idDistrito);

						if(it != distritosAgregados.end()){	//no esta ya agregado
							ele->AddDistrito(idDistrito);
							founded = false;
						}

					}
				}

				distritosAgregados.push_back(idDistrito);
			}
		}

        int idEleccion = abmEleccion.Add(ele);

        //cout << "Eleccion(" << idEleccion << "). Fecha:  " << fecha.getFriendlyStr() << ". Cargo: " << ele->GetIdCargo() << endl;
    }
/*
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
*/

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

		cout << "Lista: " << lis->GetNombre() << endl;
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
            int idCandidato = abmCandidato.Add(idLista, idVotante, idCargo);
            cout << "Candidato (" << idCandidato << "). Cargo" << idCargo << ". Lista: " << idLista << endl;
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

            cout << "Administrador. User: " << adm->GetUsuario() << ". Password: " << adm->GetClave() << endl;
    }

}

//Carga todas las entidades
void CargaMasiva::CargarEntidades(){

	//Inicializo los ids en 1
	Identities::InitializeFile();
	cout << endl;

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
	vector<Votante*> votantes = vots->GetVotantes();
	for(int k = 1 ; k < votantes.size(); k++) {

		Votante* votante = votantes[k];

		if(votante != NULL){

			//Recorro todas las elecciones t me fijo en cual le corresponde votar --> Si el distrito del votante esta en la eleccion
			for (int i = 1; i <= CANT_ELECCIONES; i++) {

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
