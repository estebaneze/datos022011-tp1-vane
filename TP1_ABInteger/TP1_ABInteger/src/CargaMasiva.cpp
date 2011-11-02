/*
 * CargaMasiva.cpp
 *
 *  Created on: 01/11/2011
 *      Author: loo
 */

#include "CargaMasiva.h"

void CargaMasiva::CargarDistritos(){
/*
	//Borro el archivo de distrito
	string archivoDistrito = ConfigurationMananger::getInstance()->getDistritoFile();

    ABMDistrito abmDistrito = ABMDistrito();

    for(int i = 1; i <= CANT_DISTRITOS; i++){
            string distrito = "Distrito ";
            distrito.append(Helper::IntToString(i));
            abmDistrito.Add(distrito);
    }
    */
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


