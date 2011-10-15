/*
 * Log.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <vector>

#ifndef LOG_H_
#define LOG_H_

class Log {

	public:
		Log();
		virtual ~Log();
		static void WriteLog(std::string message);

};

#endif /* LOG_H_ */
