/*
 * ConfigurationMananger.h
 * Clase singleton donde se setean los parámetros de configuración
 *
 *  Created on: 10/04/2010
 *      Author: nazareno
 */

#ifndef CONFIGURATIONMANANGER_H_
#define CONFIGURATIONMANANGER_H_

#include "types.h"
#include <string>
#include "ConfigFile.h"

class ConfigurationMananger {
private:
	/** instancia del Singletone. */
	static ConfigurationMananger* instance;

	//Constructor privado
	ConfigurationMananger();

	/** Almacena el porcentaje util de un nodo */
	ChargeFactor chargeFactor;

	/** Define el los bloques cabecera. */
	int bufferSize;

	/**
	 * Tamaño del buffer del arbol
	 */
	int bufferSizeTree;

	/**
	 * Tamaño minimo del registro que puede tener.
	 */
	int minRecordSizeTree;

	/**
	 * Tamaño maximo del registro que puede tener.
	 */
	int maxRecordSizeTree;

	/**
	 * Archivo de configuracion
	 */
	ConfigFile *configFile;
public:
	//Destructor
	virtual ~ConfigurationMananger();

     /**
	 * Devuelve la unica instancia del singleton.
	 */
	static ConfigurationMananger* getInstance();

	ChargeFactor getChargeFactor();
	int maxNodeLoadForInsert();
	/**
	 * Tamano que tiene el buffer, Nodo, o bloque
	 */
	int getBufferSize();

	int getBufferSizeTree();

	/**
	 * Devuelve el tama�o minimo de underflow permitido
	 *  50% tama�o del bloque -  el tama�o maximo del registro
	 */
	int getMinUnderflowSizeTree();

	int getMinRecordSizeTree();

	int getMaxRecordSizeTree();
};

#endif /* CONFIGURATIONMANANGER_H_ */
