/*
 * BalanceStrategyFactory.cpp
 *
 *  Created on: Apr 28, 2010
 *      Author: carlos
 */

#include "BalanceStrategyFactory.h"
#include "InsertBalanceStrategy.h"
#include "ModifyBalanceStrategy.h"
#include "OverflowStrategy.h"
#include "../utils/const.h"
#include "UnderflowStrategy.h"
#include "DeleteBalanceStrategy.h"
#include "UnderflorRootStrategy.h"
#include <exception>
BalanceStrategy* BalanceStrategyFactory::createBalanceStrategy(int operation){
	BalanceStrategy* strategy;
	switch (operation) {
		case INSERT:
				strategy=new InsertBalanceStrategy();
			break;
		case MODIFY:
				strategy=new ModifyBalanceStrategy();
			break;
		case DELETE:
				strategy=new DeleteBalanceStrategy();
				break;
		default:
			throw new std::exception();
			break;
	}

	return strategy;
}

ComposedBalanceStrategy* BalanceStrategyFactory::createComposedBalanceStrategy(int operation){
	ComposedBalanceStrategy* strategy;
	switch (operation) {
		case OVERFLOW:
			strategy=new OverflowStrategy();
			break;
		case UNDERFLOW:
			strategy=new UnderflowStrategy();
			break;
		default:
			break;
	}
	return strategy;
}
BalanceStrategyFactory::BalanceStrategyFactory() {

}

BalanceStrategyFactory::~BalanceStrategyFactory() {
}
