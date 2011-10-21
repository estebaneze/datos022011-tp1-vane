/*
 * ConteoIndex.cpp
 *
 *  Created on: 16/10/2011
 *      Author: minnie
 */

#include "Index.h"

Index::Index(string filename) {

	this->hashFile = Helper::concatenar(filename,"ix",".");
	this->directorio = new Directory(hashFile,2048);

}

vector<Key> Index::GetIds(Key key){

	if ((this->directorio->existKey(key))){

		string values = directorio->find(key);
		return Helper::split(values, '|');
	}
	else {
		vector<Key> aux;
		return aux;
	}

}

void Index::RefreshIndex(Key key, vector<Key> values){

	string fields = Helper::concatenar(values, "|");

	if (!(this->directorio->existKey(key))){
		this->directorio->insert(key,fields);
	}
	else{

		//Si ya existe, lo modifico
		string oldFields = this->directorio->find(key);
		oldFields.append("|");
		oldFields.append(fields);
		this->directorio->modify(key, oldFields);
	}

}


//Esto tiene un bug: por ejemplo en un Conteo, cuando se le cambia el idEleccion,
//se actualiza el regsitro de esa idEleccion
//pero no se borra el idConteo del registro de idEleccion que tenia
void Index::AppendToIndex(Key key, Key value){

	//cout << "Agrego al indice: Key: " << key << " - id Value: " << value << endl;


	if (!(this->directorio->existKey(key))){
		this->directorio->insert(key,value);
	}
	else{

		//Si ya existe, lo modifico
		string oldFields = this->directorio->find(key);
		vector<string> splited = Helper::split(oldFields, '|');

		bool founded = false;
		for(int i = 0; i < splited.size() && !founded; i++){
			if(splited[i] == value){
				founded = true;
			}
		}

		//Si la lista no esta ya indexada con ese idEleccion, la agrego. Si no, no hago nada.
		if(!founded){
			oldFields.append("|");
			oldFields.append(value);
			this->directorio->modify(key, oldFields);
		}
	}

}

void Index::DeleteFromIndex(Key key, Key value){

	cout << "Voy a borrar " << value << endl;

	if ((this->directorio->existKey(key))){

		//Lo busco
		string oldFields = this->directorio->find(key);
		vector<string> splited = Helper::split(oldFields, '|');

		cout << "Los valores del indice: " << Helper::concatenar(splited, "|") << endl;

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
			cout << "Los valores del indice: " << Helper::concatenar(splited, "|") << endl;
			this->directorio->modify(key, Helper::concatenar(splited, "|"));
		}

	}
}

void Index::AppendToIndex(Key key,Key oldKey, Key value){

	//cout << "Agrego al indice: Key: " << key << " - id Value: " << value << endl;

	if (!(this->directorio->existKey(key))){
		this->directorio->insert(key,value);
	}
	else{

		//Si ya existe, lo modifico
		string oldFields = this->directorio->find(key);
		vector<string> splited = Helper::split(oldFields, '|');

		bool founded = false;
		for(int i = 0; i < splited.size() && !founded; i++){
			if(splited[i] == value){
				founded = true;
			}
		}

		//Si la lista no esta ya indexada con ese idEleccion, la agrego. Si no, no hago nada.
		if(!founded){
			oldFields.append("|");
			oldFields.append(value);
			this->directorio->modify(key, oldFields);
		}

	}

	if(oldKey != key){
		//Admeas tengo que sacar este value de la oldKey
		string fieldsOldKey = this->directorio->find(oldKey);
		vector<string> splitedOldKey = Helper::split(fieldsOldKey, '|');

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

//			cout << endl << endl << "La key " << oldKey << " tenia: " << fieldsOldKey << endl;
			splitedOldKey.erase(splitedOldKey.begin() + position);

			fieldsOldKey = Helper::concatenar(splitedOldKey, "|");

//			cout << endl << endl << "La key " << oldKey << " ahora tiene: " << fieldsOldKey << endl;
			this->directorio->modify(oldKey, fieldsOldKey);
		}

	}
}




Index::~Index() {
	delete this->directorio;
}