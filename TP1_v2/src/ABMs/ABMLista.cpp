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
ABMLista::ABMLista(string hashFile, string indexFile) {

	this->hashFile= hashFile;
	this->directorio = new Directory(hashFile,64);
	this->index = new ListaIndex(indexFile);

	//Descomentar esto si quiere verse el contenido del archivo por pantalla
	//this->directorio->inform();

	// OJO! el tamaño lo tioene que leer desde un archivo de configuracion


}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
/********* OJO: BUG EN EL INDICE, VER IMPLE DEL INDICE *****************/
void ABMLista::Add(Lista lista){

	if (!(this->directorio->existKey(lista.GetNombre()))){
		this->directorio->insert(lista.GetNombre(),Helper::IntToString(lista.GetEleccion()));
		this->index->AppendListaToIndex(lista.GetEleccion(), lista.GetNombre());	//Tengo que refrescar el indice en todos los Adds!!!

		//logueo operacion
		this->Log(lista.GetNombre(),Helper::IntToString(lista.GetEleccion()));
	}
	else{
		cout << "Ya existe la Lista " << lista.GetNombre() << endl;
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
		this->index->AppendListaToIndex(lista.GetEleccion(), lista.GetNombre());	//Tengo que refrescar el indice en todos los Adds!!!
	}
	else{
		cout << "No existe la lista " << lista.GetNombre() << endl;
	}


}
/*
 * Devuelve un vector con el idLIsta y idEleccion correspoendiente a cada lista.
 * NO DEVUELVE LAS LIKSTAS SINO SUS ELEMENTOS
 */
vector<Lista> ABMLista::GetListas(){

	vector<KeyValue> values = this->directorio->getAllValues();
	vector<Lista> listas;

		for(unsigned int i = 0; i < values.size(); i++){

			string nombre = values[i].Key;
			int idEleccion = Helper::StringToInt(values[i].Value);

			listas.push_back(Lista(nombre,idEleccion));

		}

	//Descomentar para ver por pantalla
		/*cout << "----------------ABMLista::GetListas-----------------------" << endl;
		for(unsigned int i = 0; i < values.size(); i++){


			cout << values[i].Key << ": " << values[i].Value << endl;
		}
		cout << "----------------ABMLista::GetListas-----------------------" << endl;*/
		return listas;
}

/*
 * Devuelve la lista si no existe el nombre NULL
 */
Lista* ABMLista::GetLista(std::string nombre){

	if (!(this->directorio->existKey(nombre))){

		int auxInt = Helper::StringToInt(directorio->find(nombre));

		return new Lista(nombre,auxInt);
	}
	else return NULL;
}

bool ABMLista::existKey(Lista lista){
	return this->directorio->existKey(lista.GetNombre());
}

void ABMLista::mostrarListasPorPantalla(){
	this->directorio->inform();
}

vector<Lista> ABMLista::GetListasByEleccion(int idEleccion){
	return this->index->GetListasByIdEleccion(idEleccion);	//Busco solamente en el indice
}

void ABMLista::Log(Key key, string value){

	string message = "Inserto (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");

	//char* fileLogOperation = "Lista_HashOperations.log"
	Log::WriteLog(message, "Lista_HashOperations.log");
	//cout << message << endl;

	//Logueo como queda el hash
	ofstream logFile;

//	string fileLogProccess = Helper::concatenar(this->hashFile,"HashProccess.log","_");
	logFile.open("Lista_HashProccess.log", ios::app);
	this->directorio->inform(logFile);
	logFile.close();
}


ABMLista::~ABMLista() {
}


