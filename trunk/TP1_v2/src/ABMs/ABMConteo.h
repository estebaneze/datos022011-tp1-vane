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
#include "../Common/Helper.h"

using namespace std;

class ABMConteo {

	public:

		ABMConteo();
		void mostrarConteoPorPantalla();
		virtual ~ABMConteo();
		int Add(int idLista, int idDistrito, int idEleccion);
		vector<Conteo> GetConteoByDistrito(int idDistrito);
		vector<Conteo> GetConteoByLista(int idLista);
		vector<Conteo> GetConteoByEleccion(int idEleccion);
	private:
		BPlusTree* bplusTree;
		Index* indexByDistrito;
		Index* indexByEleccion;
		Index* indexByLista;
};

#endif /* ABMCONTEO_H_ */
