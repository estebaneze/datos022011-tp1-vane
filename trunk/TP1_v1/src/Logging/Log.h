/*
 * Log.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

#include <iostream>
#ifndef LOG_H_
#define LOG_H_

class Log {

	public:
		Log(std::string filename);
		virtual ~Log();
		void SaveLog(std::string message);
};

#endif /* LOG_H_ */
