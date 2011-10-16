/*
 * ABMVotante.cpp
 *
 *  Created on: 15/10/2011
 *      Author: gabriel
 */

#include "ABMVotante.h"

/*
 * creo el directorio y le paso el nombre del archivo a generar y tamaño de los buckets
 */
ABMVotante::ABMVotante(string file) {

	this->file = file;
	this->directorio = new Directory(file,2048);

	//Descomentar esto si quiere verse el contenido del archivo por pantalla
	//this->directorio->inform();

	// OJO! el tamaño lo tioene que leer desde un archivo de configuracion


}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
void ABMVotante::Add(Votante votante){

	if (!(this->directorio->existKey(Helper::LongToString(votante.GetDni())))){

		string aux= Helper::concatenar(votante.GetNombreYApellido(),votante.GetClave(),"|");
		aux = Helper::concatenar(aux,votante.GetDomicilio(),"|");
		aux = Helper::concatenar(aux,Helper::IntToString(votante.GetDistrito()),"|");

		//recorro la lista de eleccion y agrego todos los IdEleccion al string aux
		for (unsigned int i=0;i<(votante.GetEleccionesVotadas().GetSize());i++){
			aux = Helper::concatenar(aux,Helper::IntToString(votante.GetEleccionesVotadas().Get(i)),"|");
		}

		this->directorio->insert(Helper::LongToString(votante.GetDni()),aux);
	}
}

/**Elimina un votante, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMVotante::Delete(Votante votante){

	if (this->directorio->existKey(Helper::LongToString(votante.GetDni()))){
		return (this->directorio->remove(Helper::LongToString(votante.GetDni())));
	}
	else{
		return false;
	}
}

/**Modifica votante pasado por parametro
* si la encuentra la modifica sino no hace nada
*/
void ABMVotante::Modify(Votante votante){

	if (this->directorio->existKey(Helper::LongToString(votante.GetDni()))){

		//concateno todos los campos de votante para luego guardarlo
		string aux= Helper::concatenar(votante.GetNombreYApellido(),votante.GetClave(),"|");
		aux = Helper::concatenar(aux,votante.GetDomicilio(),"|");
		aux = Helper::concatenar(aux,Helper::IntToString(votante.GetDistrito()),"|");

		//recorro la lista de eleccion y agrego todos los IdEleccion al string aux
		for (unsigned int i=0;i<(votante.GetEleccionesVotadas().GetSize());i++){
			aux = Helper::concatenar(aux,Helper::IntToString(votante.GetEleccionesVotadas().Get(i)),"|");
		}

		this->directorio->modify(Helper::LongToString(votante.GetDni()),aux);
	}

}
/*
 * Devuelve un vector con el dni y y el resto de los campos
 * NO DEVUELVE objeto votante SINO SUS ELEMENTOS
 * la clave dni y el campo con el resto de los campos, hay que desconcatenarlos
 */
vector<KeyValue> ABMVotante::GetVotantes(){

	vector<KeyValue> values = this->directorio->getAllValues();

	//Descomentar para ver por pantalla
		/*cout << "----------------ABMVotante::GetVotantes-----------------------" << endl;
		for(unsigned int i = 0; i < values.size(); i++){


			cout << values[i].Key << ": " << values[i].Value << endl;
		}
		cout << "----------------ABMVotante::GetVotantes-----------------------" << endl;*/
		return values;
}

/*
 * Devuelve votante si no existe el nombre NULL
 */
Votante* ABMVotante::GetVotante(long dni){

	if (!(this->directorio->existKey(Helper::LongToString(dni)))){
		Votante* VotanteAux;

		//Hay que desconcatenar todos los elementos

		//VotanteAux = new Votante(nombre,0);

		return VotanteAux;
	}
	else return NULL;
}

bool ABMVotante::existKey(Votante votante){
	return this->directorio->existKey(Helper::LongToString(votante.GetDni()));
}

//muestrp key (dni) y resto de los elementos todos concatenados
void ABMVotante::mostrarVotantesPorPantalla(){
	this->directorio->inform();
}

ABMVotante::~ABMVotante() {
	// TODO Auto-generated destructor stub
}
