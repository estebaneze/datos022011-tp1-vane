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
	//string archivoDistrito = ConfigurationMananger::getInstance()->getDistritoFile();

    ABMDistrito abmDistrito = ABMDistrito();

    for(int i = 1; i <= CANT_DISTRITOS; i++){
    	string distrito = "Distrito ";
        distrito.append(Helper::IntToString(i));
        abmDistrito.Add(distrito);
    }

}

void CargaMasiva::CargarCandidatos(){

}

void CargaMasiva::CargarCargos(){



}

void CargaMasiva::CargarConteo(){

}

void CargaMasiva::CargarElecciones(){

}

void CargaMasiva::CargarListas(){

}

void CargaMasiva::CargarVotantes(){

}

void CargaMasiva::CargarAdministradores(){



}

//Carga todas las entidades
void CargaMasiva::CargarEntidades(){
	CargarDistritos();
	CargarCandidatos();
	CargarCargos();
	CargarConteo();
	CargarElecciones();
	CargarListas();
	CargarVotantes();
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
