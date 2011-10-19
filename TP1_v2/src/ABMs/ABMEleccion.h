/*
 * ABMEleccion.h
 *
 *  Created on: 19/10/2011
 *      Author: minnie
 */

#ifndef ABMELECCION_H_
#define ABMELECCION_H_

#include "../BPlusTree/BPlusTree.h"
#include "../Common/Identities.h"
#include "../Indexes/Index.h"
#include "../Entidades/Eleccion.h"
#include "../Common/Helper.h"

class ABMEleccion {

	public:
		ABMEleccion(string btreeFile, string indexByFechaFile, string indexByCargoFile);
		Eleccion* GetEleccion(int idEleccion);
		virtual ~ABMEleccion();
	private:
		string bpTreeFile;
		BPlusTree* bplusTree;
		Index* indexByCargo;
		Index* indexByFecha;
};

#endif /* ABMELECCION_H_ */
