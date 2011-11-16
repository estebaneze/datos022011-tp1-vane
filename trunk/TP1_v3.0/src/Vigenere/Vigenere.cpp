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
	int letra;
	int letraKey;

	for (int i=0;i < msj.length();i++)
	{
		if (j == key.length()) //VUELVE A 1ER CHAR DE KEY
			j=0;

		letra = (int)msj.at(i);;
		letraKey = (int)key.at(j);

		if (letra >= 32 && letra <= 126) //SI ES CHAR IMPRIMIBLE
		{
			auxAscii =  Modulo((letra-32) + (letraKey-32), 95) + 32; //95 CHARS, EMPIEZA DESDE ' '(espacio)
			j++;
		}
		else
			auxAscii = letra;

		rtnEncriptado += (char)auxAscii;
	}

	return rtnEncriptado;
}

string Vigenere::desencriptar(string key, string msjEncript)
{
	string rtnDesEncriptado;
	int j=0;
	int auxAscii;
	int letra;
	int letraKey;

	for (int i=0;i < msjEncript.length();i++)
	{
		if (j == key.length()) //VUELVE A 1ER CHAR DE KEY
			j=0;

		letra = (int)msjEncript.at(i);
		letraKey = (int)key.at(j);

		if (letra >= 32 && letra <= 126) //SI ES CHAR IMPRIMIBLE
		{
			auxAscii = Modulo((letra-32) - (letraKey-32),95) + 32; //95 CHARS, EMPIEZA DESDE ' '(espacio)
			j++;
		}
		else
			auxAscii = letra;

		rtnDesEncriptado += (char)auxAscii;
	}

	return rtnDesEncriptado;
}

int Vigenere::Modulo(int valor1, int valor2)
{
	int resultadoParcial;

	if (valor1>=0)
		resultadoParcial = valor1%valor2;
	else
	{
		resultadoParcial = valor1;
		while (resultadoParcial < 0)
		{
			resultadoParcial = resultadoParcial + valor2;
		}
	}

	return resultadoParcial;
}
