/*
 * ABMCandidato.cpp
 *
 *  Created on: 10/10/2011
 *      Author: minnie
 */

#include "ABMCandidato.h"


/*
ABMCandidato::ABMCandidato(string hashFile) {
	this->_hashFile = hashFile;
	HashExtensible hashTable = HashExtensible(hashFile);
	this->_hashTable = hashTable;
}*/

/*ABMCandidato::ABMCandidato(string hashFile){
	this->_hashFile = hashFile;
	this->_hashTable = HashExtensible(this->_hashFile);
}

ABMCandidato::~ABMCandidato() {

}

void ABMCandidato::Add(Candidato candidato){



	Key_Node keyNode = Key_Node();
	int idCandidato = 34;//candidato.GetId();
	Field candidatoField = Field(idCandidato);

	Refs refs = Refs();
	//Creo el Ref
	ref auxRef;
	//auxRef.posBloq = 1;
	//auxRef.posReg = 1;
	auxRef.Key = candidatoField;

	refs.vRefs.push_back(auxRef);	//Agrego el "auxRef2" al vector de refs de R.

	keyNode.AddField(candidatoField);

	this->_hashTable.add(keyNode, refs);
	this->_hashTable.save();
	cout << "Candidato agregado: " << endl;
	keyNode.Print();
	cout  << "----------------" << endl;
}

void ABMCandidato::Delete(Candidato candidato){

}

Candidato ABMCandidato::GetCandidato(int idCandidato){

	Key_Node keyNode = Key_Node();

	Field candidatoField = Field(idCandidato);
	keyNode.AddField(candidatoField);

	//bool existe = this->_hashTable.contains(keyNode);
	//if(existe){
	//_hashTable.load();
		Refs* values2 = this->_hashTable.get(keyNode);
		vector<ref> values = values2->vRefs;
		if(values.size() > 0){
			for(int i = 0; i < values.size(); i++){

				cout << "sdsdsdsd" << values[i].Key.toInt() << endl;
			}
		}
	//}

	if(values.size() > 0){
		Candidato c = Candidato(values[0].Key.toInt(), 1, 1);
		return c;
	}

	return Candidato(2,2,2);
}

vector<Candidato> ABMCandidato::GetCandidatos(){

}
*/
