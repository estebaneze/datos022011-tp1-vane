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
{
	short sizeNombre=0;
	short sizeCargos=0;


	//consigo tamaño de cada campo para armar los delimitadores
	sizeNombre = nombre.size();
	sizeCargos = cargosSec.size()*4; //cantidad de cargos * 4 bytes de cada Int


	//paso los tamaños a char
	char c_sizeNombre[2];
	char c_sizeCargos[2];

	for (int i=0; i<2;i++){
		memcpy((void*)c_sizeNombre,(const void*)&sizeNombre,2);
		memcpy((void*)c_sizeCargos,(const void*)&sizeCargos,2);
	}

	string data="";
	data.append(1,c_sizeNombre[0]);
	data.append(1,c_sizeNombre[1]);
	data.append(nombre.c_str());
	data.append(1,c_sizeCargos[0]);
	data.append(1,c_sizeCargos[1]);

	//concateno cada cargos uno desytras de otro sabiendo que cada uno ocupa 4 bytes.
	for (unsigned int i=0; i< cargosSec.size(); i++){
		data.append(Helper::copyBytesToString(cargosSec.at(i)).c_str(),4);
	}

	data.append("|"); //este pipe hace que el string no haga recorte por ceros al final
	//cout << data.size() << endl;
	return data;

}



void ProcessData::obtenerData(string valor, string &nombre, vector<int> & CargosSec)
{
	char c_sizeNombre[2];
	char c_sizeCargo[2];

	unsigned int i=0;
	short tamDato=0;
	string aux="";

	//RECUPERO DE NOMBRE
	c_sizeNombre[0]=valor.c_str()[0];
	c_sizeNombre[1]=valor.c_str()[1];
	i=2;

	memcpy((void*)&tamDato,(void*)&c_sizeNombre,2);

	for (int j=0;j<(tamDato)&& (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}

	nombre.append(aux);

	//RECUPERO CARGOS
	c_sizeCargo[0]=valor.c_str()[i];
	i++;
	c_sizeCargo[1]=valor.c_str()[i];
	i++;

	tamDato=0;
	memcpy((void*)&tamDato,(void*)&c_sizeCargo,2);
	CargosSec.clear(); //LIMPIO EL VECTOR POR LAS DUDAS QUE VENGA CON BASURA

	for (unsigned int j=0; j<(tamDato/4) && (i<valor.size());j++){  //divido por 4 or que el tamaño de cada elemento (int)

		aux.clear();
		for (int k=0 ; k<4 ; k++){
			aux.append(1,valor.at(i));
			i++;
		}

		CargosSec.push_back(Helper::copyBytesToInt(aux));

	}

}

void ProcessData::obtenerData(string valor, string & nombre, string & clave, string & dom, int & idDistrito, vector<int> & listaElecciones)
{
	char c_sizeNombre[2];
	char c_sizeClave[2];
	char c_sizeDom[2];
	char c_sizeDis[2];
	char c_sizeLista[2];
	unsigned int i=0;
	short tamDato=0;
	string aux="";

	//RECUPERO DE NOMBRE
	c_sizeNombre[0]=valor.c_str()[0];
	c_sizeNombre[1]=valor.c_str()[1];
	i=2;

	memcpy((void*)&tamDato,(void*)&c_sizeNombre,2);

	for (int j=0;j<(tamDato)&& (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}
	nombre.append(aux);

	//RECUPERO CLAVE
	c_sizeClave[0]=valor.c_str()[i];
	i++;
	c_sizeClave[1]=valor.c_str()[i];
	i++;

	tamDato=0;
	memcpy((void*)&tamDato,(void*)&c_sizeClave,2);

	aux.clear();
	for (int j=0;j<(tamDato)&& (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}

	clave.append(aux);

	//RECUPERO DOMICILIO
	c_sizeDom[0]=valor.c_str()[i];
	i++;
	c_sizeDom[1]=valor.c_str()[i];
	i++;

	tamDato=0;
	memcpy((void*)&tamDato,(void*)&c_sizeDom,2);

	aux.clear();
	for (int j=0; j<tamDato && (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}
	dom.append(aux);


	//RECUPERO DISTRITO
	c_sizeDis[0]=valor.c_str()[i];
	i++;
	c_sizeDis[1]=valor.c_str()[i];
	i++;

	tamDato=0;
	memcpy((void*)&tamDato,(void*)&c_sizeDis,2);

	aux.clear();
	for (int j=0; j<tamDato && (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}

	idDistrito= Helper::copyBytesToInt(aux);


	//RECUPERO LISTA ELECCIONES
	c_sizeLista[0]=valor.c_str()[i];
	i++;
	c_sizeLista[1]=valor.c_str()[i];
	i++;

	tamDato=0;
	memcpy((void*)&tamDato,(void*)&c_sizeLista,2);

	listaElecciones.clear(); //limpio el vector por si trae basura. Deberia estar vacio

	for (unsigned int k=0; k< (tamDato/4) && (i<valor.size()); k++){
		//hago tamDato/4 ya que cada dato tiene 4 bytes (son Int)
		aux.clear();

		for (int j=0; j<4 && (i<valor.size());j++){
			aux.append(1,valor.at(i));
			i++;
		}

		listaElecciones.push_back(Helper::copyBytesToInt(aux));
	}

}

/*
 * generarData usado en ABMVotante
 */
string ProcessData::generarData(string nombre, string clave, string domicilio, int distrito, vector<int> listaElecciones)
{
	short sizeNombre=0;
	short sizeClave=0;
	short sizeDom=0;
	short sizeDis=0;
	short sizeLista=0;

	//consigo tamaño de cada campo para armar los delimitadores
	sizeNombre = nombre.size();
	sizeClave = clave.size();
	sizeDom = domicilio.size();
	sizeDis = sizeof(int);
	sizeLista = listaElecciones.size()*4; //x4 ya que cada elemento es un int (4 bytes)

  	//paso los tamaños a char
	char c_sizeNombre[2];
	char c_sizeClave[2];
	char c_sizeDom[2];
	char c_sizeDis[2];
	char c_sizeLista[2];

	for (int i=0; i<2;i++){

	memcpy((void*)c_sizeNombre,(const void*)&sizeNombre,2);
	memcpy((void*)c_sizeClave,(const void*)&sizeClave,2);
	memcpy((void*)c_sizeDom,(const void*)&sizeDom,2);
	memcpy((void*)c_sizeDis,(const void*)&sizeDis,2);
	memcpy((void*)c_sizeLista,(const void*)&sizeLista,2);

	}
	string data="";
  	data.append(1,c_sizeNombre[0]);
  	data.append(1,c_sizeNombre[1]);
	data.append(nombre.c_str());
	data.append(1,c_sizeClave[0]);
	data.append(1,c_sizeClave[1]);
	data.append(clave.c_str(),4);
	data.append(1,c_sizeDom[0]);
	data.append(1,c_sizeDom[1]);
	data.append(domicilio.c_str(),4);
	data.append(1,c_sizeDis[0]);
	data.append(1,c_sizeDis[1]);
	data.append(Helper::copyBytesToString(distrito).c_str(),4);

	//concateno cada cargos uno desytras de otro sabiendo que cada uno ocupa 4 bytes.
	for (unsigned int i=0; i< listaElecciones.size(); i++){
		data.append(Helper::copyBytesToString(listaElecciones.at(i)).c_str(),4);
	}

	data.append("|"); //este pipe hace que el string no haga recorte por ceros al final
	//cout << data.size() << endl;
	return data;
}




