/*
 * ConteoIndex.cpp
 *
 *  Created on: 16/10/2011
 *      Author: minnie
 */

#include "../Persistencia/exceptions/excepciones.h"
#include "Index.h"

using namespace except;

Index::Index(string filename) {

		this->hashFile = Helper::concatenar(filename,"ix",".");
		this->directorio = new Directory(hashFile,4096);
        string plainFileName = this->hashFile;
        vector<string> splited = Helper::split(this->hashFile,'/');

        if (splited.size() > 0)
        	plainFileName = splited[1];

        this->processLogIx = ConfigurationMananger::getInstance()->getLogDirectory() + plainFileName + "_Process" + "." + "log";
        this->operationLogIx = ConfigurationMananger::getInstance()->getLogDirectory() + plainFileName + "_Operation" + "." + "log";

}
/*
 * busco keys asociado a la data pasada por paramertro
 */
vector<Key> Index::GetIds(Key data){

        if ((this->directorio->existKey(data))){

			string values = directorio->find(data);

			//return Helper::split(values, '|');
			vector<string> keys;
			ProcessData::obtenerData(values,keys);

			return keys;
        }
        else {
			vector<Key> aux;
			return aux;
        }

}

vector<int> Index::GetIdsInt(Key data){

        if ((this->directorio->existKey(data))){

			string values = directorio->find(data);

			//return Helper::split(values, '|');
			vector<int> keys;

			ProcessData::obtenerData(values, keys);
			return keys;
        }
        else {
			vector<int> aux;
			return aux;
        }

}

void Index::RefreshIndex(Key key, vector<Key> values){

        //string fields = Helper::concatenar(values, ConfigurationMananger::getInstance()->getSeparador1());

		string fields = ProcessData::generarData(values);

        if (!(this->directorio->existKey(key))){
            this->directorio->insert(key,fields);
        }
        else{

			//Si ya existe, lo modifico
			string oldFields = this->directorio->find(key);
			string newFields = ProcessData::generarData(oldFields,fields);
			//oldFields.append("|");
			//oldFields.append(fields);
			this->directorio->modify(key, newFields);
        }

}


void Index::AppendToIndex(KeyInt key, Key value){
	this->AppendToIndex(Helper::copyBytesToString(key), value);
}

/*
 * OJO: ESTE TIENE QUE USARSE SOLAMENTE CUANDO SE HACE ADD DE UN NUEVO ELEMENTO.
 * SI SE ESTA MODIFICANDO, TIENE QUE USARSE void AppendToIndex(Key key,Key oldKey, Key value), QUE ACTUALIZA EL INDICE CON EL VALOR QUE TENIA ANTES LA ENTIDAD
 */

void Index::AppendToIndex(Key key, Key value){

        if (!(this->directorio->existKey(key))){
        	this->directorio->insert(key,value);
        }
        else{

            //Si ya existe, lo modifico
            string oldFields = this->directorio->find(key);

            vector<string> actualValues;
            ProcessData::obtenerData(oldFields,actualValues);
            bool founded = false;

            int prox = 0;
            ProcessData::obtenerData(value, prox);

            for(int i = 0; i < actualValues.size() && !founded; i++){
				if(actualValues[i] == value){
					founded = true;
				}
			}

			//Si la lista no esta ya indexada con ese idEleccion, la agrego. Si no, no hago nada.
			if(!founded){
				oldFields.append(value);
				this->directorio->modify(key, oldFields);
			}
		}

        HashLog::LogProcess(this->directorio,this->processLogIx);
		HashLog::LogInsert(key,value,this->operationLogIx);

}

void Index::AppendToIndex(int key, int value){

	string processedId = Helper::copyBytesToString(key);
	string processedData = ProcessData::generarData(value);

	if (!(this->directorio->existKey(processedId))){
		this->directorio->insert(processedId,processedData);
	}
	else{

		//Si ya existe, lo modifico
		string oldData = this->directorio->find(processedId);
		vector<int> actualValues;

		ProcessData::obtenerData(oldData,actualValues);

		bool founded = false;
		for(int i = 0; i < actualValues.size() && !founded; i++){
			if(actualValues[i] == value){
				founded = true;
			}
		}

		//Si la lista no esta ya indexada con ese idEleccion, la agrego. Si no, no hago nada.
		if(!founded){
			actualValues.push_back(value);
			string newData = ProcessData::generarData(actualValues);//[0], value);
			this->directorio->modify(processedId, newData);
		}
	}

	HashLog::LogProcess(this->directorio,this->processLogIx);
	HashLog::LogInsert(processedId,processedData,this->operationLogIx);

}


