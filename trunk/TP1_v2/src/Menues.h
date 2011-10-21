/*
 * Menues.h
 *
 *  Created on: 19/10/2011
 *      Author: gabriel
 */

#ifndef MENUES_H_
#define MENUES_H_


#include <stdio.h>
#include <stdlib.h>
#include "ABMs/ABMVotante.h"
#include "ABMs/ABMAdministrador.h"
#include "ABMs/ABMLista.h"
#include "ABMs/ABMCandidato.h"
#include "ABMs/ABMCargo.h"
#include "ABMs/ABMConteo.h"
#include "ABMs/ABMDistrito.h"
#include "ABMs/ABMEleccion.h"
#include "utils/Fecha.h"
#include "Logging/Log.h"
#include <ctime>

class Menues {
public:
	Menues();
	void MenuPpal();
	void MenuVotante();
	void MenuAdmin();
	void Menu_EleccionesXDistrito_votante(Votante* votante);
	void Menu_ListasXEleccion(Eleccion* eleccion);
	void MenuABM();
	void MenuABMDistrito();
	void MenuABMVotante();
	void MenuABMEleccion();
	void MenuABMCargo();
	void MenuABMLista();
	void MenuABMCandidato();
	void Reportes();
	virtual ~Menues();

private:
	Fecha fechaActual();
};

#endif /* MENUES_H_ */
