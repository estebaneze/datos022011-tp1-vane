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
#include "../Indexes/ListaIndex.h"
#include "../Logging/HashLog.h"

class ABMLista {

	public:
		ABMLista(string HashFile, string indexFile);
		virtual ~ABMLista();
		bool existKey(Lista lista);
		void Add(Lista lista);
		bool Delete(Lista lista);
		void ModifyEleccion(Lista lista);
		vector<Lista> GetListas();
		Lista* GetLista(std::string nombre);
		void mostrarListasPorPantalla();
		vector<Lista> GetListasByEleccion(int idEleccion);

	private:
			string hashFile;
			Directory* directorio;
			ListaIndex* index;
};

#endif /* ABMLISTA_H_ */
