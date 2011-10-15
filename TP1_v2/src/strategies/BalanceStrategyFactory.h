/*
 * BalanceStrategyFactory.h
 *
 *  Created on: Apr 28, 2010
 *      Author: carlos
 */

#ifndef BALANCESTRATEGYFACTORY_H_
#define BALANCESTRATEGYFACTORY_H_
#include "../utils/const.h"
#include "BalanceStrategy.h"
#include "ComposedBalanceStrategy.h"
class BalanceStrategyFactory {
public:

	static BalanceStrategy* createBalanceStrategy(int operation);
	static ComposedBalanceStrategy* createComposedBalanceStrategy(int operation);
	BalanceStrategyFactory();
	virtual ~BalanceStrategyFactory();

};

#endif /* BALANCESTRATEGYFACTORY_H_ */
