/*
 * ConteoIndex.cpp
 *
 *  Created on: 16/10/2011
 *      Author: minnie
 */

#include "Index.h"

Index::Index(string filename) {

	this->hashFile = filename;
	this->directorio = new Directory(hashFile,2048);

}

vector<int> Index::GetIds(int idKey){

	string key = Helper::IntToString(idKey);
	vector<int> ids;

	if ((this->directorio->existKey(key))){

		string values = directorio->find(key);
		vector<string> splitedVs = Helper::split(values, '|');

		for(int i = 0; i < splitedVs.size(); i++){
			ids.push_back(Helper::StringToInt(splitedVs[i]));
		}

		return ids;
	}
	else {
		return ids;
	}

}

void Index::RefreshIndex(int idKey, vector<int> idsValues){

	string key = Helper::IntToString(idKey);
	string fields = Helper::concatenar(idsValues, "|");

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

void Index::AppendToIndex(int idKey, int idValue){

	cout << "Agrego al indice: Key: " << idKey << " - id Value: " << idValue << endl;

	string key = Helper::IntToString(idKey);
	string field = Helper::IntToString(idValue);

	if (!(this->directorio->existKey(key))){
		this->directorio->insert(key,field);
	}
	else{

		//Si ya existe, lo modifico
		string oldFields = this->directorio->find(key);
		vector<string> splited = Helper::split(oldFields, '|');

		bool founded = false;
		for(int i = 0; i < splited.size() && !founded; i++){
			if(splited[i] == field){
				founded = true;
			}
		}

		//Si la lista no esta ya indexada con ese idEleccion, la agrego. Si no, no hago nada.
		if(!founded){
			oldFields.append("|");
			oldFields.append(field);
			this->directorio->modify(key, oldFields);
		}
	}

}




Index::~Index() {
	delete this->directorio;
}
