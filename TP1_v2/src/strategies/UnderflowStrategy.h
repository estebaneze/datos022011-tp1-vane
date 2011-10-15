/*
 * UnderflowStrategy.h
 *
 *  Created on: Apr 28, 2010
 *      Author: carlos
 */

#ifndef UNDERFLOWSTRATEGY_H_
#define UNDERFLOWSTRATEGY_H_

#include "ComposedBalanceStrategy.h"

class UnderflowStrategy: public ComposedBalanceStrategy {
private:
	bool doBalaceForRightNode(Node* parent, BNode* child);
	bool doBalanceForLeftNode(Node* parent, BNode* child);
	/**
	 * Devuelve true en caso que el padre cambio.
	 */
	bool join(Node* parent,BNode* child);
public:
	UnderflowStrategy();
	virtual ~UnderflowStrategy();
	bool doBalance(Node* parent, BNode* child,BalanceStrategy* parentStrategy);
};

#endif /* UNDERFLOWSTRATEGY_H_ */
