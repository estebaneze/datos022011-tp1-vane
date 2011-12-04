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
#include "Common/Identities.h"
#include "utils/ConfigurationMananger.h"

#define CANT_DISTRITOS 20
#define CANT_CANDIDATOS 20
#define CANT_CARGOS 80
#define CANT_LISTAS 20
#define CANT_VOTANTES 60
#define CANT_ELECCIONES 60
#define CANT_ADMINISTRADORES 1

class CargaMasiva {

	public:

		//Carga todas las entidades
		static void CargarEntidades();
		static void GenerarVotosAutomaticos();
		static void GenerarVotosAutomaticos2();

//	private:
		static vector<Votante*> GetVotantesByDistrito(vector<Votante*> votantes, int idDistrito);
		static void BorraTodosArchivos();
		static void CargarVotantes();
		static void CargarDistritos();
		static void CargarCandidatos();
		static void CargarCargos();
		static void CargarElecciones();
		static void CargarListas();

		static void CargarAdministradores();
		static int GetRandom(int maxNumber);
		static vector<int> GetIdsConteos(vector<Conteo> cs);
		static int GetRandomFromNumbers(vector<int> posibleNumbers);
		static void BorrarArchivos();
		static void BorrarArchivosLog();
		static void BorrarArchivosIndice(string indexFile);

};

#endif /* CARGAMASIVA_H_ */