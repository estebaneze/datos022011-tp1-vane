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
#include "../ABMs/ABMConteo.h"
#include "../ABMs/ABMEleccion.h"

class ABMLista {

	public:
		ABMLista();
		virtual ~ABMLista();
		bool existKey(int idLista);
		int Add(Lista* lista);
		//bool Delete(Lista* lista);
		//void Modify(Lista* lista);
		vector<Lista> GetListas();
		Lista* GetLista(int idLista);
		void mostrarListasPorPantalla();
		vector<Lista> GetListasByEleccion(int idEleccion);

	private:
		string hashFile;
		Directory* directorio;
		Index* indexByEleccion;
};

#endif /* ABMLISTA_H_ */