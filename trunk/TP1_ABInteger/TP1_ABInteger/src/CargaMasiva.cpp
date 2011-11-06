/*
 * CargaMasiva.cpp
 *
 *  Created on: 01/11/2011
 *      Author: loo
 */

#include "Persistencia/exceptions/excepciones.h"
#include "CargaMasiva.h"

void CargaMasiva::BorrarArchivosLog(){

	string scriptEliminaLog = "rm -r " + ConfigurationMananger::getInstance()->getLogDirectory() + "*.log";
	system(scriptEliminaLog.c_str());
}

void CargaMasiva::BorraTodosArchivos(){

	string scriptEliminaArchivos = "rm -r " + ConfigurationMananger::getInstance()->getFileDirectory() + "*.bk";
	system(scriptEliminaArchivos.c_str());

	scriptEliminaArchivos = "rm -r " + ConfigurationMananger::getInstance()->getFileDirectory() + "*.fs";
	system(scriptEliminaArchivos.c_str());

	scriptEliminaArchivos = "rm -r " + ConfigurationMananger::getInstance()->getFileDirectory() + "*.dir";
	system(scriptEliminaArchivos.c_str());

	scriptEliminaArchivos = "rm -r " + ConfigurationMananger::getInstance()->getFileDirectory() + "*.bpt";
	system(scriptEliminaArchivos.c_str());

	CargaMasiva::BorrarArchivosLog();
}

void CargaMasiva::BorrarArchivosIndice(string indexFile){

	string indexFileAux = "rm " + indexFile + ".ix.bk";
	system(indexFileAux.c_str());
	indexFileAux = "rm " + indexFile + ".ix.bk.fs";
	system(indexFileAux.c_str());
	indexFileAux = "rm " + indexFile + ".ix.dir";
	system(indexFileAux.c_str());
	indexFileAux = "rm " + indexFile + ".ix.dir.fs";
	system(indexFileAux.c_str());

}

void CargaMasiva::BorrarArchivos(){

	//------------------------------ Listas -------------------------------------------//
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


	//Borro el archivo de indices
	string indexFile = Helper::concatenar(ConfigurationMananger::getInstance()->getListaFile(),"Lista",ConfigurationMananger::getInstance()->getSeparador2());
	CargaMasiva::BorrarArchivosIndice(indexFile);

	//---------------------------------- Conteo --------------------------------//
	//Borro el archivo de conteo
	archivo = "rm " + ConfigurationMananger::getInstance()->getConteoFile() + ".bpt";
	system(archivo.c_str());
	archivo = "rm " + ConfigurationMananger::getInstance()->getConteoFile() + ".bpt" + ".fs";
	system(archivo.c_str());

	indexFile = Helper::concatenar(ConfigurationMananger::getInstance()->getConteoFile(),"Distrito",ConfigurationMananger::getInstance()->getSeparador2());
	CargaMasiva::BorrarArchivosIndice(indexFile);

	indexFile = Helper::concatenar(ConfigurationMananger::getInstance()->getConteoFile(),"Eleccion",ConfigurationMananger::getInstance()->getSeparador2());
	CargaMasiva::BorrarArchivosIndice(indexFile);

	indexFile = Helper::concatenar(ConfigurationMananger::getInstance()->getConteoFile(),"Lista",ConfigurationMananger::getInstance()->getSeparador2());
	CargaMasiva::BorrarArchivosIndice(indexFile);

	//---------------------------------- Distritos --------------------------------//
	//Borro el archivo de distrito
	archivo = "rm " + ConfigurationMananger::getInstance()->getDistritoFile();
	system(archivo.c_str());
	archivo = "rm " + ConfigurationMananger::getInstance()->getDistritoFile() + ".fs";
	system(archivo.c_str());

	//---------------------------------- Votantes--------------------------------//
	//Borro el archivo de votantes
	archivo = ConfigurationMananger::getInstance()->getVotanteFile();
	archivobk = "rm " + archivo + ".bk";
	system(archivobk.c_str());
	archivobk = archivobk + ".fs";
	system(archivobk.c_str());
	archivodir = "rm " + archivo + ".dir";
	system(archivodir.c_str());
	archivodir = archivodir + ".fs";
	system(archivodir.c_str());

	//---------------------------------- Cargos--------------------------------//
	//Borro el archivo de cargos
	archivo = ConfigurationMananger::getInstance()->getCargoFile();
	archivobk = "rm " + archivo + ".bk";
	system(archivobk.c_str());
	archivobk = archivobk + ".fs";
	system(archivobk.c_str());
	archivodir = "rm " + archivo + ".dir";
	system(archivodir.c_str());
	archivodir = archivodir + ".fs";
	system(archivodir.c_str());

	//---------------------------- Elecciones --------------------------------//
	//Borro el archivo de elecciones
	archivo = ConfigurationMananger::getInstance()->getEleccionFile();
	archivo = "rm " + archivo;
	system(archivo.c_str());
	archivo = archivo + ".fs";
	system(archivo.c_str());

	indexFile = Helper::concatenar(ConfigurationMananger::getInstance()->getEleccionFile(),"Fecha",ConfigurationMananger::getInstance()->getSeparador2());
	CargaMasiva::BorrarArchivosIndice(indexFile);

	indexFile = Helper::concatenar(ConfigurationMananger::getInstance()->getEleccionFile(),"Distrito",ConfigurationMananger::getInstance()->getSeparador2());
	CargaMasiva::BorrarArchivosIndice(indexFile);

	indexFile = Helper::concatenar(ConfigurationMananger::getInstance()->getEleccionFile(),"Cargo",ConfigurationMananger::getInstance()->getSeparador2());
	CargaMasiva::BorrarArchivosIndice(indexFile);


	//--------------------------- Candidatos -----------------------------------//
	//Borro el archivo de candidatos
	archivo = ConfigurationMananger::getInstance()->getCandidatoFile();
	archivobk = "rm " + archivo + ".bk";
	system(archivobk.c_str());
	archivobk = archivobk + ".fs";
	system(archivobk.c_str());
	archivodir = "rm " + archivo + ".dir";
	system(archivodir.c_str());
	archivodir = archivodir + ".fs";
	system(archivodir.c_str());

	//-------------------------- Admin -----------------------------------------//
	//Borro el archivo de administradores
	archivo = ConfigurationMananger::getInstance()->getAdminFile();
	archivobk = "rm " + archivo + ".bk";
	system(archivobk.c_str());
	archivobk = archivobk + ".fs";
	system(archivobk.c_str());
	archivodir = "rm " + archivo + ".dir";
	system(archivodir.c_str());
	archivodir = archivodir + ".fs";
	system(archivodir.c_str());


	//CargaMasiva::BorrarArchivosLog();
}

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

	//Cargo CANT_Distrito distritos
	ABMDistrito* abmDistrito = new ABMDistrito();

    for(int i = 1; i <= CANT_DISTRITOS; i++){

    	string distrito = "Distrito ";
		distrito.append(Helper::IntToString(i));
		int idDistrito =  abmDistrito->Add(distrito);

        cout << "Distrito (" << idDistrito << "): " << distrito << endl;
        Log::WriteLog("Distrito (" + Helper::IntToString(idDistrito) + "): " + distrito+ " ", "files/logs/cargaMasiva.log" );
    }

    delete abmDistrito;
}


