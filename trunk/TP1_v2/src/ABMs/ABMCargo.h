/*
 * ABMCargo.h
 *
 *  Created on: 17/10/2011
 *      Author: vanesa
 */

#ifndef ABMCARGO_H_
#define ABMCARGO_H_

#include "../Common/Common.h"
#include "../Entidades/Cargo.h"
#include "../Hash/Directory.h"

//Cargo ((cargo)i, (cargo)*): Hash

class ABMCargo {

	public:
		ABMCargo(string hashFile);
		virtual ~ABMCargo();
		bool Exists(Cargo cargo);
		void Add(string nombre, vector<int> cargosSecundarios);
		bool Delete(int idCargo);
		void Modify(Cargo cargo);
		vector<Cargo> GetCargos();
		Cargo* GetCargo(int idCargo);
		void mostrarCargosPorPantalla();
	private:
		string hashFile;
		Directory* directorio;

};

#endif /* ABMCARGO_H_ */
