/*
 * ProcessData.cpp
 *
 *  Created on: 16/11/2011
 *      Author: gabriel
 */
#include "ProcessData.h"

string ProcessData::generarDataCandidato(int idLista,long idVotante, int idCargo){

		short sizeIdLista=0;
    	short sizeIdVotante=0;
    	short sizeIdCargo=0;

    	//consigo tamaño de cada campo para armar los delimitadores
    	sizeIdLista = sizeof(int);
    	sizeIdVotante = sizeof(long);
    	sizeIdCargo = sizeof(int);

      	//paso los tamaños a char
    	char c_sizeIdLista[2];
    	char c_sizeIdVotante[2];
    	char c_sizeIdCargo[2];

    	memcpy((void*)c_sizeIdLista,(const void*)&sizeIdLista,2);
    	memcpy((void*)c_sizeIdVotante,(const void*)&sizeIdVotante,2);
    	memcpy((void*)c_sizeIdCargo,(const void*)&sizeIdCargo,2);

    	string data="";
      	data.append(1,c_sizeIdLista[0]);
      	data.append(1,c_sizeIdLista[1]);
      	data.append(Helper::copyBytesToString(idLista).c_str(),4);


    	data.append(1,c_sizeIdVotante[0]);
    	data.append(1,c_sizeIdVotante[1]);
    	data.append(Helper::copyBytesToString(idVotante).c_str(),4);

    	data.append(1,c_sizeIdCargo[0]);
    	data.append(1,c_sizeIdCargo[1]);
    	data.append(Helper::copyBytesToString(idCargo).c_str(),4);

    	data.append("|"); //este pipe hace que el string no haga recorte por ceros al final
    	return data;
}

string ProcessData::generarData(int key){

	short sizeKey=0;

	//consigo tamaño de cada campo para armar los delimitadores
	sizeKey = sizeof(int);

	//paso los tamaños a char
	char c_sizeKey[2];

	memcpy((void*)c_sizeKey,(const void*)&sizeKey,2);

	string data="";
	data.append(1,c_sizeKey[0]);
	data.append(1,c_sizeKey[1]);
	data.append(Helper::copyBytesToString(key).c_str(),4);

	data.append("|"); //este pipe hace que el string no haga recorte por ceros al final

	return data;
}

void ProcessData::obtenerData(string valor, int &campo){

	char c_sizeValor[2];

	unsigned int i=0;
	short tamDato=0;
	string aux="";

	//cout << "obtenerData: " << valor.size() << endl;
	//cout << "\n\n\n" ;
	//cout << "	Valores: " << endl;
	//for(int k = 0; k < valor.size(); k++){
	//	cout << "	valor.c_str()[" << k << "]" << valor.c_str()[k] << endl;
	//}
	//cout << endl;


	c_sizeValor[0] = valor.c_str()[i];
	i++;
	c_sizeValor[1]=valor.c_str()[i];
	i++;

	//cout << "	c_sizeValor[0]: " << c_sizeValor[0] << " c_sizeValor[1]: " << c_sizeValor[1] << endl << endl<<endl;

	tamDato = 0;
	memcpy((void*)&tamDato,(void*)&c_sizeValor,2);

	aux.clear();
	i=0;	///TODO vane: REVISAR. ACA NO TRAE EL TAMAÑO DEL CAMPO(AUNQUE NO LO NECESITO PORQUE SE QUE ES UN INT --> 4 BYTES)
			//RECUPERO el tamaño del campo. REVISAR PORQUE TENGO QUE VOLVER A PONER i = 0
	for (int j=0; j < (tamDato)&& (i < valor.size());j++){

		aux.append(1,valor.c_str()[i]);
		i++;
	}

	campo = Helper::copyBytesToLong(aux);
}

/*Procesar data de Lista*/
string ProcessData::generarDataLista(string nombreLista, int idEleccion){

	short sizeLista=0;
	short sizeIdEleccion = 0;

	//consigo tamaño de cada campo para armar los delimitadores
	sizeLista = nombreLista.size();
	sizeIdEleccion = sizeof(long);

	//paso los tamaños a char
	char c_sizeLista[2];
	char c_sizeIdEleccion[2];

	memcpy((void*)c_sizeLista,(const void*)&sizeLista,2);
	memcpy((void*)c_sizeIdEleccion,(const void*)&sizeIdEleccion,2);

	string data="";

  	data.append(1,c_sizeLista[0]);
  	data.append(1,c_sizeLista[1]);
	data.append(nombreLista.c_str());

	data.append(1,c_sizeIdEleccion[0]);
	data.append(1,c_sizeIdEleccion[1]);
	data.append(Helper::copyBytesToString(idEleccion).c_str(),4);

	data.append("|"); //este pipe hace que el string no haga recorte por ceros al final

	//cout << "generar data de lista - data.size(): " << data.size() << endl;
	//cout << "generar data de lista: " << data << endl;

	return data;
}

