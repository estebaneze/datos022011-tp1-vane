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
#include "../Logging/HashLog.h"
#include "../Indexes/Index.h"
#include "../Common/ProcessData.h"
//Cargo ((cargo)i, (cargo)*): Hash

class ABMCargo {

	public:
		ABMCargo();
		virtual ~ABMCargo();
		bool Exists(Cargo cargo);
		bool Exists(int idCargo);
		int Add(string nombre, vector<int> cargosSecundarios);
		bool Delete(int idCargo);
		void Modify(Cargo cargo);
		vector<Cargo> GetCargos();
		Cargo* GetCargo(int idCargo);

		void mostrarCargosPorPantalla();
	private:
		string hashFile;
		Directory* directorio;
		bool Exists(string nombreCargo);
		//vector<Cargo> cargos;	//Va guardando en memoria los cargos que tiene la tabla de hash --si queda tiempo lo implemento
};

#endif /* ABMCARGO_H_ */
