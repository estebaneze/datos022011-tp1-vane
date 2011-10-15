/*
 * ComposedBalanceStrategy.h
 *
 *  Created on: Apr 29, 2010
 *      Author: carlos
 */

#ifndef COMPOSEDBALANCESTRATEGY_H_
#define COMPOSEDBALANCESTRATEGY_H_
#include "../utils/const.h"
#include "../strategies/BalanceStrategy.h"
#include "../BPlusTree/Node.h"
#include "../BPlusTree/BNode.h"
/**
 * Estrategia de balanceo que tiene que ser llamada por otra estrategia.
 * Estas no pueden ser llamadas solas.
 */
class ComposedBalanceStrategy {
public:
	ComposedBalanceStrategy();
	virtual ~ComposedBalanceStrategy();
	virtual bool doBalance(Node* parent, BNode* child,BalanceStrategy* parentStrategy)=0;

};

#endif /* COMPOSEDBALANCESTRATEGY_H_ */
