/*
 * DeleteBalanceStrategy.cpp
 *
 *  Created on: Apr 28, 2010
 *      Author: carlos
 */

#include "DeleteBalanceStrategy.h"
#include "../utils/const.h"
#include "BalanceStrategyFactory.h"
DeleteBalanceStrategy::DeleteBalanceStrategy() {

}

//Devuelve true si parent ha cambiado
bool DeleteBalanceStrategy::doBalance(Node* parent, BNode* child){
	//verificamos si hay underflow.

	ComposedBalanceStrategy* strategy=BalanceStrategyFactory::createComposedBalanceStrategy(UNDERFLOW);
	return strategy->doBalance(parent,child,this);
}


int DeleteBalanceStrategy::getTypeOfStrategy(){
	return DELETE;
}
DeleteBalanceStrategy::~DeleteBalanceStrategy() {
}