void ProcessData::obtenerDataLista(string valor, string &nombreLista, int &idEleccion){

	char c_sizeLista[2];
	char c_sizeEleccion[2];

	unsigned int i=0;
	short tamDato=0;
	string aux="";

	//RECUPERO DE Nombre Lista
	c_sizeLista[0]=valor.c_str()[0];
	c_sizeLista[1]=valor.c_str()[1];
	i=2;

	memcpy((void*)&tamDato,(void*)&c_sizeLista,2);

	for (int j=0;j<(tamDato)&& (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}

	nombreLista.append(aux);

	//RECUPERO id eleccion
	c_sizeEleccion[0] = valor.c_str()[i];
	i++;
	c_sizeEleccion[1]=valor.c_str()[i];
	i++;

	tamDato=0;
	memcpy((void*)&tamDato,(void*)&c_sizeEleccion,2);

	aux.clear();
	for (int j=0;j<(tamDato)&& (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}

	idEleccion = Helper::copyBytesToLong(aux);

}

void ProcessData::obtenerDataCandidato(string valor,string &campo1,long &campo2,int &campo3){

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

	memcpy((void*)c_sizeNombre,(const void*)&sizeNombre,2);
	memcpy((void*)c_sizeCargos,(const void*)&sizeCargos,2);


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

/*string ProcessData::generarData(string nombre)
{
	short sizeNombre=0;

	//consigo tamaño de cada campo para armar los delimitadores
	sizeNombre = nombre.size();

	//paso los tamaños a char
	char c_sizeNombre[2];

	memcpy((void*)c_sizeNombre,(const void*)&sizeNombre,2);

	string data="";
	data.append(1,c_sizeNombre[0]);
	data.append(1,c_sizeNombre[1]);
	data.append(nombre.c_str());

	data.append("|"); //este pipe hace que el string no haga recorte por ceros al final
	//cout << data.size() << endl;
	return data;

}*/

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

/*
 * Junto todos los string del vector en un string, poniendo delante de cada string su longitud
 */
string ProcessData::generarData(vector<string> vec)
{
	short size=0;

	char c_size[2];
	string aux;
	aux.clear();

	for (unsigned int i=0; i<vec.size();i++){
		size = vec.at(i).size(); //obtengo tamaño del string
		memcpy((void*)c_size,(const void*)&size,2); //paso size a char

		//cargo en el string aux la longitud del dato y el dato
		aux.append(1,c_size[0]);
		aux.append(1,c_size[1]);
		aux.append(vec.at(i).c_str());
		//limpio size por las dudas
		size=0;

	}

	aux.append("|"); //este pipe hace que el string no haga recorte por ceros al final
	//cout << data.size() << endl;

	return aux;
}

string ProcessData::generarData(string valor)
{
	short size=0;

	char c_size[2];
	string aux;
	aux.clear();

	size = valor.size(); //obtengo tamaño del string
	memcpy((void*)c_size,(const void*)&size,2); //paso size a char

	//cargo en el string aux la longitud del dato y el dato
	aux.append(1,c_size[0]);
	aux.append(1,c_size[1]);
	aux.append(valor.c_str());

	aux.append("|"); //este pipe hace que el string no haga recorte por ceros al final
	//cout << data.size() << endl;

	return aux;
}

/*
 *	los 2 string pasados por parametros ya estan procesados cada uno tiene una lista
 *	de string y con su longitud como prefijo. Lo unico que hago es juntarlos en un
 *	de solo string
 */
string ProcessData::generarData(string valor, string valorNuevo)
{
	//recordar que cada string tiene un "|" al final para evitar que se corte en en caso
	// que haya ceros al final, por lo tanto debo eliminar el "|" del string que va a
	// ir delante del otro
	string aux;
	string pipe("|");
	aux.append(valor.c_str());

	//busco donde esta el pipe y lo reemplazo por valorNuevo

	if(aux.find(pipe) < aux.length())
		aux.replace(aux.find(pipe),pipe.length(),valorNuevo.c_str());

	return aux;
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
/**
 * Obtener data de ABMEleccion
 */
void ProcessData::obtenerData(string valor,string &fecha,int &cargo,vector<int> &v)
//;(string valor, string & nombre, string & clave, string & dom, int & idDistrito, vector<int> & listaElecciones)
{
	char c_sizeFecha[2];
	char c_sizeCargo[2];
	char c_sizeV[2];
	unsigned int i=0;
	short tamDato=0;
	string aux="";

	//RECUPERO DE FECHA
	c_sizeFecha[0]=valor.c_str()[0];
	c_sizeFecha[1]=valor.c_str()[1];
	i=2;

	memcpy((void*)&tamDato,(void*)&c_sizeFecha,2);

	for (int j=0;j<(tamDato)&& (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}
	fecha.append(aux);


	//RECUPERO CARGO
	c_sizeCargo[0]=valor.c_str()[i];
	i++;
	c_sizeCargo[1]=valor.c_str()[i];
	i++;

	tamDato=0;
	memcpy((void*)&tamDato,(void*)&c_sizeCargo,2);

	aux.clear();
	for (int j=0; j<tamDato && (i<valor.size());j++){
		aux.append(1,valor.at(i));
		i++;
	}

	cargo= Helper::copyBytesToInt(aux);


	//RECUPERO LISTA DISTRITOS
	c_sizeV[0]=valor.c_str()[i];
	i++;
	c_sizeV[1]=valor.c_str()[i];
	i++;

	tamDato=0;
	memcpy((void*)&tamDato,(void*)&c_sizeV,2);

	v.clear(); //limpio el vector por si trae basura. Deberia estar vacio

	for (unsigned int k=0; k< (tamDato/4) && (i<valor.size()); k++){
		//hago tamDato/4 ya que cada dato tiene 4 bytes (son Int)
		aux.clear();

		for (int j=0; j<4 && (i<valor.size());j++){
			aux.append(1,valor.at(i));
			i++;
		}

		v.push_back(Helper::copyBytesToInt(aux));
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

	memcpy((void*)c_sizeNombre,(const void*)&sizeNombre,2);
	memcpy((void*)c_sizeClave,(const void*)&sizeClave,2);
	memcpy((void*)c_sizeDom,(const void*)&sizeDom,2);
	memcpy((void*)c_sizeDis,(const void*)&sizeDis,2);
	memcpy((void*)c_sizeLista,(const void*)&sizeLista,2);


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

/*
 * generarData usado en ABMEleccion
 */
string ProcessData::generarData (string fecha, int cargo,vector<int> v)
//(string nombre, string clave, string domicilio, int distrito, vector<int> listaElecciones)
{
	short sizeFecha=0;

	short sizeCargo=0;
	short sizeDistritos=0;

	//consigo tamaño de cada campo para armar los delimitadores
	sizeFecha = fecha.size();
	sizeCargo = sizeof(int);
	sizeDistritos = v.size()*4; //x4 ya que cada elemento es un int (4 bytes)

  	//paso los tamaños a char
	char c_sizeFecha[2];
	char c_sizeCargo[2];
	char c_sizeDistritos[2];

	memcpy((void*)c_sizeFecha,(const void*)&sizeFecha,2);
	memcpy((void*)c_sizeCargo,(const void*)&sizeCargo,2);
	memcpy((void*)c_sizeDistritos,(const void*)&sizeDistritos,2);

	string data="";
  	data.append(1,c_sizeFecha[0]);
  	data.append(1,c_sizeFecha[1]);
	data.append(fecha.c_str());
	data.append(1,c_sizeCargo[0]);
	data.append(1,c_sizeCargo[1]);
	data.append(Helper::copyBytesToString(cargo).c_str(),4);

	//concateno cada distritos uno desytras de otro sabiendo que cada uno ocupa 4 bytes.
	for (unsigned int i=0; i< v.size(); i++){
		data.append(Helper::copyBytesToString(v.at(i)).c_str(),4);
	}

	data.append("|"); //este pipe hace que el string no haga recorte por ceros al final
	//cout << data.size() << endl;
	return data;
}



/*
 * obtengo datos de valor y los guardo separados en un vector
 */
void ProcessData::obtenerData(string valor, vector<string> & vec)
{
	//char para cargar la lonmgitud de cada elemento
	char c_size[2];

	unsigned int i=0;
	short tamDato=0;
	string aux="";

	//voy obteniendo la long de cada string y despues lo recupero en el vector
	for (i=0; i<valor.size();/*NO incremento "i" aca, lo hace adentro mismo*/){

		c_size[0] = valor.c_str()[i];
		i++;
		c_size[1] = valor.c_str()[i];
		i++;

		//cout << "valor.c_str()[" << i <<  "]: " << valor.c_str()[i] << endl;
		if(i >= valor.size()){
			//cout << " break " << endl;
			break;
		}
		else{
			//cout << "valor.c_str()[" << i <<  "]: " << valor.at(i) << endl;
		}

		memcpy((void*)&tamDato,(void*)&c_size,2);

		for (int j = 0; j < (tamDato) && (i < valor.size()); j++){

			aux.append(1,valor.at(i));
			i++;
		}

		//cout << "aux " << aux << endl;
		vec.push_back(aux);
	}


}






