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

	cout << "Agrego al indice: Key: " << key << " - id Value: " << value << endl;


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




Index::~Index() {
	delete this->directorio;
}
