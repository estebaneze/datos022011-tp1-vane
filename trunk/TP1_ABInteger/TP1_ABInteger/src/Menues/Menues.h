/*
 * Menues.h
 *
 *  Created on: 19/10/2011
 *      Author: gabriel
 */

#ifndef MENUES_H_
#define MENUES_H_

#include "../Reportes/Reportes.h"
#include <stdio.h>
#include <stdlib.h>
#include "../ABMs/ABMVotante.h"
#include "../ABMs/ABMAdministrador.h"
#include "../ABMs/ABMLista.h"
#include "../ABMs/ABMCandidato.h"
#include "../ABMs/ABMCargo.h"
#include "../ABMs/ABMConteo.h"
#include "../ABMs/ABMDistrito.h"
#include "../ABMs/ABMEleccion.h"
#include "../utils/Fecha.h"
#include "../Logging/Log.h"
#include "../Logging/VotanteLog.h"
#include "../CargaMasiva.h"
#include <ctime>

class Menues {
public:
	Menues();
	static void MenuInicial();
	static void MenuPpal();
	static void MenuVotante();
	static void MenuAdmin();
	static void Menu_EleccionesXDistrito_votante(Votante* votante);
	static void Menu_ListasXEleccion(Eleccion* eleccion);
	static void MenuABM();
	static void MenuABMDistrito();
	static void MenuABMVotante();
	static void MenuABMEleccion();
	static void MenuABMCargo();
	static void MenuABMLista();
	static void MenuABMCandidato();
	static void Reportes();


private:
	static Fecha fechaActual();
	static Votante* EditaVotante(string dni);
};

#endif /* MENUES_H_ */
