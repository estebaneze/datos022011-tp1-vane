/*
 * Identities.h
 *
 *  Created on: 09/10/2011
 *      Author: minnie
 *
 *  Esta clase proporciona los autonumericos para todas las clases
 */

#ifndef IDENTITIES_H_
#define IDENTITIES_H_

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

using namespace std;

class Identities {

	public:
		static int GetNextIdCandidato();
		static int GetNextIdCargo();
		static int GetNextIdDistrito();
		static int GetNextIdAdministrador();
		static void InitializeFile();
	private:
		static void RefreshFile(string key, int value);
		static string _file;
		static int GetNextId(string key);
};

#endif /* IDENTITIES_H_ */
