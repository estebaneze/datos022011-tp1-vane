/*
 * InsertBalanceStrategy.cpp
 *
 *  Created on: Apr 28, 2010
 *      Author: carlos
 */

#include "InsertBalanceStrategy.h"
#include "../Persistence/Persistor.h"
#include "../Persistence/PersistorBTree.h"
#include "../BPlusTree/KeyElement.h"
#include "BalanceStrategyFactory.h"
#include "ComposedBalanceStrategy.h"
#include "../utils/const.h"
InsertBalanceStrategy::InsertBalanceStrategy() {

}

InsertBalanceStrategy::~InsertBalanceStrategy() {
}

int InsertBalanceStrategy::getTypeOfStrategy(){
	return INSERT;
}

/**
 * Si modifica parent debe devolver true.
 * Persistir la hijo es responsabilidad de esta clase.
 */
bool InsertBalanceStrategy::doBalance(Node* parent,BNode* child){
	bool hasChanged=false;
	bool hasChangedForUnderflow;
	ComposedBalanceStrategy* strategy=BalanceStrategyFactory::createComposedBalanceStrategy(OVERFLOW);
	hasChanged=strategy->doBalance(parent,child,this);
	strategy=BalanceStrategyFactory::createComposedBalanceStrategy(UNDERFLOW);
	hasChangedForUnderflow=strategy->doBalance(parent,child,this);
	hasChanged=hasChanged||hasChanged;
	delete strategy;
    return hasChanged;
}
