/*
 * Vigenere.cpp
 *
 *  Created on: 14/11/2011
 *      Author: ricardo
 */

#include "Vigenere.h"

using namespace std;
string Vigenere::encriptar(string key, string msj)
{
	string rtnEncriptado;
	int j=0;
	int auxAscii;

	for (int i=0;i < msj.length();i++)
	{
		if (j == key.length())
			j=0;

		if(msj[i] == 32) // si es espacio lo dejo igual
			auxAscii = 32;
		else
		{
			auxAscii = ((int)msj.at(i) + (int)key.at(j))%26;
			j++;
		}

		rtnEncriptado += (char)auxAscii;
	}

	return rtnEncriptado;
}

string Vigenere::desencriptar(string key, string msjEncript)
{
	string rtnDesEncriptado;
	int j=0;
	int auxAscii;

	for (int i=0;i < msjEncript.length();i++)
	{
		if(msjEncript[i] == 32) // si es espacio lo dejo igual
			auxAscii = 32;
		else
		{
			auxAscii = ((int)msjEncript.at(i) - (int)key.at(j))%26;
			j++;
		}

		rtnDesEncriptado += (char)auxAscii;
	}

	return rtnDesEncriptado;
}