vector<KeyValue> Index::GetAllValues(){

	return this->directorio->getAllValues();

}

void Index::DeleteFromIndex(KeyInt key, Key value){
                this->DeleteFromIndex(Helper::copyBytesToString(key), value);
}

void Index::DeleteFromIndex(Key key, Key value){

        //cout << "Voy a borrar " << value << endl;

        if ((this->directorio->existKey(key))){

                //Lo busco
                string oldFields = this->directorio->find(key);
                //vector<string> splited = Helper::split(oldFields, '|');
                vector<string> splited;
                ProcessData::obtenerData(oldFields,splited);

                //cout << "Los valores del indice: " << Helper::concatenar(splited, ConfigurationMananger::getInstance()->getSeparador1()) << endl;

                bool founded = false;
                int index = 0;
                for(int i = 0; i < splited.size() && !founded; i++){
                        if(splited[i] == value){
                                index  = i;
                                founded = true;
                        }
                }

                //Borro el "value" del registro de la "key"
                splited.erase(splited.begin() + index);

                //Vuelvo a actualizar el registro con esta clave
                if(founded){
                        cout << "Los valores del indice: " << Helper::concatenar(splited, ConfigurationMananger::getInstance()->getSeparador1()) << endl;
                        //this->directorio->modify(key, Helper::concatenar(splited, ConfigurationMananger::getInstance()->getSeparador1()));
                        this->directorio->modify(key, ProcessData::generarData(splited));
                }

        }
}

void Index::AppendToIndex(KeyInt key,KeyInt oldKey, Key value){
        this->AppendToIndex(Helper::copyBytesToString(key), Helper::copyBytesToString(oldKey), value);
}

void Index::AppendToIndex(Key key,Key oldKey, Key value){

        //cout << "Agrego al indice: Key: " << key << " - id Value: " << value << endl;

        if (!(this->directorio->existKey(key))){
                this->directorio->insert(key,value);
        }
        else{

                //Si ya existe, lo modifico
                string oldFields = this->directorio->find(key);
                //vector<string> splited = Helper::split(oldFields, '|');
                vector<string> splited;
                ProcessData::obtenerData(oldFields,splited);

                bool founded = false;
                for(int i = 0; i < splited.size() && !founded; i++){
                        if(splited[i] == value){
                                founded = true;
                        }
                }

                //Si la lista no esta ya indexada con ese idEleccion, la agrego. Si no, no hago nada.
                if(!founded){
                        string newFields = ProcessData::generarData(oldFields,value);
						//oldFields.append("|");
                        //oldFields.append(value);
                        this->directorio->modify(key, newFields);
                }

        }

        if(oldKey != key){
                //Admeas tengo que sacar este value de la oldKey
                string fieldsOldKey = this->directorio->find(oldKey);
                //vector<string> splitedOldKey = Helper::split(fieldsOldKey, '|');

                vector<string> splitedOldKey;
                ProcessData::obtenerData(fieldsOldKey,splitedOldKey);

                bool founded = false;
                int position = -1;
                for(int i = 0; i < splitedOldKey.size() && !founded; i++){
                        if(splitedOldKey[i] == value){
                                position = i;
                                founded = true;
                        }
                }

                //Si encontre value indezado con la oldKey, lo borro de ese registro
                if(founded){

//                      cout << endl << endl << "La key " << oldKey << " tenia: " << fieldsOldKey << endl;
                        splitedOldKey.erase(splitedOldKey.begin() + position);

                        //fieldsOldKey = Helper::concatenar(splitedOldKey, ConfigurationMananger::getInstance()->getSeparador1());
                        fieldsOldKey = ProcessData::generarData(splitedOldKey);
//                      cout << endl << endl << "La key " << oldKey << " ahora tiene: " << fieldsOldKey << endl;
                        this->directorio->modify(oldKey, fieldsOldKey);
                }

        }

        HashLog::LogProcess(this->directorio,this->processLogIx);
		HashLog::LogInsert(key,value,this->operationLogIx);
}




Index::~Index() {
        delete this->directorio;
}

