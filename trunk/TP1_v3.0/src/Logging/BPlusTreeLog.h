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

	static void LogProcess(BPlusTree* bpt,string logProcess);
	static void LogProcess(BPlusTree* bpt,string fileProcess, string dataType);

	static void LogInsert(Key key,string valor,string logOperation);
	static void LogInsert(KeyInt key,string value,string logOperation);

	static void LogDelete(Key key,string valor,string logOperation);
	static void LogDelete(KeyInt key,string valor,string logOperation);

	static void LogModify(Key key, string valor, string logOperation);
	static void LogModify(KeyInt key, string valor, string logOperation);

	virtual ~BPlusTreeLog();
};

#endif /* BPLUSTREELOG_H_ */
