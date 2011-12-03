/*
 * RSA.h
 *
 *  Created on: 29/11/2011
 *      Author: loo
 */

#ifndef RSA_H_
#define RSA_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include "../Common/Helper.h"
#include <math.h>
#include "BadRSAKeySizeException.h"
#include "../Common/Claves.h"

using namespace std;

class RSA {

	public:
		static void generarClave();
		static char* encriptar(char* m);
		static void encriptar2(char* m);
		static char* desencriptar(char* c);
		static char* desencriptar2();
		static void CheckCache();

	//private:
		/*static long int p;
		static long int q;
		static long int n;
		static long int e;
		static long int d;
		static long int fi;*/
		//static string GetAlfabeto();
		static bool es_primo(int n);
		static int get_pos(string str,char elemento);
		static string validar_mensaje(string texto_plano);
		static int alg_euc(int a,int b);
		static long* alg_euc_ext(int n1,int n2); // n1 es a y n2 es b
		static long Inverso_Zn(int a,int n);
		static unsigned long long Exponenciacion_Zn(unsigned long long  a,unsigned long long  k,unsigned long long  n);
		static void validarTamClave();
};


#endif /* RSA_H_ */
