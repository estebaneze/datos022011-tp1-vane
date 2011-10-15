/*
 * ABMConteo.h
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */

#ifndef ABMCONTEO_H_
#define ABMCONTEO_H_

#include "../Common/Common.h"
#include "../Entidades/Conteo.h"
#include "../BPlusTree/BPlusTree.h"

class ABMConteo {
public:
	ABMConteo(string BPTree);
	void mostrarListasPorPantalla();
	virtual ~ABMConteo();
	void Add(Conteo conteo);
private:
		string bpTreeFile;
		BPlusTree* bplusTree;
};

#endif /* ABMCONTEO_H_ */
