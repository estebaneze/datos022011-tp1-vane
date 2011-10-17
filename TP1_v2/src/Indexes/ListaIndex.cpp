/*
 * Index.cpp
 *
 *  Created on: 16/10/2011
 *      Author: minnie
 */

#include "ListaIndex.h"

ListaIndex::ListaIndex(string filename) {

	this->hashFile = filename;
	this->directorio = new Directory(hashFile,2048);
}

ListaIndex::~ListaIndex() {
	delete this->directorio;
}

/*
 * Pisa el valor del indice con "listas"
 */
void ListaIndex::RefreshIndexLista(int idEleccion, vector<string> listas){

	string key = Helper::IntToString(idEleccion);
	string fields = Helper::concatenar(listas, "|");

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

/*	string line;
	ifstream myfile (this->_filename);
	std::vector< string > lines;
	std::vector< int > values;

	//Me guardo las lineas con los valores
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			lines.push_back(line);
		}
		myfile.close();
	}

	bool updated = false;
	//Busco la linea que tengo que modificar
	for(int i = 0; i < lines.size(); i++){

		//Los valores estan guardados como: idEleccion|lista1|lista2|lista3|....
		vector<string> splited = Helper::split(lines[i], '|');

		//Si encuentro la eleccion que estoy buscando,
		if(splited.size() > 0 && splited[0] == Helper::IntToString(idEleccion)){
			lines[i].append("|");
			lines[i].append(Helper::concatenar(listas, "|"));	//Le agrego al final las listas
			updated = true;
		}
	}

	//Si no la encontre en el archivo, la agrego al final
	if(!updated){
		string newLine = Helper::IntToString(idEleccion);
		newLine.append("|");
		newLine.append(Helper::concatenar(listas, "|"));
		lines.push_back(newLine);
	}

	//Reescribo el archivo
	fstream File;
	File.open(this->_filename, ios::out);

	if (File.is_open ()) {
		for(int i = 0; i < lines.size(); i++){
			File << lines[i] << endl;;
		}
	}

	File.close();
*/

}

//Esto tiene un bug: cuando se le cambia el idEleccion a la lista, se actualiza el regsitro de esa idEleccion
//pero no se borra la lista del registro de la idEleccion que tenia
void ListaIndex::AppendListaToIndex(int idEleccion, string lista){

	string key = Helper::IntToString(idEleccion);

	if (!(this->directorio->existKey(key))){
		this->directorio->insert(key,lista);
	}
	else{

		//Si ya existe, lo modifico
		string oldFields = this->directorio->find(key);
		vector<string> splited = Helper::split(oldFields, '|');

		bool founded = false;
		for(int i = 0; i < splited.size() && !founded; i++){
			if(splited[i] == lista){
				founded = true;
			}
		}

		//Si la lista no esta ya indexada con ese idEleccion, la agrego. Si no, no hago nada.
		if(!founded){
			oldFields.append("|");
			oldFields.append(lista);
			this->directorio->modify(key, oldFields);
		}
	}

	/*
	string line;
	ifstream myfile (this->_filename);
	std::vector< string > lines;
	std::vector< int > values;

	//Me guardo las lineas con los valores
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			lines.push_back(line);
		}
		myfile.close();
	}

	bool updated = false;

	//Busco la linea que tengo que modificar
	for(int i = 0; i < lines.size(); i++){

		//Los valores estan guardados como: idEleccion|lista1|lista2|lista3|....
		vector<string> splited = Helper::split(lines[i], '|');

		//Si encuentro la eleccion que estoy buscando,
		if(splited.size() > 0 && splited[0] == Helper::IntToString(idEleccion)){
			lines[i].append("|");
			lines[i].append(lista);	//Le agrego al final las listas
			updated = true;
		}
	}

	//Si no la encontre en el archivo, la agrego al final
	if(!updated){
		string newLine = Helper::IntToString(idEleccion);
		newLine.append("|");
		newLine.append(lista);
		lines.push_back(newLine);
	}

	//Reescribo el archivo
	fstream File;
	File.open(this->_filename, ios::out);

	if (File.is_open ()) {
		for(int i = 0; i < lines.size(); i++){
			File << lines[i] << endl;
		}
	}

	File.close();

*/
}


vector<Lista> ListaIndex::GetListasByIdEleccion(int idEleccion){

	string key = Helper::IntToString(idEleccion);
	vector<Lista> listas;

	if ((this->directorio->existKey(key))){

		string values = directorio->find(key);
		vector<string> splitedVs = Helper::split(values, '|');

		for(int i = 0; i < splitedVs.size(); i++){
			Lista l = Lista(splitedVs[i], idEleccion);
			listas.push_back(l);
		}

		return listas;
	}
	else {
		return listas;
	}

	/*
	string line;
	ifstream myfile (this->_filename);
	vector<Lista> listas;

	//Me guardo las lineas con los valores
	if (myfile.is_open()) {

		while ( myfile.good() ) {

			getline (myfile,line);

			//Los valores estan guardados como: idEleccion|lista1|lista2|lista3|....
			vector<string> splited = Helper::split(line, '|');

			//Si encuentro la eleccion que estoy buscando, y tiene listas asignadas (splited.size() > 1, podria no tener)
			if(splited.size() > 0 && splited[0] == Helper::IntToString(idEleccion)&& splited.size() > 1){

				//Recorro los demas valores spliteados, que son las listas de esta eleccion
				for(int i = 1; i < splited.size(); i++){
					Lista lista = Lista(splited[i], idEleccion);
					listas.push_back(lista);
				}
			}
		}

		myfile.close();
	}

	return listas;
	*/
}
