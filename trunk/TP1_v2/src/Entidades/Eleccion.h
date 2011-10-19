/*
 * Eleccion.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "../Common/Common.h"
#include "../utils/Fecha.h"

#ifndef ELECCION_H_
#define ELECCION_H_

class Eleccion {

	public:
		Eleccion(int idCargo, Fecha date);
		virtual ~Eleccion();
		Fecha GetDate();
		int GetIdCargo();
		IntegerList GetDistritos();
		void AddDistrito(int idDistrito);
		void RemoveDistrito(int idDistrito);

	private:
		int _id;
		Fecha _date;
		int _idCargo;
		IntegerList _distritos;
};

#endif /* ELECCION_H_ */
