/*
 * BPlusTreeLog.cpp
 *
 *  Created on: 18/10/2011
 *      Author: loo
 */

#include "BPlusTreeLog.h"

BPlusTreeLog::BPlusTreeLog(){
}

void BPlusTreeLog::LogProcess(BPlusTree* bpt,char* fileProcess){

		//Logueo como queda el arbol
		ofstream logFile;

		logFile.open(fileProcess, ios::app);
		bpt->printMe(logFile);
		logFile.close();
}

void BPlusTreeLog::LogInsert(KeyInt key,string value,char* logOperation){
	BPlusTreeLog::LogInsert(Helper::IntToString(key), value, logOperation);
}

void BPlusTreeLog::LogInsert(Key key,string value,char* logOperation){
	string message = "Inserto (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, logOperation);
	//cout << message << endl;
}

void BPlusTreeLog::LogDelete(KeyInt key,string value,char* logOperation){
	BPlusTreeLog::LogDelete(Helper::IntToString(key), value, logOperation);
}

void BPlusTreeLog::LogDelete(Key key,string value,char* logOperation){
	string message = "Elimino (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, logOperation);
	//cout << message << endl;
}

void BPlusTreeLog::LogModify(KeyInt key,string value,char* logOperation){
	BPlusTreeLog::LogModify(Helper::IntToString(key), value, logOperation);
}

void BPlusTreeLog::LogModify(Key key,string value,char* logOperation){
	string message = "Modifico (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, logOperation);
	//cout << message << endl;
}

BPlusTreeLog::~BPlusTreeLog() {
	// TODO Auto-generated destructor stub
}
