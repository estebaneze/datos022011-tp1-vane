/*
 * Conteo.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef CONTEO_H_
#define CONTEO_H_

//Conteo (((lista)ie, (distrito)ie, (eleccion)ie)i, cantidad): Arbol B+

using namespace std;

class Conteo {

	public:
		Conteo(int idLista, int idDistrito, int idEleccion, int idConteo);
		virtual ~Conteo();
		int GetIdLista();
		int GetIdDistrito();
		int GetIdEleccion();
		void AddVoto();
		int GetCountVotos();
		int GetId();
	private:
		int _idLista;
		int _idDistrito;
		int _idEleccion;
		int _countVotos;
		int _id;
};

#endif /* CONTEO_H_ */

