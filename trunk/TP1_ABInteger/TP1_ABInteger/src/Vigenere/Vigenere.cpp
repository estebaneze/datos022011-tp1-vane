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
	char letra;
	char letraKey;

	for (int i=0;i < msj.length();i++)
	{
		if (j == key.length())
			j=0;

		letra = toupper(msj.at(i));
		letraKey = toupper(key.at(j));

		if (letra >= 'A' && letra <= 'Z')
		{
			auxAscii = ((int)letra + (int)letraKey)%26;
			j++;
		}
		else
			auxAscii = (int)letra;

		rtnEncriptado += (char)auxAscii;
	}

	return rtnEncriptado;
}

string Vigenere::desencriptar(string key, string msjEncript)
{
	string rtnDesEncriptado;
	int j=0;
	int auxAscii;
	char letra;
	char letraKey;

	for (int i=0;i < msjEncript.length();i++)
	{
		if (j == key.length())
			j=0;

		letra = toupper(msjEncript.at(i));
		letraKey = toupper(key.at(j));

		if ( letra>= 'A' && letra <= 'Z')
		{
			auxAscii = ((int)letra - (int)letraKey)%26;
			j++;
		}
		else
			auxAscii = (int)letra;

		rtnDesEncriptado += (char)auxAscii;
	}

	return rtnDesEncriptado;
}
