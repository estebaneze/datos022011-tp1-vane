/*
 * BPlusTreeLog.cpp
 *
 *  Created on: 18/10/2011
 *      Author: loo
 */

#include "BPlusTreeLog.h"

BPlusTreeLog::BPlusTreeLog(){
}

void BPlusTreeLog::LogProcess(BPlusTree* bpt,string fileProcess){

		//Logueo como queda el arbol
		ofstream logFile;

		logFile.open(fileProcess.c_str(), ios::app);
		bpt->printMe(logFile);
		logFile.close();
}

void BPlusTreeLog::LogInsert(KeyInt key,string value,string logOperation){
	BPlusTreeLog::LogInsert(Helper::IntToString(key), value, logOperation);
}

void BPlusTreeLog::LogInsert(Key key,string value,string logOperation){
	string message = "Inserto (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, (char*)logOperation.c_str());
}

void BPlusTreeLog::LogDelete(KeyInt key,string value,string logOperation){
	BPlusTreeLog::LogDelete(Helper::IntToString(key), value, logOperation);
}

void BPlusTreeLog::LogDelete(Key key,string value,string logOperation){
	string message = "Elimino (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, (char*)logOperation.c_str());
}

void BPlusTreeLog::LogModify(KeyInt key,string value,string logOperation){
	BPlusTreeLog::LogModify(Helper::IntToString(key), value, logOperation);
}

void BPlusTreeLog::LogModify(Key key,string value,string logOperation){
	string message = "Modifico (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, (char*)logOperation.c_str());
}

BPlusTreeLog::~BPlusTreeLog() {
}
