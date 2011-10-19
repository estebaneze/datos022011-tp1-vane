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
		Votante(long dni, string nombreYApellido, string clave, string domicilio, int idDistrito);
		virtual ~Votante();

		long GetDni();
		string GetNombreYApellido();
		string GetClave();
		string GetDomicilio();
		int GetDistrito();
		IntegerList GetEleccionesVotadas(); //Ids de las elecciones en las que ya voto
	    void SetClave(string clave);
	    void SetDni(long  dni);
	    void SetDomicilio(string domicilio);
	    void SetIdDistrito(int idDistrito);
	    void SetNombreYApellido(string nombreYApellido);
	    void SetEleccionesVotadas(IntegerList eleccionesVotadas);
		void AgregarEleccion(int idEleccion);	//Agrega una eleccion a la lista de elccioes en las que voto
		bool Authenticate(string clave);	//Este método lo usamos para cuando el usuario ingresa al sistema
		bool VotoEnEleccion(int idEleccion);

	private:
		long _dni;
		string _nombreYApellido;
		string _clave;
		string _domicilio;
		int _idDistrito;
		IntegerList _listaElecciones;	//Ids de las elecciones en las que ya voto
};

#endif /* VOTANTE_H_ */