void CargaMasiva::CargarVotantes(){

	//Cargo CANT_VOTANTES votantes
	ABMVotante* abmVotante = new ABMVotante();

    for(int i = 1; i <= CANT_VOTANTES; i++){

		string nombreApellido = "Nombre Apellido ";
		nombreApellido = nombreApellido.append(Helper::IntToString(i));

		string clave = "Clave";
		clave.append(Helper::IntToString(i));

		string domicilio = "Domicilio ";
		domicilio.append(Helper::IntToString(i));

		long dni = i;//(long)GetRandom(99999) * 1000;

		int idDistrito = GetRandom(CANT_DISTRITOS);

		Votante  * vot = new Votante(dni, nombreApellido, clave, domicilio, idDistrito);
		abmVotante->Add(vot);

		string strDni = Helper::LongToString(vot->GetDni());
		string pass = vot->GetClave();
		string strDistrito = Helper::IntToString(vot->GetDistrito());
		cout << "Votante " << strDni << ". Clave: "<< pass << ". Distrito: " << strDistrito << endl;
		Log::WriteLog("Votante: " + strDni + ". Clave: " + pass + " . Distrito: " + strDistrito + " ", "files/logs/cargaMasiva.log");
    }

    delete abmVotante;
}

void CargaMasiva::CargarCargos(){

	//Cargo CANT_CARGOS cargos
	ABMCargo* abmCargo = new ABMCargo();

    for(int i = 1; i <= CANT_CARGOS; i++){

    	string cargo = "Cargo";
		cargo.append(Helper::IntToString(i));
		vector<int> cargosSecundarios;
		if (i>1) cargosSecundarios.push_back(GetRandom(i-1));

		int idCargo = abmCargo->Add(cargo, cargosSecundarios);

		cout << "Cargo (" << idCargo << "): " << cargo << endl;
		Log::WriteLog("Cargo (" + Helper::IntToString(idCargo) + "): " + cargo+ " ", "files/logs/cargaMasiva.log");
    }

    delete abmCargo;
}

