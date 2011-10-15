/*
 * DeleteBalanceStrategy.h
 *
 *  Created on: Apr 28, 2010
 *      Author: carlos
 */

#ifndef DELETEBALANCESTRATEGY_H_
#define DELETEBALANCESTRATEGY_H_

#include "BalanceStrategy.h"
#include "ComposedBalanceStrategy.h"
class DeleteBalanceStrategy: public BalanceStrategy {
public:
	DeleteBalanceStrategy();
	virtual ~DeleteBalanceStrategy();
	bool doBalance(Node* parent, BNode* child);
	/**
	 * Devuelve el tipo de estrategia segun el archivo const.h
	 */
	int getTypeOfStrategy();
};

#endif /* DELETEBALANCESTRATEGY_H_ */
