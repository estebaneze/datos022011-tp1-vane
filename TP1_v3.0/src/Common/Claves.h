/*
 * Claves.h
 *
 *  Created on: 09/10/2011
 *      Author: minnie

 */

#ifndef CLAVES_H_
#define CLAVES_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "Helper.h"
#include "../utils/ConfigurationMananger.h"
#include "../Persistencia/Archivo.h"
#include "../Common/Helper.h"


using namespace std;

class Claves {

	public:
		static long int GetClavePublicaN();
		static long int GetClavePrivadaN();
		static long int GetClavePrivadaD();
		static long int GetClavePublicaE();


		static void GuardarClaves(long int n, long int e, long int d);

	private:
		static long int GetId(string key);

};

#endif /* CLAVES_H_ */
