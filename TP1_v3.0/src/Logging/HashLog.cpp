/*
 * HashLog.cpp
 *
 *  Created on: 18/10/2011
 *      Author: gabriel
 */

#include "HashLog.h"

HashLog::HashLog(){
}

void HashLog::LogProcess(DirectoryBase* dir,string fileProcess){

		//Logueo como queda el hash
		ofstream logFile;

	//	string fileLogProccess = Helper::concatenar(this->hashFile,"HashProccess.log","_");
		logFile.open(fileProcess.c_str(), ios::app);
		dir->inform(logFile);
		logFile.close();
	}


void HashLog::LogInsert(Key key,string value,string logOperation){
	string message = "Inserto (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, (char*)logOperation.c_str());
	//cout << message << endl;
}

void HashLog::LogDelete(Key key,string value,string logOperation){
	string message = "Elimino (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, (char*)logOperation.c_str());
	//cout << message << endl;
}

void HashLog::LogModify(Key key,string value,string logOperation){
	string message = "Modifico (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, (char*)logOperation.c_str());
	//cout << message << endl;
}

HashLog::~HashLog() {
	// TODO Auto-generated destructor stub
}
