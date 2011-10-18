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

		HashLog::LogProcess(this->directorio,"Votante_HasProcess.log");
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
 * Devuelve un vector con los votantes sin las listas de elecciones
 * habria que implementar otro metodo en VOTANTE para obtener sus listas
 * ya qyue en el constructor se inicia con una lista vacia
 */
vector<Votante> ABMVotante::GetVotantes(){

	vector<KeyValue> values = this->directorio->getAllValues();
	vector<Votante> votantes;

	//IntegerList _listaElecciones;

		for(unsigned int i = 0; i < values.size(); i++){

			vector<string> splitedVs = Helper::split(values[i].Value, '|');

			long _dni = Helper::StringToLong(values[i].Key);

			string _nombreYApellido  = splitedVs[0];
			string _clave = splitedVs[1];
			string _domicilio = splitedVs[2];
			int _idDistrito = Helper::StringToInt(splitedVs[3]);
			/*for (unsigned int j=4; j < splitedVs.size() ;j++){
				_listaElecciones.Add(Helper::StringToInt(splitedVs[j]));
			}*/

			votantes.push_back(Votante(_dni, _nombreYApellido, _clave, _domicilio, _idDistrito));

		}

		return votantes;
}

/*
 * Devuelve votante sin su lista de elecciones, si no existe el nombre NULL
 */
Votante* ABMVotante::GetVotante(long dni){

	if (!(this->directorio->existKey(Helper::LongToString(dni)))){

		string values = directorio->find(Helper::LongToString(dni));
		vector<string> splitedVs = Helper::split(values, '|');

		string _nombreYApellido  = splitedVs[0];
		string _clave = splitedVs[1];
		string _domicilio = splitedVs[2];
		int _idDistrito = Helper::StringToInt(splitedVs[3]);

		/*for (unsigned int j=4; j < splitedVs.size() ;j++){
			_listaElecciones.Add(Helper::StringToInt(splitedVs[j]));
		}*/

		return new Votante(dni, _nombreYApellido, _clave, _domicilio, _idDistrito);
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