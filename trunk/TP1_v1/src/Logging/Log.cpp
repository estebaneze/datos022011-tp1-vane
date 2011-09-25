/*
 * Log.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include "Log.h"


using namespace std;

Log::Log() {

}

Log::~Log() {
}

void Log::WriteLog(std::string message){

	time_t rawtime;
    time ( &rawtime );

    std:string time(ctime(&rawtime));
	fstream File;

	File.open("Log.txt", ios::out);

	if (File.is_open ()) {
		File << "%s" << time << ":" << message << "\n";
	}

	File.close();

}
