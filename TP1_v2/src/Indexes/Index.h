/*
 * Index.h
 *
 *  Created on: 16/10/2011
 *      Author: minnie
 */

#ifndef INDEX_H_
#define INDEX_H_

#include "../Hash/KeyValue.h"
#include "../Hash/Directory.h"
#include "../Common/Entidades.h"
#include "../Common/Common.h"

class Index {

	public:
		Index(string filename);
		virtual ~Index();
		vector<Lista> GetListasByIdEleccion(int idEleccion);
		void RefreshIndexLista(int idEleccion, vector<string> listas);
		void AppendListaToIndex(int idEleccion, string lista);
	private:
		string hashFile;
		Directory* directorio;

};

#endif /* INDEX_H_ */
