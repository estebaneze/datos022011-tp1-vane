/*
 * ABMEleccion.h
 *
 *  Created on: 10/10/2011
 *      Author: loo
 */

#ifndef ABMELECCION_H_
#define ABMELECCION_H_

#include "../Common/Common.h"
#include "../Entidades/Eleccion.h"
#include "../BPlusTree/BPlusTree.h"
#include "../utils/ConfigFile.h"
#include "../Common/Identities.h"
#include "../Indexes/Index.h"
#include "../BPlusTree/Element.h"
#include "../Logging/BPlusTreeLog.h"


class ABMEleccion {

	public:
		ABMEleccion();
		virtual ~ABMEleccion();
		bool Exists(Eleccion* eleccion);
		bool Exists(int idEleccion);
		int ObtenerKey(Eleccion* eleccion);
		bool ExistsKey(KeyInt idEleccion);
		//bool ExistsKey(Fecha fecha,int idCargo);
		int Add(Eleccion* eleccion);
		bool Delete(Eleccion* eleccion);
		bool Modify(Eleccion* eleccion);
		vector<Eleccion> GetElecciones();
		Eleccion* GetEleccion(int idEleccion);
		void mostrarEleccionesPorPantalla();
		vector<Eleccion*> GetByFecha(Fecha* fecha);
		vector<Eleccion> GetByFechaYDistrito(Fecha* fecha, int idDistrito);
	private:
			string bpTreeFile;
			BPlusTree* bpPlusTree;
			Index* indexByFecha;
			Index* indexByDistrito;
			Index* indexByCargo;

			/*Splitea el id de eleccion y te devuelve la elecicon con la fecha y el cargo correspondientes*/
			Eleccion* GenerateEleccion(int idEleccion);
};

#endif /* ABMELECCION_H_ */
