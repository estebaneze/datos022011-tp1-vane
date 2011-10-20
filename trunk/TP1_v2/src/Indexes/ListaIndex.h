/*
 * Index.h
 *
 *  Created on: 16/10/2011
 *      Author: minnie
 */

#ifndef LISTAINDEX_H_
#define LISTAINDEX_H_

#include "../Hash/KeyValue.h"
#include "../Hash/Directory.h"
#include "../Common/Entidades.h"
#include "../Common/Common.h"

class ListaIndex {

	public:
		ListaIndex(string filename);
		virtual ~ListaIndex();
		vector<Lista> GetListasByIdEleccion(string idEleccion);
		void RefreshIndexLista(string idEleccion, vector<string> listas);
		void AppendListaToIndex(string idEleccion, string lista);

	private:
		string hashFile;
		Directory* directorio;

};

#endif /* INDEX_H_ */
