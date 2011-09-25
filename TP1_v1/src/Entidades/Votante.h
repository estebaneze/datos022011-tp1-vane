/*
 * Votante.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef VOTANTE_H_
#define VOTANTE_H_

#include "../Common/Common.h"

class Votante {
	public:
		Votante(int id, string nombreYApellido, long dni, string clave, string domicilio, int idDistrito);
		virtual ~Votante();
		string GetNombreYApellido();
		long GetDni();
		string GetClave();
		string GetDomicilio();
		int GetDistrito();
		bool VotoEnEleccion(int idEleccion);
		IntegerList EleccionesVotadas(); //Ids de las elecciones en las que ya voto
		void AgregarEleccion(int idEleccion);	//Agrega una eleccion a la lista de elccioes en las que voto
		bool Authenticate(string clave);	//Este método lo usamos para cuando el usuario ingresa al sistema

	private:
		int _id;
		string _nombreYApellido;
		long _dni;
		string _clave;	//'??????QUE ES ESTO??????????????
		string _domicilio;
		int _idDistrito;
		IntegerList _listaElecciones;	//Ids de las elecciones en las que ya voto
};

#endif /* VOTANTE_H_ */
