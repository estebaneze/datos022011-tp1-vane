/*
 * Cargo.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef CARGO_H_
#define CARGO_H_

#include "../Common/Common.h"

class Cargo {

	public:
		Cargo(int idCargo, string nombre);
		Cargo(int idCargo, string nombre, vector<int> cargos);
		virtual ~Cargo();
		int GetId();
		vector<int> GetCargosSecundarios();
		void AddCargoSecundario(int idCargo);
		string GetNombre();
	private:
		int _idCargo;
		string _nombre;
		vector<int> _cargosSecundarios;
};

#endif /* CARGO_H_ */
