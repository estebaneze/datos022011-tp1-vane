/*
 * ModifyBalanceStrategy.cpp
 *
 *  Created on: Apr 28, 2010
 *      Author: carlos
 */

#include "ModifyBalanceStrategy.h"
#include "OverflowStrategy.h"
#include "BalanceStrategyFactory.h"
#include "../utils/const.h"
ModifyBalanceStrategy::ModifyBalanceStrategy() {

}

ModifyBalanceStrategy::~ModifyBalanceStrategy() {
}

int ModifyBalanceStrategy::getTypeOfStrategy(){
	return MODIFY;
}
bool ModifyBalanceStrategy::doBalance(Node* parent,BNode* child){
	ComposedBalanceStrategy* strategy=BalanceStrategyFactory::createComposedBalanceStrategy(OVERFLOW);
	bool hasChanged=strategy->doBalance(parent,child,this);

	if(!hasChanged){//si no cambio verifico si esta en underflow.
		strategy=BalanceStrategyFactory::createComposedBalanceStrategy(UNDERFLOW);
		hasChanged=strategy->doBalance(parent,child,this);
	}

	return hasChanged;

}
