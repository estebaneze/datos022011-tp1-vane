/*
 * Conteo.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "../Common/Common.h"

#ifndef CONTEO_H_
#define CONTEO_H_

//Conteo (((lista)ie, (distrito)ie, (eleccion)ie)i, cantidad): Arbol B+

class Conteo {

	public:
		Conteo(std::string  idLista, int idDistrito, int idEleccion, int idConteo);
		virtual ~Conteo();
		string  GetIdLista();
		int GetIdDistrito();
		int GetIdEleccion();
		void AddVoto();
		int GetCountVotos();
		int GetId();
	private:
		string  _idLista;
		int _idDistrito;
		int _idEleccion;
		int _countVotos;
		int _id;
};

#endif /* CONTEO_H_ */

