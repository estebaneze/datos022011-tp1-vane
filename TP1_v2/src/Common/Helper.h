/*
 * Helper.h
 *
 *  Created on: 09/10/2011
 *      Author: minnie
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <string>

using namespace std;

class Helper {
	public:
		static string IntToString(int value);
		static int StringToInt(string value);
		static vector<string> split(const string &s, char delim);
	private:
		static vector<string> &split(const string &s, char delim, vector<string> &elems);
};

#endif /* HELPER_H_ */
