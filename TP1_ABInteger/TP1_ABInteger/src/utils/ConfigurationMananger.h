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
	 * Tamaño del bloque del los archivos de hash
	 */
	int hashBSizeCandidato;
	int hashBSizeAdministrador;
	int hashBSizeCargo;
	int hashBSizeLista;
	int hashBSizeVotante;

	/**
	 * Archivo de configuracion
	 */
	ConfigFile *configFile;

public:

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

	/**
	 * Devuelven el tamaño del bloque de los archivos de hash
	 */
	int getHashBSizeCandidato();
	int getHashBSizeAdministrador();
	int getHashBSizeCargo();
	int getHashBSizeLista();
	int getHashBSizeVotante();
};

#endif /* CONFIGURATIONMANANGER_H_ */
