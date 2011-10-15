/*
 * ModifyBalanceStrategy.h
 *
 *  Created on: Apr 28, 2010
 *      Author: carlos
 */

#ifndef MODIFYBALANCESTRATEGY_H_
#define MODIFYBALANCESTRATEGY_H_

#include "BalanceStrategy.h"
class ModifyBalanceStrategy: public BalanceStrategy {
public:
	ModifyBalanceStrategy();
	virtual ~ModifyBalanceStrategy();
	/*
	 * Devuelve true o false si modifico al padre o no
	 */
	bool doBalance(Node* parent, BNode* child);

	/**
	 * Devuelve el tipo de estrategia segun el archivo const.h
	 */
	int getTypeOfStrategy();
};

#endif /* MODIFYBALANCESTRATEGY_H_ */
