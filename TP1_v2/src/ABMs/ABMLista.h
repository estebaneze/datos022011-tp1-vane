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

class ABMLista {
public:
	ABMLista(string HashFile);
	virtual ~ABMLista();
	bool existKey(Lista lista);
	void Add(Lista lista);
	bool Delete(Lista lista);
	void ModifyEleccion(Lista lista);
	vector<Lista> GetListas(); //FALTA HACER ESTE
	Lista* GetLista(std::string nombre);
	void mostrarListasPorPantalla();
private:
		string hashFile;
		Directory* directorio;
};

#endif /* ABMLISTA_H_ */
