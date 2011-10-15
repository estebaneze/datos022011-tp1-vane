/*
 * UnderflorRootStrategy.h
 *
 *  Created on: May 1, 2010
 *      Author: carlos
 */

#ifndef UNDERFLORROOTSTRATEGY_H_
#define UNDERFLORROOTSTRATEGY_H_

#include "BalanceStrategy.h"

class UnderflorRootStrategy{
public:
	UnderflorRootStrategy();
	virtual ~UnderflorRootStrategy();
	BNode* doBalance(BNode* root);
};

#endif /* UNDERFLORROOTSTRATEGY_H_ */
