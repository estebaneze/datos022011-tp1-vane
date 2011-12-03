/*
 * HashLog.h
 *
 *  Created on: 18/10/2011
 *      Author: gabriel
 */

#ifndef HASHLOG_H_
#define HASHLOG_H_

#include "../Hash/DirectoryBase.h"
#include "Log.h"

class HashLog {

	public:
		HashLog();
		static void LogProcess(DirectoryBase* dir,string logProcess);
		static void LogProcess(DirectoryBase* dir,string fileProcess, string dataType);
		static void LogInsert(Key key,string valor,string logOperation);
		static void LogDelete(Key key,string valor,string logOperation);
		static void LogModify(Key key, string valor, string logOperation);

		virtual ~HashLog();
};

#endif /* HASHLOG_H_ */
