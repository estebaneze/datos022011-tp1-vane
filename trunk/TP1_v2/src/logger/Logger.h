/**
 * Clase singleton que permite hacer logging de mensajes
 * sobre uno o varios archivos de log
 * autor nromani, ssoria.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "exceptions/FileNotOpenException.h"

/**
 * Definición
 */
class Logger {

/* Miembros privados de la clase Logger*/
private:
	/**
	 * Instancia singleton de la clase Logger.
	 */
	static Logger* logger;

	/*
	 * Numero del proximo archivo de log
	 */
	int nextFile;

	/*
	 * Numero de registros en archivo de log actual
	 */
	int count;

	/*
	 * Numero de registros maximo en archivo de log
	 */
	static int limit;

	/**
	 * Almacena un stream de salida sobre el archivo de log.
	 */
	std::fstream ioFile;

	/**
	 * Constructor privado de la clase Logger.
	 */
	Logger();

	/*
	 * Se encarga de cerrar el archivo actual, lo renombra y lo vuelve a abrir.
	 */
	void renameFile();

	/*
	 * Obtiene el Valor del siguiente archivo de Log
	 */
	int setNextFile();

	/*
	 * Arma el string con la fecha y hora actuales.
	 */
	std::string getTime();

/*Miembros publicos de la clase Logger*/
public:
	/**
	 * Devuelve la unica instancia del singleton.
	 */
	static Logger* getInstance();

	/**
	 * Setea la cantidad de registros
	 */
	static void setLimit(int cantRegistros);

	/**
	 * Escribe un mensaje de debug sobre el log.
	 */
	void debug(std::string message);

	/**
	 * Escribe un mensaje de informacion sobre el log.
	 */
	void info(std::string message);

	/**
	 * Escribe un mensaje de warning sobre el log.
	 */
	void warn(std::string message);

	/**
	 * Escribe un mensaje de error sobre el log.
	 */
	void error(std::string message);

	/**
	 * Inserta un mensaje en el archivo de log.
	 */
	void insert(std::string& key, std::string& value);

	/*
	 * Busca una cadena de caracteres dentro el/los archivo/s de log
	 */
	int buscar(std::string cadena);

	/*
	 * Busca las cantidad de ocurrencias de "subCadena" dentro de "cadena"
	 */
	int encontrarOcurrencias(std::string cadena, std::string subCadena);

	/*
	 * Lista todas las lineas de el/los archivo/s de log
	 */
	void listar();

	/**
	 * Destructor virtual de la clase Logger.
	 */
	virtual ~Logger();
};

#endif /** LOGGER_H */
