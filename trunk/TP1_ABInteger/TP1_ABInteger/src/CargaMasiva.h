/*
 * CargaMasiva.h
 *
 *  Created on: 01/11/2011
 *      Author: loo
 */

#ifndef CARGAMASIVA_H_
#define CARGAMASIVA_H_

#include "ABMs/ABMDistrito.h"
#include "ABMs/ABMCandidato.h"
#include "ABMs/ABMCargo.h"
#include "ABMs/ABMConteo.h"
#include "ABMs/ABMEleccion.h"
#include "ABMs/ABMLista.h"
#include "ABMs/ABMVotante.h"
#include "ABMs/ABMAdministrador.h"
#include "utils/ConfigFile.h"
#include "Common/Helper.h"

#define CANT_DISTRITOS 100
#define CANT_CANDIDATOS 100
#define CANT_CARGOS 100
#define CANT_CONTEO 100
#define CANT_ELECCIONES 100
#define CANT_LISTAS 100
#define CANT_VOTANTES 100
#define CANT_ADMINISTRADORES 100

class CargaMasiva {

	public:
		static void CargarDistritos();
		static void CargarCandidatos();
		static void CargarCargos();
		static void CargarConteo();
		static void CargarElecciones();
		static void CargarListas();
		static void CargarVotantes();
		static void CargarAdministradores();

		//Carga todas las entidades
		static void CargarEntidades();

};

#endif /* CARGAMASIVA_H_ */
