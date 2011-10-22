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

        if (!(this->directorio->existKey(Helper::LongToString(votante->GetDni())))){

                string aux= Helper::concatenar(votante->GetNombreYApellido(),votante->GetClave(),ConfigurationMananger::getInstance()->getSeparador1());
                aux = Helper::concatenar(aux,votante->GetDomicilio(),ConfigurationMananger::getInstance()->getSeparador1());
                aux = Helper::concatenar(aux,Helper::IntToString(votante->GetDistrito()),ConfigurationMananger::getInstance()->getSeparador1());

                //recorro la lista de eleccion y agrego todos los IdEleccion al string aux
//<<<<<<< .mine
                for (unsigned int i=0;i<(votante->GetEleccionesVotadas().size());i++){

                        string idE = Helper::IntToString(votante->GetEleccionesVotadas()[i]);
                        aux = Helper::concatenar(aux, idE,ConfigurationMananger::getInstance()->getSeparador1());
                }
/*=======
                for (unsigned int i=0;i<(votante->GetEleccionesVotadas().GetSize());i++){
                        aux = Helper::concatenar(aux,Helper::IntToString(votante->GetEleccionesVotadas().Get(i)),"|");
>>>>>>> .r74
                }
*/
                this->directorio->insert(Helper::LongToString(votante->GetDni()),aux);

                HashLog::LogProcess(this->directorio,"Votante_HashProcess.log");
                HashLog::LogInsert(Helper::LongToString(votante->GetDni()),aux,"Votante_HashOperation.log");

        }
}

/**Elimina un votante, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMVotante::Delete(Votante *votante){

        if (this->directorio->existKey(Helper::LongToString(votante->GetDni()))){
                this->directorio->remove(Helper::LongToString(votante->GetDni()));

                string aux= Helper::concatenar(votante->GetNombreYApellido(),votante->GetClave(),ConfigurationMananger::getInstance()->getSeparador1());
                                aux = Helper::concatenar(aux,votante->GetDomicilio(),ConfigurationMananger::getInstance()->getSeparador1());
                                aux = Helper::concatenar(aux,Helper::IntToString(votante->GetDistrito()),ConfigurationMananger::getInstance()->getSeparador1());

                HashLog::LogProcess(this->directorio,"Votante_HashProcess.log");
                HashLog::LogDelete(Helper::LongToString(votante->GetDni()),aux,"Votante_HashOperation.log");
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

        if (this->directorio->existKey(Helper::LongToString(votante->GetDni()))){

                //concateno todos los campos de votante para luego guardarlo
                string aux= Helper::concatenar(votante->GetNombreYApellido(),votante->GetClave(),ConfigurationMananger::getInstance()->getSeparador1());
                aux = Helper::concatenar(aux,votante->GetDomicilio(),ConfigurationMananger::getInstance()->getSeparador1());
                aux = Helper::concatenar(aux,Helper::IntToString(votante->GetDistrito()),ConfigurationMananger::getInstance()->getSeparador1());

                //recorro la lista de eleccion y agrego todos los IdEleccion al string aux
//<<<<<<< .mine
                for (unsigned int i=0;i<(votante->GetEleccionesVotadas().size());i++){

                        string idE = Helper::IntToString(votante->GetEleccionesVotadas()[i]);
                        aux = Helper::concatenar(aux,idE,ConfigurationMananger::getInstance()->getSeparador1());
                }
                        /*=======
                for (unsigned int i=0;i<(votante->GetEleccionesVotadas().GetSize());i++){
                        aux = Helper::concatenar(aux,Helper::IntToString(votante->GetEleccionesVotadas().Get(i)),"|");
>>>>>>> .r74
                }
*/
                this->directorio->modify(Helper::LongToString(votante->GetDni()),aux);


                HashLog::LogProcess(this->directorio,"Votante_HashProcess.log");
                HashLog::LogModify(Helper::LongToString(votante->GetDni()),aux,"Votante_HashOperation.log");
        }

}
/*
 * Devuelve un vector con los votantes sin las listas de elecciones
 * habria que implementar otro metodo en VOTANTE para obtener sus listas
 * ya qyue en el constructor se inicia con una lista vacia
 *
 *TODO: levantar la lista de elecciones en las que ya voto
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
                        //TODO:"Falta agregar la lista de elecciones en las que voto " 
                        votantes.push_back(Votante(_dni, _nombreYApellido, _clave, _domicilio, _idDistrito));

                }

                return votantes;
}

/*
 * Devuelve votante sin su lista de elecciones, si no existe el nombre NULL
 * TODO:Falta agregar la lista de elecciones en las que voto
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
        // TODO Auto-generated destructor stub
}
