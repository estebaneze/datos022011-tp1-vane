/*
 * Conteo.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef CONTEO_H_
#define CONTEO_H_

class Conteo {

	public:
		Conteo(int idLista, int idDistrito, int idEleccion);
		virtual ~Conteo();
		int GetIdLista();
		int GetIdDistrito();
		int GetIdEleccion();
		void AddVoto();
		int GetCountVotos();
	private:
		int _idLista;
		int _idDistrito;
		int _idEleccion;
		int _countVotos;
};

#endif /* CONTEO_H_ */