void CargaMasiva::CargarElecciones(){

	//Cargo CANT_ELECCIONES elecciones
	ABMEleccion* abmEleccion = new ABMEleccion();

	for(int i = 1; i <= CANT_ELECCIONES; i++){

		Fecha fecha = Fecha(GetRandom(30), GetRandom(12), 2006 + i);
		//Fecha fecha = Fecha(5+i, 11,2010+i);

		int idCargo = GetRandom(CANT_CARGOS);

		Eleccion  * ele = new Eleccion(idCargo, fecha);

		if(CANT_DISTRITOS / 20 < 1){
			//Agrego un solo distrito a la elccion
			ele->AddDistrito(GetRandom(CANT_DISTRITOS));
		}
		else{
			//Agrego CANT_DISTRITOS/20 distritos a la eleccion
			vector<int> distritosAgregados;

			for(int i = 0; i < CANT_DISTRITOS/20; i++){

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

						if(it == distritosAgregados.end()){	//no esta ya agregado
							ele->AddDistrito(idDistrito);
							founded = false;
						}

					}
				}

				distritosAgregados.push_back(idDistrito);
			}
		}

        int idEleccion = abmEleccion->Add(ele);

        cout << "Eleccion(" << idEleccion << "). Fecha:  " << fecha.getFriendlyStr() << ". Cargo: " << ele->GetIdCargo() << " ";
        cout << "Distritos: ";
        vector<int> ds = ele->GetDistritos();
        for(int i = 0; i<ds.size(); i++){
        	cout << ds[i] << " ";
        }
        cout << endl;

        string msg = "Eleccion(" + Helper::IntToString(idEleccion) + "). Fecha:  " + fecha.getFriendlyStr() + ". Cargo: " + Helper::IntToString(ele->GetIdCargo()) + " " + ". Distritos: ";
        for(int i = 0; i<ds.size(); i++){
        	msg = msg + Helper::IntToString(ds[i]) + " ";
        }
        Log::WriteLog(msg+ " ", "files/logs/cargaMasiva.log");
    }

	delete abmEleccion;
}

void CargaMasiva::CargarListas(){

	//Cargo CANT_LISTAS listas
	ABMLista* abmLista = new ABMLista();
	ABMEleccion* elec = new ABMEleccion();

    for(int i = 1; i <= CANT_LISTAS; i++){

    	string lista = "Lista";
		lista.append(Helper::IntToString(i));

		int idEleccion = GetRandom(CANT_ELECCIONES);

		Lista * lis = new Lista(lista, idEleccion);
		abmLista->Add(lis);

			string msg = "Lista(" + lis->GetNombre() + "): " + lis->GetNombre() + ". Eleccion: " + Helper::IntToString(lis->GetEleccion());
			cout << msg << endl;
			Log::WriteLog(msg+ " ", "files/logs/cargaMasiva.log");

    }

    delete elec;
    delete abmLista;
}


void CargaMasiva::CargarCandidatos(){

	//Cargo CANT_CANDIDATOS cargos
	ABMCandidato* abmCandidato = new ABMCandidato();

    for(int i = 1; i <= CANT_CANDIDATOS; i++){

		string idLista = Helper::IntToString(GetRandom(CANT_LISTAS));
		long int idVotante = (long int) GetRandom(CANT_VOTANTES);
		int idCargo = (int) GetRandom(CANT_CARGOS);
		int idCandidato = abmCandidato->Add(idLista, idVotante, idCargo);

		cout << "Candidato (" << idCandidato << "). Cargo" << idCargo << ". Lista: " << idLista << endl;
		string msg = "Candidato (" + Helper::IntToString(idCandidato) + "). Cargo" + Helper::IntToString(idCargo) + ". Lista: " + idLista;
		Log::WriteLog(msg+ " ", "files/logs/cargaMasiva.log");

    }

    delete abmCandidato;
}

void CargaMasiva::CargarAdministradores(){

	//Cargo CANT_ADMINISTRADORES administradores
	ABMAdministrador* abmAdministrador = new ABMAdministrador();

    for(int i = 1; i <= CANT_ADMINISTRADORES; i++){

    	string admin = "Admin";
		admin.append(Helper::IntToString(i));
		Administrador  * adm = new Administrador(admin,admin);
		abmAdministrador->Add(adm);

		cout << "Administrador. User: " << adm->GetUsuario() << ". Password: " << adm->GetClave() << endl;
		string msg = "Administrador. User: " + adm->GetUsuario() + ". Password: " + adm->GetClave();
		Log::WriteLog(msg+ " ", "files/logs/cargaMasiva.log");
    }

    delete abmAdministrador;
}

//Carga todas las entidades
void CargaMasiva::CargarEntidades(){

	//Inicializo los ids en 1
	Identities::InitializeFile();
	cout << endl;

	//BorrarArchivos();
	BorraTodosArchivos();
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

				Eleccion* eleccion = elecc->GetEleccion(i);
				vector<int> ds = eleccion->GetDistritos();
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
