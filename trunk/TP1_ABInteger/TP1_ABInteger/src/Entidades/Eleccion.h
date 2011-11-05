/*
 * Eleccion.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

//Eleccion ((fecha, (cargo)ie)i, ((distrito)ie)+): Arbol B+

#include "../Common/Common.h"
#include "../utils/Fecha.h"

#ifndef ELECCION_H_
#define ELECCION_H_

class Eleccion {

	public:
		Eleccion(const Eleccion &e);
		Eleccion(int idCargo, Fecha date);
		Eleccion(int idCargo, Fecha date, int id);
		virtual ~Eleccion();
		//int GetId();
		Fecha GetDate();
		int GetIdCargo();
		vector<int> GetDistritos();
		void AddDistrito(int idDistrito);
		void RemoveDistrito(int idDistrito);
		//string GetId();	/* El id lo armamos: fecha_idcargo (NO CON |, PORQUE EN LAS DEMAS ENTIDADES SE CONFUNDIRIA CON LA CLAVE IDENTIFICADOR DEL ARBOL O HASH) */
		int GetId();
	private:
		int _id;
		Fecha _date;
		int _idCargo;
		vector<int> _distritos;
};

#endif /* ELECCION_H_ */