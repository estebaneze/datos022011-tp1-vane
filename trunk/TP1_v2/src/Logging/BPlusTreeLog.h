/*
 * BPlusTreeLog.h
 *
 *  Created on: 18/10/2011
 *      Author: loo
 */

#ifndef BPLUSTREELOG_H_
#define BPLUSTREELOG_H_

#include "../BPlusTree/BPlusTree.h"
#include "Log.h"

class BPlusTreeLog {
public:
	BPlusTreeLog();
	static void LogProcess(BPlusTree* bpt,char* logProcess);
	static void LogInsert(Key key,string valor,char* logOperation);
	static void LogDelete(Key key,string valor,char* logOperation);
	static void LogModify(Key key, string valor, char* logOperation);

	virtual ~BPlusTreeLog();
};

#endif /* BPLUSTREELOG_H_ */
