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
ABMCandidato::ABMCandidato(string hashFile) {

	this->hashFile= hashFile;
	this->directorio = new Directory(hashFile,2048);

	//Descomentar esto si quiere verse el contenido del archivo por pantalla
	//this->directorio->inform();

	// OJO! el tamaño lo tioene que leer desde un archivo de configuracion


}

/**Agrego un candidato, lo guarda en hash con el formato idLista|idVotante|idCargo
 */
void ABMCandidato::Add(int idLista, int idVotante, int idCargo){

	int idCandidato = Identities::GetNextIdCandidato();

	if (!(this->directorio->existKey(Helper::IntToString(idCandidato)))){

		string fields1 = Helper::concatenar(Helper::IntToString(idLista),Helper::IntToString(idVotante),"|");
		string fields2 = Helper::concatenar(fields1,Helper::IntToString(idCargo),"|");

		/*
		string fields = Helper::IntToString(idLista);
		fields.append("|");
		fields.append(Helper::IntToString(idVotante));
		fields.append("|");
		fields.append(Helper::IntToString(idCargo));*/

		this->directorio->insert(Helper::IntToString(idCandidato), fields2);
	}
}

/**Elimina una Candidato, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMCandidato::Delete(int idCandidato){

	if (this->directorio->existKey(Helper::IntToString(idCandidato))){
		return (this->directorio->remove(Helper::IntToString(idCandidato)));
	}
	else {
		return false;
	}
}

/**Modifica el idEleccion de una candidato pasada por parametro
* si la encuentra la modifica sino no hace nada
*/
void ABMCandidato::Modify(Candidato candidato){

	string id = Helper::IntToString(candidato.GetId());
	if (this->directorio->existKey(id)){


		string fields1 = Helper::concatenar(Helper::IntToString(candidato.GetIdLista()),Helper::IntToString(candidato.GetIdVotante()),"|");
		string fields2 = Helper::concatenar(fields1,Helper::IntToString(candidato.GetIdCargo()),"|");

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

		int idLista  = Helper::StringToInt(splitedVs[0]);
		int idVotante = Helper::StringToInt(splitedVs[1]);
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

		int idLista  = Helper::StringToInt(splitedVs[0]);
		int idVotante = Helper::StringToInt(splitedVs[1]);
		int idCargo = Helper::StringToInt(splitedVs[2]);

		return new Candidato(idLista, idVotante, idCargo, idCandidato);
	}
	else {
		return NULL;
	}

}

bool ABMCandidato::Exists(Candidato candidato){
	return this->directorio->existKey(Helper::IntToString(candidato.GetId()));
}

void ABMCandidato::mostrarCandidatosPorPantalla(){
	this->directorio->inform();
}

ABMCandidato::~ABMCandidato() {
	delete this->directorio;
}


