/*
 * Persistor.h
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#ifndef PERSISTOR_H_
#define PERSISTOR_H_

#include "PersistorBTree.h"

class Persistor{
private:
	/* Variable estatica de patron singleton*/
	static PersistorBTree* instance;

	static std::string 	fileName;
	static BlockSize	blockSize;

	/* Constructor privado */
	Persistor(std::string fileName, BlockSize size) ;

public:
	virtual ~Persistor();

	/* Captura la instancia del Persistor */
	static PersistorBTree* getInstance();

	/* Define la información principal del Persistor
	 * Solo permite definirlos si la instancia no fue iniciada.
	 * de caso contrario, lanzara PersistorInitializedException. */
	static void init(std::string fileName, BlockSize size) ;
};

#endif /* PERSISTOR_H_ */
