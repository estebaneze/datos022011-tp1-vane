/*
 * HashLog.h
 *
 *  Created on: 18/10/2011
 *      Author: gabriel
 */

#ifndef HASHLOG_H_
#define HASHLOG_H_

#include "../Hash/Directory.h"
#include "Log.h"

class HashLog {
public:
	HashLog();
	static void LogProcess(Directory* dir,char* logProcess);
	static void LogInsert(Key key,string valor,char* logOperation);
	static void LogDelete(Key key,string valor,char* logOperation);
	static void LogModify(Key key, string valor, char* logOperation);

	virtual ~HashLog();
};

#endif /* HASHLOG_H_ */
