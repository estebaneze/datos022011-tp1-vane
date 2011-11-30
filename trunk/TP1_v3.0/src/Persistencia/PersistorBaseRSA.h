/*
 * PersistorBaseRSA.h
 *
 *  Created on: 29/11/2011
 *      Author: loo
 */

#ifndef PERSISTORBASERSA_H_
#define PERSISTORBASERSA_H_

#include "PersistorBase.h"
#include "../utils/RSA.h"

class PersistorBaseRSA: public PersistorBase {
public:
	PersistorBaseRSA();
	PersistorBaseRSA(std::string fileName, BlockSize size);
	virtual ~PersistorBaseRSA();
	void modify(Block* block) ;
	std::string load(Offset key);
	void load(Offset key, Block* block) ;
};

#endif /* PERSISTORBASERSA_H_ */
