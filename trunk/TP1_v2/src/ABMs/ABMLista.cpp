/*
 * ABMLista.cpp
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */
#include "ABMLista.h"

/*
 * creo el directorio y le paso el nombre del archivo a generar y tamaño de los buckets
 */
ABMLista::ABMLista(string hashFile) {

	this->hashFile= hashFile;
	this->directorio = new Directory(hashFile,2048);

	//Descomentar esto si quiere verse el contenido del archivo por pantalla
	//this->directorio->inform();

	// OJO! el tamaño lo tioene que leer desde un archivo de configuracion


}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
void ABMLista::Add(Lista lista){

	if (!(this->directorio->existKey(lista.GetNombre()))){
		this->directorio->insert(lista.GetNombre(),Helper::IntToString(lista.GetEleccion()));
	}
}

/**Elimina una lista, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMLista::Delete(Lista lista){

	if (this->directorio->existKey(lista.GetNombre())){
		return (this->directorio->remove(lista.GetNombre()));
	}
	else{
		return false;
	}
}

/**Modifica el idEleccion de una lista pasada por parametro
* si la encuentra la modifica sino no hace nada
*/
void ABMLista::ModifyEleccion(Lista lista){

	if (this->directorio->existKey(lista.GetNombre())){
		this->directorio->modify(lista.GetNombre(),Helper::IntToString(lista.GetEleccion()));
	}

}
/*
 * Devuelve un vector con el idLIsta y idEleccion correspoendiente a cada lista.
 * NO DEVUELVE LAS LIKSTAS SINO SUS ELEMENTOS
 */
vector<KeyValue> ABMLista::GetListas(){

	vector<KeyValue> values = this->directorio->getAllValues();

	//Descomentar para ver por pantalla
		/*cout << "----------------ABMCandidato::GetCandidatos-----------------------" << endl;
		for(unsigned int i = 0; i < values.size(); i++){


			cout << values[i].Key << ": " << values[i].Value << endl;
		}
		cout << "----------------ABMCandidato::GetCandidatos-----------------------" << endl;*/
		return values;
}

/*
 * Devuelve la lista si no existe el nombre NULL
 */
Lista* ABMLista::GetLista(std::string nombre){

	if (!(this->directorio->existKey(nombre))){
		Lista* listaAux;
		int auxInt;
		auxInt = Helper::StringToInt(directorio->find(nombre));
		listaAux = new Lista(nombre,auxInt);

		return listaAux;
	}
	else return NULL;
}

bool ABMLista::existKey(Lista lista){
	return this->directorio->existKey(lista.GetNombre());
}

void ABMLista::mostrarListasPorPantalla(){
	this->directorio->inform();
}

ABMLista::~ABMLista() {
}


