/*
 * ProcessData.cpp
 *
 *  Created on: 16/11/2011
 *      Author: gabriel
 */

#include "ProcessData.h"

string ProcessData::generarData(string idLista,long idVotante, int idCargo){

		short sizeIdLista=0;
    	short sizeIdVotante=0;
    	short sizeIdCargo=0;

    	//consigo tamaño de cada campo para armar los delimitadores
    	sizeIdLista = idLista.size();
    	sizeIdVotante = sizeof(long);
    	sizeIdCargo = sizeof(int);

      	//paso los tamaños a char
    	char c_sizeIdLista[2];
    	char c_sizeIdVotante[2];
    	char c_sizeIdCargo[2];

    	for (int i=0; i<2;i++){

    	memcpy((void*)c_sizeIdLista,(const void*)&sizeIdLista,2);
    	memcpy((void*)c_sizeIdVotante,(const void*)&sizeIdVotante,2);
    	memcpy((void*)c_sizeIdCargo,(const void*)&sizeIdCargo,2);

    	}
    	string data="";
      	data.append(1,c_sizeIdLista[0]);
      	data.append(1,c_sizeIdLista[1]);
    	data.append(idLista.c_str());
    	data.append(1,c_sizeIdVotante[0]);
    	data.append(1,c_sizeIdVotante[1]);
    	data.append(Helper::copyBytesToString(idVotante).c_str(),4);
    	data.append(1,c_sizeIdCargo[0]);
    	data.append(1,c_sizeIdCargo[1]);
    	data.append(Helper::copyBytesToString(idCargo).c_str(),4);
    	data.append("|"); //este pipe hace que el string no haga recorte por ceros al final
    	//cout << data.size() << endl;
    	return data;

}


void ProcessData::obtenerData(string valor,string &campo1,long &campo2,int &campo3){

	vector<string> vec;
	vec.clear();

	char c_sizeLista[2];
	char c_sizeVotante[2];
	char c_sizeCargo[2];
	unsigned int i=0;
	short tamDato=0;
	string aux="";

	//RECUPERO DE IDLISTA
	c_sizeLista[0]=valor.c_str()[0];
	c_sizeLista[1]=valor.c_str()[1];
	i=2;

	memcpy((void*)&tamDato,(void*)&c_sizeLista,2);

	for (int j=0;j<(tamDato)&& (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}

	campo1.append(aux);

	//RECUPERO VOTANTE
	c_sizeVotante[0]=valor.c_str()[i];
	i++;
	c_sizeVotante[1]=valor.c_str()[i];
	i++;

	tamDato=0;
	memcpy((void*)&tamDato,(void*)&c_sizeVotante,2);

	aux.clear();
	for (int j=0;j<(tamDato)&& (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}

	campo2 = Helper::copyBytesToLong(aux);

	//RECUPERO CARGO
	c_sizeCargo[0]=valor.c_str()[i];
	i++;
	c_sizeCargo[1]=valor.c_str()[i];
	i++;

	//obtengo idVotante en formato short
	tamDato=0;
	memcpy((void*)&tamDato,(void*)&c_sizeCargo,2);

	aux.clear();
	for (int j=0; j<tamDato && (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}

	//paso todos los datos en formato string, luego el metodo invocante tiene que recuperar con su formato
	campo3 = Helper::copyBytesToInt(aux);


}

string ProcessData::generarData(string nombre, vector<int> cargosSec)
{	string aux;
	aux.clear();
	return aux;
}



void ProcessData::obtenerData(string valor, string &nombre, vector<int> & CargosSec)
{
}

void ProcessData::obtenerData(string valor, string & nombre, string & clave, string & dom, int & idDistrito, vector<int> & listaElecciones)
{
}

string ProcessData::generarData(string nombre, string clave, string domicilio, int distrito, vector<int> v)
{
	string aux;
	aux.clear();
	return aux;
}




