/*
 * LennyArchivo.h
 *
 *  Created on: 18/10/2009
 *      Author: leonardo
 */

#ifndef ARCHIVO_H_
#define ARCHIVO_H_

#include <string>

using namespace std;

class Archivo {
protected:
	string _filename;
	unsigned int _componentSize;
	void mover (unsigned int);		//Seek
	FILE* _fp;

public:
	Archivo(string, unsigned int);
	virtual ~Archivo();

	string leer (unsigned int);				//Lee la posicion especificada (posicion = numero de componente)
	unsigned int agregar (string);			//Agrega un componente al final del archivo
	void escribir (string, unsigned int);	//Escribe en la posicion indicada (posicion = numero de componente)
	void eliminar (unsigned int) {};			//Marca un bloque como eliminado
	virtual unsigned int elementos();		//Cantidad de elementos en el archivo
	unsigned int size();						//Tamaño en bytes del archivo
	void vaciar();								//Toma un archivo y lo vuelve a longitud cero
	virtual void flush();
	virtual bool cached (unsigned int);
	void eliminarArchivo();

};

#endif /* LENNYARCHIVO_H_ */
