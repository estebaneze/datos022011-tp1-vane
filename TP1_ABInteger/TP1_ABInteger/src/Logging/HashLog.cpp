/*
 * HashLog.cpp
 *
 *  Created on: 18/10/2011
 *      Author: gabriel
 */

#include "HashLog.h"

HashLog::HashLog(){
}

void HashLog::LogProcess(Directory* dir,char* fileProcess){

		//Logueo como queda el hash
		ofstream logFile;

	//	string fileLogProccess = Helper::concatenar(this->hashFile,"HashProccess.log","_");
		logFile.open(fileProcess, ios::app);
		dir->inform(logFile);
		logFile.close();
	}


void HashLog::LogInsert(Key key,string value,char* logOperation){
	string message = "Inserto (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, logOperation);
	//cout << message << endl;
}

void HashLog::LogDelete(Key key,string value,char* logOperation){
	string message = "Elimino (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, logOperation);
	//cout << message << endl;
}

void HashLog::LogModify(Key key,string value,char* logOperation){
	string message = "Modifico (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, logOperation);
	//cout << message << endl;
}

HashLog::~HashLog() {
	// TODO Auto-generated destructor stub
}
