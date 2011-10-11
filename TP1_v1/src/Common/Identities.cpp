/*
 * Identities.cpp
 *
 *  Created on: 09/10/2011
 *      Author: minnie
 */

#include "Identities.h"

void Identities::InitializeFile(){

	fstream File;

	File.open("identities.txt", ios::out);

	if (File.is_open ()) {
		File << "Candidato 1" << "\n";
		File << "Cargo 1" << "\n";
		File << "Conteo 1" << "\n";
		File << "Distrito 1" << "\n";
		File << "Eleccions 1" << "\n";
		File << "Lista 1" << "\n";
	}

	File.close();

	cout << "File was properly initialiazed" << endl;
}

void Identities::RefreshFile(string key, int value){

	string line;
	ifstream myfile ("identities.txt");
	std::vector< string > keys;
	std::vector< int > values;

	//Me guardo las lineas con los valores
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			keys.push_back(line);
		}
		myfile.close();
	}

	//Busco la linea que tengo que modificar
	for(int i = 0; i < keys.size(); i++){
		if(keys[i].size() >= (key.size() + 2) && keys[i].substr(0, key.size()) == key){
			string space = " ";
			key.append(space);
			key.append(Helper::IntToString(value));
			keys[i] = key;
		}
	}

	//Reescribo el archivo
	fstream File;
	File.open("identities.txt", ios::out);

	if (File.is_open ()) {
		for(int i = 0; i < keys.size(); i++){
			File << keys[i] << endl;
		}
	}

	File.close();
}

int Identities::GetNextIdCandidato(){
	return Identities::GetNextId("Candidato");
}

int Identities::GetNextIdCargo(){
	return Identities::GetNextId("Cargo");
}

int Identities::GetNextIdDistrito(){
	return Identities::GetNextId("Distrito");
}

int Identities::GetNextId(string key){

	string line;
	ifstream myfile ("identities.txt");
	int id = -1;

	if (myfile.is_open()) {
		while ( myfile.good() )
		{
			getline (myfile,line);
			if(line.size() >= (key.size() + 2) && line.substr(0, key.size()) == key){
				string next = line.substr(key.size() + 1, line.size() - key.size() + 1);
				id = atoi(next.c_str());
			}
		}

		myfile.close();
	}
	else {
		id = -1;
		cout << "Error reading Identities file. File was not properly initialized." << endl;
	}

	if(id == -1){
		cout << "Error reading Identities file. File was not properly initialized." << endl;
	}
	else{
		RefreshFile(key, id + 1);
	}

	return id;

}