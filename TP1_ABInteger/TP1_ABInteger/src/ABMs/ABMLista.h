/*
 * ABMLista.h
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */

#ifndef ABMLISTA_H_
#define ABMLISTA_H_

#include "../Common/Common.h"
#include "../Entidades/Lista.h"
#include "../Hash/Directory.h"
#include "../Indexes/Index.h"
#include "../Logging/HashLog.h"
#include "../utils/ConfigFile.h"

class ABMLista {

	public:
		ABMLista();
		virtual ~ABMLista();
		bool existKey(string key);
		void Add(Lista* lista);
		bool Delete(Lista* lista);
		void Modify(Lista* lista);
		vector<Lista> GetListas();
		Lista* GetLista(std::string nombre);
		void mostrarListasPorPantalla();
		vector<Lista> GetListasByEleccion(string idEleccion);

	private:
			string hashFile;
			Directory* directorio;
			Index* index;
};

#endif /* ABMLISTA_H_ */
