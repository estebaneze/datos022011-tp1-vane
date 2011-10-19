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
		int Add(string idLista, int idDistrito, int idEleccion);
		vector<Conteo> GetConteoByDistrito(int idDistrito);
		vector<Conteo> GetConteoByLista(string idLista);
		vector<Conteo> GetConteoByEleccion(int idEleccion);
		Conteo* GetConteo(int idConteo);

		/* Le suma un voto al registro y devuelve la cantidad de votos totales */
		int AddVoto(int idConteo);

		/*Busca el registro de Conteo segun la lisa, distrito y eleccion y le suma un voto. Devuelve la cantidad de votos totales*/
		int AddVoto(string idLista, int idDistrito, int idEleccion);
	private:
		BPlusTree* bplusTree;
		Index* indexByDistrito;
		Index* indexByEleccion;
		Index* indexByLista;
};

#endif /* ABMCONTEO_H_ */