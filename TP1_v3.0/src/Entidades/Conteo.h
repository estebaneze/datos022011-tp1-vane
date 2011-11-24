/*
 * Conteo.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "../Common/Common.h"
#include "Eleccion.h"

#ifndef CONTEO_H_
#define CONTEO_H_

//Conteo (((lista)ie, (distrito)ie, (eleccion)ie)i, cantidad): Arbol B+

class Conteo {

	public:
		Conteo();
		Conteo(int idLista, int idDistrito, int idEleccion, int idConteo);
		Conteo(int idLista, int idDistrito, int idEleccion, int idConteo, int cantVotos);
		virtual ~Conteo();
		int GetIdLista();
		int GetIdDistrito();
		//Eleccion* GetEleccion();
		int GetIdEleccion();
		int AddVoto();
		int GetCountVotos();
		int GetId();
	private:
		int _idLista;
		int _idDistrito;
		//Eleccion* _eleccion;
		int _idEleccion;
		int _countVotos;
		int _id;
};

#endif /* CONTEO_H_ */

