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

    this->index = new Index(Helper::concatenar(hashFile,"Lista",ConfigurationMananger::getInstance()->getSeparador2()));
}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
void ABMLista::Add(Lista* lista){

        if (!(this->directorio->existKey(lista->GetNombre()))){

        	this->directorio->insert(lista->GetNombre(),Helper::copyBytesToString(lista->GetEleccion()));

			this->index->AppendToIndex(Helper::copyBytesToString(lista->GetEleccion()), lista->GetNombre());   //Tengo que refrescar el indice en todos los Adds!!!


			//logueo operacion y proceso

			//aca dejo el helepr:inttoString por que es para el log.
			HashLog::LogInsert(lista->GetNombre(),Helper::IntToString(lista->GetEleccion()),ConfigurationMananger::getInstance()->getLogOperListaFile());
			HashLog::LogProcess(this->directorio,ConfigurationMananger::getInstance()->getLogProcessListaFile());

			//Tengo que crear los registros de conteo con la combinacion idLista, idEleccion, idDistrito con 0 votos
			//Busco los distritos de esa eleccion

			ABMConteo conteos = ABMConteo();

			ABMEleccion elecciones = ABMEleccion();

			Eleccion* e = elecciones.GetEleccion(lista->GetEleccion());

			vector<int> distritos = e->GetDistritos();

			for(unsigned int i = 0; i < distritos.size(); i++){
				conteos.Inicializa(lista->GetNombre(), distritos[i], e->GetId());
			}

        }
        else{
                cout << "Ya existe la Lista " << lista->GetNombre() << endl;
        }
}

/**Elimina una lista, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMLista::Delete(Lista *lista){

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
}

/**Modifica el idEleccion de una lista pasada por parametro
* si la encuentra la modifica sino no hace nada
*/
void ABMLista::Modify(Lista *lista){


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
                        string idEleccion = values[i].Value;

                        listas.push_back(Lista(nombre,Helper::copyBytesToInt(idEleccion)));

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

        if ((this->directorio->existKey(nombre))){

                return new Lista(nombre,Helper::copyBytesToInt(directorio->find(nombre)));
        }
        else{
                return NULL;
        }
}

bool ABMLista::existKey(string key){

        return this->directorio->existKey(key);
}

void ABMLista::mostrarListasPorPantalla(){
        this->directorio->inform();
}

vector<Lista> ABMLista::GetListasByEleccion(int idEleccion){

        vector<Key> values = this->index->GetIds(Helper::copyBytesToString(idEleccion));

        vector<Lista> listas;

                for(unsigned int i = 0; i < values.size(); i++){
                        listas.push_back(Lista(values[i],idEleccion));
                }
        return listas;
}

ABMLista::~ABMLista() {
}

