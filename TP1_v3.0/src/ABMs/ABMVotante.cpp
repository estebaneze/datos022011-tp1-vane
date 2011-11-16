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
ABMVotante::ABMVotante() {
        int maxBucketSize = ConfigurationMananger::getInstance()->getHashBSizeVotante();
		this->file = ConfigurationMananger::getInstance()->getVotanteFile();
        this->directorio = new Directory(file, maxBucketSize);
}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
void ABMVotante::Add(Votante* votante){

        if (!(this->directorio->existKey(Helper::copyBytesToString(votante->GetDni())))){

                string data = ProcessData::generarData(votante->GetNombreYApellido(),votante->GetClave(),votante->GetDomicilio(),votante->GetDistrito(),votante->GetEleccionesVotadas());

                this->directorio->insert(Helper::copyBytesToString(votante->GetDni()),data);


                //LOGUEO
                string aux= Helper::concatenar(votante->GetNombreYApellido(),votante->GetClave(),ConfigurationMananger::getInstance()->getSeparador1());
                aux = Helper::concatenar(aux,votante->GetDomicilio(),ConfigurationMananger::getInstance()->getSeparador1());
                aux = Helper::concatenar(aux,Helper::IntToString(votante->GetDistrito()),ConfigurationMananger::getInstance()->getSeparador1());

                //recorro la lista de eleccion y agrego todos los IdEleccion al string aux
                for (unsigned int i=0;i<(votante->GetEleccionesVotadas().size());i++){
                        string idE = Helper::IntToString(votante->GetEleccionesVotadas()[i]);
                        aux = Helper::concatenar(aux, idE,ConfigurationMananger::getInstance()->getSeparador1());
                }

                HashLog::LogProcess(this->directorio,ConfigurationMananger::getInstance()->getLogProcessVotanteFile());
                HashLog::LogInsert(Helper::LongToString(votante->GetDni()),aux,ConfigurationMananger::getInstance()->getLogOperVotanteFile());

        }
}

/**Elimina un votante, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMVotante::Delete(Votante *votante){

        if (this->directorio->existKey(Helper::copyBytesToString(votante->GetDni()))){

        	this->directorio->remove(Helper::copyBytesToString(votante->GetDni()));

        	//LOGUEO
            string aux= Helper::concatenar(votante->GetNombreYApellido(),votante->GetClave(),ConfigurationMananger::getInstance()->getSeparador1());
            aux = Helper::concatenar(aux,votante->GetDomicilio(),ConfigurationMananger::getInstance()->getSeparador1());
            aux = Helper::concatenar(aux,Helper::IntToString(votante->GetDistrito()),ConfigurationMananger::getInstance()->getSeparador1());

            HashLog::LogProcess(this->directorio,ConfigurationMananger::getInstance()->getLogProcessVotanteFile());
            HashLog::LogDelete(Helper::LongToString(votante->GetDni()),aux,ConfigurationMananger::getInstance()->getLogOperVotanteFile());
            return true;
        }
        else{
                return false;
        }
}

/**Modifica votante pasado por parametro
* si la encuentra la modifica sino no hace nada
*/
void ABMVotante::Modify(Votante *votante){

        if (this->directorio->existKey(Helper::copyBytesToString(votante->GetDni()))){

        	string data = ProcessData::generarData(votante->GetNombreYApellido(),votante->GetClave(),votante->GetDomicilio(),votante->GetDistrito(),votante->GetEleccionesVotadas());
        	this->directorio->modify(Helper::copyBytesToString(votante->GetDni()),data);

        	//LOGUEO

        	//concateno todos los campos de votante para luego guardarlo
            string aux= Helper::concatenar(votante->GetNombreYApellido(),votante->GetClave(),ConfigurationMananger::getInstance()->getSeparador1());
            aux = Helper::concatenar(aux,votante->GetDomicilio(),ConfigurationMananger::getInstance()->getSeparador1());
            aux = Helper::concatenar(aux,Helper::IntToString(votante->GetDistrito()),ConfigurationMananger::getInstance()->getSeparador1());

            //recorro la lista de eleccion y agrego todos los IdEleccion al string aux
            for (unsigned int i=0;i<(votante->GetEleccionesVotadas().size());i++){
            	string idE = Helper::IntToString(votante->GetEleccionesVotadas()[i]);
                aux = Helper::concatenar(aux,idE,ConfigurationMananger::getInstance()->getSeparador1());
            }

            HashLog::LogProcess(this->directorio,ConfigurationMananger::getInstance()->getLogProcessVotanteFile());
            HashLog::LogModify(Helper::LongToString(votante->GetDni()),aux,ConfigurationMananger::getInstance()->getLogOperVotanteFile());
        }
}
/*
 * Devuelve un vector con los votantes sin las listas de elecciones
 * habria que implementar otro metodo en VOTANTE para obtener sus listas
 * ya qyue en el constructor se inicia con una lista vacia
 *
 */
vector<Votante*> ABMVotante::GetVotantes(){

        vector<KeyValue> values = this->directorio->getAllValues();
        vector<Votante*> votantes;

        //IntegerList _listaElecciones;

                for(unsigned int i = 0; i < values.size(); i++){

                	string nombreYApellido;
                	string clave;
                	string domicilio;
                	int idDistrito = 0;
                	vector<int> listaElecciones;

                	long dni = Helper::copyBytesToLong(values[i].Key);

                	ProcessData::obtenerData(values[i].Value,nombreYApellido,clave,domicilio,idDistrito,listaElecciones);
                	//vector<string> splitedVs = Helper::split(values[i].Value, '|');

                	votantes.push_back(new Votante(dni, nombreYApellido, clave, domicilio, idDistrito));
                }

                return votantes;
}

/*
 * Devuelve votante sin su lista de elecciones, si no existe el nombre NULL
 *
 */
Votante* ABMVotante::GetVotante(long dni){

        if ((this->directorio->existKey(Helper::LongToString(dni)))){

                string values = directorio->find(Helper::LongToString(dni));

                vector<string> splitedVs = Helper::split(values, '|');

                string _nombreYApellido  = splitedVs[0];
                string _clave = splitedVs[1];
                string _domicilio = splitedVs[2];
                int _idDistrito = Helper::StringToInt(splitedVs[3]);

                Votante* votante = new Votante(dni, _nombreYApellido, _clave, _domicilio, _idDistrito);

                //El reso de los valores spliteados son las elcciones en las que voto
                for (unsigned int j=4; j < splitedVs.size() ;j++){
                        votante->AgregarEleccion(Helper::StringToInt(splitedVs[j]));
                }

                return votante;
        }
        else {
                return NULL;
        }
}

bool ABMVotante::existKey(long dni){
        return this->directorio->existKey(Helper::LongToString(dni));
}

//muestrp key (dni) y resto de los elementos todos concatenados
void ABMVotante::mostrarVotantesPorPantalla(){
        this->directorio->inform();
}


ABMVotante::~ABMVotante() {

}
