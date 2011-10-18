/*
 * ABMCandidato.h
 *
 *  Created on: 10/10/2011
 *      Author: loo
 */

#ifndef ABMDISTRITO_H_
#define ABMDISTRITO_H_

#include "../Common/Common.h"
#include "../Entidades/Distrito.h"
#include "../BPlusTree/BPlusTree.h"
#include "../utils/ConfigFile.h"
#include "../BPlusTree/Element.h"


class ABMDistrito {

	public:
		ABMDistrito(string bpTreeFile);
		virtual ~ABMDistrito();
		bool Exists(Distrito distrito);
		bool Exists(int idDistrito);
		bool ExistsKey(Key idDistrito);
		int Add(string nombre);
		bool Delete(int idDistrito);
		void Modify(Distrito distrito);
		vector<Distrito> GetDistritos();
		Distrito * GetDistrito(int idDistrito);
		void mostrarDistritosPorPantalla();
	private:
			string bpTreeFile;
			BPlusTree* bpPlusTree;

};

#endif /* ABMDISTRITO_H_ */
