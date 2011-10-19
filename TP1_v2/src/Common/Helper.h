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
		static string FloatToString(float value);
		static string LongToString(long value);
		static long StringToLong(string value);
		static string IntToString(int value);
		static int StringToInt(string value);
		static vector<string> split(const string &s, char delim);
		static string concatenar(string value1, string value2, string delimitador);
		static string concatenar(vector<string> values, string delimitador);
		static string concatenar(vector<int> values, string delimitador);
	private:
		static vector<string> &split(const string &s, char delim, vector<string> &elems);
};

#endif /* HELPER_H_ */
