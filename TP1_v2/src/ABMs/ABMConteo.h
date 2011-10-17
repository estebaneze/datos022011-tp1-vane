/*
 * ABMConteo.h
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */

#ifndef ABMCONTEO_H_
#define ABMCONTEO_H_

#include "../BPlusTree/BPlusTree.h"
#include "../Common/Identities.h"
#include "../Indexes/Index.h"
#include "../Entidades/Conteo.h"

using namespace std;

class ABMConteo {

	public:
		ABMConteo(string BPTree, string indexDistritoFile, string indexEleccionFile, string indexListaFile);
		void mostrarListasPorPantalla();
		virtual ~ABMConteo();
		void Add(int idLista, int idDistrito, int idEleccion);
		vector<Conteo> GetConteoByDistrito(int idDistrito);
		vector<Conteo> GetConteoByLista(int idLista);
		vector<Conteo> GetConteoByEleccion(int idEleccion);
	private:
		string bpTreeFile;
		BPlusTree* bplusTree;
		Index* indexByDistrito;
		Index* indexByEleccion;
		Index* indexByLista;
};

#endif /* ABMCONTEO_H_ */
