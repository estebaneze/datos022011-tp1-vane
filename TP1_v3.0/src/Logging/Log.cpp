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

void Log::WriteLog(std::string message, char* filename){

	time_t rawtime;
    time ( &rawtime );
    std:string time(ctime(&rawtime));
    time.append(" - ");

	string line;
	ofstream logFile;
	logFile.open(filename, ios::app);

	if(logFile.is_open()){

		time.append(" - ");
		time.append(message);
		logFile.write(time.c_str(), time.size());

		logFile.close();
	}

		/*
	//Me guardo las lineas con los valores
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			lines.push_back(line);
		}
		myfile.close();
	}

	fstream File;
    std:string time(ctime(&rawtime));
	File.open("Log.txt", ios::out);
*/
	/*if (File.is_open ()) {
		for(int i = 0; i < lines.size(); i++){
			File << lines[i] << endl;
		}

		File <<  message << "---" << time  << "\n";
	}

	File.close();
*/
}
