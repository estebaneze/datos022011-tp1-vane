/*
 * Vigenere.h
 *
 *  Created on: 14/11/2011
 *      Author: ricardo
 */

#include <iostream>
#include <cstdlib>
#include <string>

#ifndef VIGENERE_H_
#define VIGENERE_H_

using namespace std;
class Vigenere {
	public:
		static string encriptar(string key, string msj);
		static string desencriptar(string key, string msjEncript);
	private:
		static int Modulo(int valor1, int valor2);
};


#endif /* VIGENERE_H_ */
