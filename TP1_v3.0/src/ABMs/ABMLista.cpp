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
ABMLista::ABMLista() {

    int maxBucketSize = ConfigurationMananger::getInstance()->getHashBSizeLista();
	this->hashFile = ConfigurationMananger::getInstance()->getListaFile();
    this->directorio = new Directory(hashFile, maxBucketSize);

    this->indexByEleccion = new Index(Helper::concatenar(hashFile,"Lista",ConfigurationMananger::getInstance()->getSeparador2()));
}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
int ABMLista::Add(Lista* lista){

	vector<Lista> ls = this->GetListasByEleccion(lista->GetEleccion());
	for(int i = 0; i < ls.size(); i++){
		if(ls[i].GetNombre() == lista->GetNombre()){
			cout << "Ya existe la Lista con el nombre " << lista->GetNombre() << " para la eleccionindicada" << endl;
			return -1;
		}
	}

	int idLista = Identities::GetNextIdLista();

	if (!(this->directorio->existKey(Helper::copyBytesToString(idLista)))){

    	string data="";
    	//metodo que concatena todos los campos
    	int idEleccion = lista->GetEleccion();
    	string nombreLista = lista->GetNombre();
    	data = ProcessData::generarDataLista(nombreLista, idEleccion);

        this->directorio->insert(Helper::copyBytesToString(idLista), data);

		//this->directorio->insert(lista->GetNombre(),Helper::copyBytesToString(lista->GetEleccion()));

		this->indexByEleccion->AppendToIndex(lista->GetEleccion(), idLista);   //Tengo que refrescar el indice en todos los Adds!!!

		//logueo operacion y proceso

		//aca dejo el helepr:inttoString por que es para el log.
		string insertedValues = nombreLista + "|" + Helper::IntToString(lista->GetEleccion());
		HashLog::LogInsert(Helper::IntToString(idLista),insertedValues,ConfigurationMananger::getInstance()->getLogOperListaFile());
		HashLog::LogProcess(this->directorio,ConfigurationMananger::getInstance()->getLogProcessListaFile(), "lista");

		//Tengo que crear los registros de conteo con la combinacion idLista, idEleccion, idDistrito con 0 votos
		//Busco los distritos de esa eleccion

		ABMConteo conteos = ABMConteo();
		ABMEleccion elecciones = ABMEleccion();

		Eleccion* e = elecciones.GetEleccion(lista->GetEleccion());

		vector<int> distritos = e->GetDistritos();

		for(unsigned int i = 0; i < distritos.size(); i++){
			conteos.Inicializa(idLista, distritos[i], e->GetId());
		}

		return idLista;
	}
	else{
		cout << "Ya existe la Lista " << idLista << endl;
		return -1;
	}
}

/**Elimina una lista, si no exite arroja un excepcion, informa true si elimino sino false*/
/*bool ABMLista::Delete(Lista *lista){

        if (this->directorio->existKey(lista->GetNombre())){

                this->directorio->remove(lista->GetNombre());

                HashLog::LogDelete(lista->GetNombre(),Helper::IntToString(lista->GetEleccion()),"Lista_HashOperation.log");
                HashLog::LogProcess(this->directorio,"Lista_HashProccess.log");

                this->index->DeleteFromIndex(Helper::copyBytesToString(lista->GetEleccion()), lista->GetNombre());

                return true;
        }
        else{
                return false;
        }
}**/

/**Modifica el idEleccion de una lista pasada por parametro
* si la encuentra la modifica sino no hace nada
*/
/*void ABMLista::Modify(Lista *lista){

	if (this->directorio->existKey(lista->GetNombre())){

		Lista* oldLista = this->GetLista(lista->GetNombre());
		int idOldEleccion = oldLista->GetEleccion();

		this->directorio->modify(lista->GetNombre(),Helper::copyBytesToString(lista->GetEleccion()));

		this->index->AppendToIndex(Helper::copyBytesToString(lista->GetEleccion()),Helper::copyBytesToString(idOldEleccion) , lista->GetNombre());   //Tengo que refrescar el indice en todos los Adds!!!

		HashLog::LogModify(lista->GetNombre(),Helper::IntToString(lista->GetEleccion()),"Lista_HashOperation.log");
		HashLog::LogProcess(this->directorio,"Lista_HashProccess.log");
	}
	else{
		cout << "No existe la lista " << lista->GetNombre() << endl;
	}

}*/
/*
 * Devuelve un vector con el idLIsta y idEleccion correspoendiente a cada lista.
 * NO DEVUELVE LAS LIKSTAS SINO SUS ELEMENTOS
 */
vector<Lista> ABMLista::GetListas(){

        vector<KeyValue> values = this->directorio->getAllValues();
        vector<Lista> listas;

		for(unsigned int i = 0; i < values.size(); i++){

	        string nombreLista;
	        nombreLista.clear();
	        int idEleccion = 0;

	        int idLista = Helper::copyBytesToInt(values[i].Key);

			ProcessData::obtenerDataLista(values[i].Value, nombreLista, idEleccion);

	        listas.push_back(Lista(nombreLista, idEleccion, idLista));

		}

		return listas;
}

/*
 * Devuelve la lista si no existe el nombre NULL
 */
/*Lista* ABMLista::GetLista(std::string nombre){

	if ((this->directorio->existKey(nombre))){

		return new Lista(nombre,Helper::copyBytesToInt(directorio->find(nombre)));
	}
	else{
		return NULL;
	}
}*/

Lista* ABMLista::GetLista(int idLista){

	string listaId = Helper::copyBytesToString(idLista);
	if (this->directorio->existKey(listaId)){

        string values = directorio->find(listaId);

        string nombreLista;
        nombreLista.clear();
        int idEleccion = 0;
		ProcessData::obtenerDataLista(values, nombreLista, idEleccion);

        return new Lista(nombreLista, idEleccion, idLista);
	}
	else{
		return NULL;
	}
}

bool ABMLista::existKey(int idLista){

	string listaId = Helper::copyBytesToString(idLista);
    return this->directorio->existKey(listaId);
}

void ABMLista::mostrarListasPorPantalla(){
        this->directorio->inform();
}

vector<Lista> ABMLista::GetListasByEleccion(int idEleccion){

	vector<int> values = this->indexByEleccion->GetIdsInt(idEleccion);
	vector<Lista> listas;

	for(unsigned int i = 0; i < values.size(); i++){

		Lista* lista = this->GetLista(values[i]);
		listas.push_back(Lista(lista->GetNombre(),lista->GetEleccion()));
	}

	return listas;
}

ABMLista::~ABMLista() {
}

