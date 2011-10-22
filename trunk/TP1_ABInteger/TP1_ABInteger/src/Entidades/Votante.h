/*
 * Votante.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#ifndef VOTANTE_H_
#define VOTANTE_H_

#include "../Common/Common.h"
#include "Eleccion.h"

class Votante {
	public:
		Votante(long dni, string nombreYApellido, string clave, string domicilio, int idDistrito);
		virtual ~Votante();

		long GetDni();
		string GetNombreYApellido();
		string GetClave();
		string GetDomicilio();
		int GetDistrito();
		vector<int> GetEleccionesVotadas(); //Ids de las elecciones en las que ya voto
	    void SetClave(string clave);
	    void SetDni(long  dni);
	    void SetDomicilio(string domicilio);
	    void SetIdDistrito(int idDistrito);
	    void SetNombreYApellido(string nombreYApellido);
		void AgregarEleccion(int idEleccion);	//Agrega una eleccion a la lista de elccioes en las que voto
		bool Authenticate(string clave);	//Este método lo usamos para cuando el usuario ingresa al sistema
		bool VotoEnEleccion(Eleccion eleccion);
		bool VotoEnEleccion(int idEleccion);
		bool VotoEnEleccion(Eleccion* eleccion);

	private:
		long _dni;
		string _nombreYApellido;
		string _clave;
		string _domicilio;
		int _idDistrito;
		vector<int> _listaElecciones;	//Ids de las elecciones en las que ya voto
};

#endif /* VOTANTE_H_ */
