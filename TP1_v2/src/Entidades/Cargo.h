/*
 * Cargo.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef CARGO_H_
#define CARGO_H_

#include "../Common/Common.h";

class Cargo {

	public:
		Cargo(int idCargo);
		virtual ~Cargo();
		int GetIdCargo();
		IntegerList GetCargosSecundarios();
		void AddCargoSecundario(int idCargo);
	private:
		int _idCargo;
		IntegerList _cargosSecundarios;
};

#endif /* CARGO_H_ */
