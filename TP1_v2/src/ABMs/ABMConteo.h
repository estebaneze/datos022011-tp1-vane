/*
 * ABMConteo.h
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */

#ifndef ABMCONTEO_H_
#define ABMCONTEO_H_

#include "../Common/Common.h"
#include "../Entidades/Conteo.h"
#include "../BPlusTree/BPlusTree.h"
#include "../Indexes/Index.h"
#include "../Common/Identities.h"

class ABMConteo {

	public:
		ABMConteo(string BPTree, string indexFile);
		void mostrarListasPorPantalla();
		virtual ~ABMConteo();
		void Add(int idLista, int idDistrito, int idEleccion);
		vector<Conteo> GetConteoByDistrito(int idDistrito);
	private:
		string bpTreeFile;
		BPlusTree* bplusTree;
		//Index* indexDistrito;

};

#endif /* ABMCONTEO_H_ */
