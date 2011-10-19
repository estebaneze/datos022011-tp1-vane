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


class ABMEleccion {

	public:
		ABMEleccion(string bpTreeFile);
		virtual ~ABMEleccion();
		bool Exists(Eleccion eleccion);
		bool Exists(int idEleccion);
		bool ExistsKey(Key idEleccion);
		int Add(Eleccion eleccion);
		bool Delete(Eleccion eleccion);
		void Modify(Eleccion eleccion);
		vector<Eleccion> GetElecciones();
		Eleccion * GetEleccion(Fecha fecha, int cargo);
		void mostrarEleccionesPorPantalla();
	private:
			string bpTreeFile;
			BPlusTree* bpPlusTree;
			Index* indexByFecha;

};

#endif /* ABMELECCION_H_ */