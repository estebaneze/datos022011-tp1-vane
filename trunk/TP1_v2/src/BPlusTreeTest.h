/*
 * BPlusTreeTest.h
 *
 *  Created on: Apr 17, 2010
 *      Author: carlos
 */

#ifndef BPLUSTREETEST_H_
#define BPLUSTREETEST_H_

#include "BPlusTree/BPlusTree.h"

class BPlusTreeTest {
private:
	BPlusTree* bplus;
	void firstSetTest();
	void secondSetTest();
	void thirdSetTest();
public:
	BPlusTreeTest();
	void run();
	virtual ~BPlusTreeTest();
};

#endif /* BPLUSTREETEST_H_ */
