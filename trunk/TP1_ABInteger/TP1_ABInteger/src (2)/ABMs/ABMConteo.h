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
#include "../Entidades/Votante.h"
#include "../Common/Helper.h"
#include "ABMVotante.h"
#include "ABMEleccion.h"

using namespace std;

class ABMConteo {

	public:
		ABMConteo();
		void mostrarConteoPorPantalla();
		virtual ~ABMConteo();
		int Add(string idLista, int idDistrito, int idEleccion);

		vector<Conteo> GetConteoByDistrito(int idDistrito);
		vector<Conteo> GetConteoByDistritoYFecha(int idDistrito, Fecha fecha);
		vector<Conteo> GetConteoByLista(string idLista);
		vector<Conteo> GetConteoByEleccion(int idEleccion);

		Conteo* GetConteo(int idConteo);

		/* Le suma un voto al registro y devuelve la cantidad de votos totales */
		void AddVoto(int idConteo, Votante* votante);

		/*Busca el registro de Conteo segun la lisa, distrito y eleccion y le suma un voto. Devuelve la cantidad de votos totales*/
		//void AddVoto(string idLista, int idDistrito, int idEleccion, Votante* votante);

		bool ExistsKey(KeyInt key);
	private:
		BPlusTree* bplusTree;
		Index* indexByDistrito;
		Index* indexByEleccion;
		Index* indexByLista;

		/* Le avisa al Votante que ya voto en esta eleccion */
		void NotifyVotante(Votante* votante, int idEleccion);
};

#endif /* ABMCONTEO_H_ */
