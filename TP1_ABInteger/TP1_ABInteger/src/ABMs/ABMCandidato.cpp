/*
 * ABMCandidato.cpp
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */

#include "ABMCandidato.h"

/*
 * creo el directorio y le paso el nombre del archivo a generar y tamaño de los buckets
 */
ABMCandidato::ABMCandidato() {
        int maxBucketSize = ConfigurationMananger::getInstance()->getHashBSizeCandidato();
        this->hashFile= ConfigurationMananger::getInstance()->getCandidatoFile();
        this->directorio = new Directory(hashFile, maxBucketSize);
}

/**Agrego un candidato, lo guarda en hash con el formato idLista|idVotante|idCargo
 */
int ABMCandidato::Add(string idLista, long idVotante, int idCargo){

        int idCandidato = Identities::GetNextIdCandidato();

        if (!(this->directorio->existKey(Helper::IntToString(idCandidato)))){

                string fields1 = Helper::concatenar(idLista,Helper::LongToString(idVotante),ConfigurationMananger::getInstance()->getSeparador1());
                string fields2 = Helper::concatenar(fields1,Helper::IntToString(idCargo),ConfigurationMananger::getInstance()->getSeparador1());

                this->directorio->insert(Helper::IntToString(idCandidato), fields2);

                HashLog::LogProcess(this->directorio,ConfigurationMananger::getInstance()->getLogProcessCandidatoFile());
                HashLog::LogInsert(Helper::IntToString(idCandidato),fields2,ConfigurationMananger::getInstance()->getLogOperCandidatoFile());

                return idCandidato;
        }

        return -1;
}

/**Elimina una Candidato, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMCandidato::Delete(int idCandidato){

        if (this->directorio->existKey(Helper::IntToString(idCandidato))){
                this->directorio->remove(Helper::IntToString(idCandidato));
                HashLog::LogProcess(this->directorio,"Candidato_HashProccess.log");
                HashLog::LogDelete(Helper::IntToString(idCandidato),"","Candidato_HashOperation.log");
                return true;
        }
        else {
                return false;
        }
}

/**Modifica el idEleccion de una candidato pasada por parametro
* si la encuentra la modifica sino no hace nada
*/
void ABMCandidato::Modify(Candidato *candidato){

        string id = Helper::IntToString(candidato->GetId());
        if (this->directorio->existKey(id)){


                string fields1 = Helper::concatenar(candidato->GetIdLista(),Helper::LongToString(candidato->GetIdVotante()),ConfigurationMananger::getInstance()->getSeparador1());
                string fields2 = Helper::concatenar(fields1,Helper::IntToString(candidato->GetIdCargo()),ConfigurationMananger::getInstance()->getSeparador1());

                HashLog::LogProcess(this->directorio,"Candidato_HashProccess.log");
                HashLog::LogModify(Helper::IntToString(candidato->GetId()),fields2,"Candidato_HashOperation.log");
                /*string fields = Helper::IntToString(candidato.GetIdLista());
                fields.append("|");
                fields.append(Helper::IntToString(candidato.GetIdVotante()));
                fields.append("|");
                fields.append(Helper::IntToString(candidato.GetIdCargo()));*/

                this->directorio->modify(id,fields2);
        }

}

vector<Candidato> ABMCandidato::GetCandidatos(){

        vector<KeyValue> values = this->directorio->getAllValues();
        vector<Candidato> candidatos;

        for(unsigned int i = 0; i < values.size(); i++){

                vector<string> splitedVs = Helper::split(values[i].Value, '|');

                string idLista  = splitedVs[0];
                long idVotante = Helper::StringToLong(splitedVs[1]);
                int idCargo = Helper::StringToInt(splitedVs[2]);
                int idCandidato = Helper::StringToInt(values[i].Key);

                candidatos.push_back(Candidato(idLista, idVotante, idCargo, idCandidato));

        }

        return candidatos;
}

/*
 * Devuelve la candidato si no existe el nombre NULL
 */
Candidato* ABMCandidato::GetCandidato(int idCandidato){

        string candidatoId = Helper::IntToString(idCandidato);

        if ((this->directorio->existKey(candidatoId))){

                string values = directorio->find(candidatoId);
                vector<string> splitedVs = Helper::split(values, '|');

                string idLista  = splitedVs[0];
                long idVotante = Helper::StringToLong(splitedVs[1]);
                int idCargo = Helper::StringToInt(splitedVs[2]);

                return new Candidato(idLista, idVotante, idCargo, idCandidato);
        }
        else {
                return NULL;
        }

}

bool ABMCandidato::Exists(Candidato *candidato){
        return this->directorio->existKey(Helper::IntToString(candidato->GetId()));
}

void ABMCandidato::mostrarCandidatosPorPantalla(){
        this->directorio->inform();
}

ABMCandidato::~ABMCandidato() {
        delete this->directorio;
}
