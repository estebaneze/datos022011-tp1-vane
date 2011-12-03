#include "Element.h"
#include "../utils/utiles.h"
#include <iostream>
#include "../Common/Helper.h"
#include "../Common/ProcessData.h"

//**********************************/
// * Constructores de copia
 //**********************************/

 Element::Element(const Element& el){
		key=el.key;
		dataSize=el.dataSize;
		char* dataBuffer = new char[dataSize];
		memcpy(dataBuffer,(char*)el.data,dataSize);

		this->data=dataBuffer;
	}
Element::Element(const Element* el){
		key=el->key;
		dataSize=el->dataSize;
		char* dataBuffer = new char[dataSize];
		memcpy(dataBuffer,(char*)el->data,dataSize);

		this->data=dataBuffer;
}
//**********************************/
// * Fin de Constructores de copia
 //**********************************/

Element::Element() {
	this->key=0;
	this->dataSize=0;
	this->data=NULL;
}
Element::Element(KeyInt key,Data data,DataSize dataSize) {
	this->key  = key;
	this->setData(data,dataSize);
}

Element::~Element() {
	if(data != NULL)
		delete data;
}

void Element::setKey(KeyInt key) {
	this->key = key;
}

KeyInt Element::getKey() const {
	return key;
}

void Element::setData(Data data, DataSize dataSize){
	this->dataSize = dataSize;

	char* dataBuffer = new char[dataSize];
	memcpy(dataBuffer,(char*)data,dataSize);

	this->data = dataBuffer;
}

Data Element::getData() {
	return data;
}

DataSize Element::getElementSize() {
	return dataSize;
}

std::string Element::serialize() {
	std::string buffer = "";

	buffer.append((char*)&key,sizeof(KeyInt));
	buffer.append((char*)&dataSize,sizeof(DataSize));
	buffer.append((char*)data,dataSize);

	return buffer;
}


void Element::unserialize(std::string &buffer) {
	buffer.copy((char*)&key,sizeof(KeyInt));
	buffer.erase(0,sizeof(KeyInt));

	buffer.copy((char*)&dataSize,sizeof(DataSize));
	buffer.erase(0,sizeof(DataSize));

	data = new char[dataSize];

	buffer.copy((char*)data,dataSize);
	buffer.erase(0,dataSize);
}


int Element::getDataSize(){
	return (sizeof(KeyInt) + sizeof(dataSize) + dataSize);
}

ostream& Element::printMe(ostream& myOstream, string dataType){

	string data;
	int key;

	if(this->getData()!=NULL){ //programacion defensiva

		data.append(this->getData(), this->getElementSize());
		key = this->getKey();

		if(dataType == "conteo"){

			int idLista = 0;
			int idDistrito = 0;
			int idEleccion = 0;
			int votos = 0;
			ProcessData::obtenerDataConteo(this->getData(), this->getDataSize(), idLista, idDistrito, idEleccion, votos);
			data = Helper::IntToString(idLista) + "|" + Helper::IntToString(idDistrito) + "|" + Helper::IntToString(idEleccion) + "|" + Helper::IntToString(votos) + "|";
		}
		else if(dataType == "distrito"){

			string nombre;
			nombre.clear();
			ProcessData::obtenerDataDistrito(this->getData(), this->getDataSize(), nombre);
			data = nombre;
		}
		else if(dataType == "eleccion"){

			//fecha|idcargo|distritos
			int fecha, idCargo;
			vector<int> idDistritos;

			ProcessData::obtenerDataEleccion(this->getData(), this->getDataSize(), fecha, idCargo, idDistritos);

			data = Helper::IntToString(fecha) + "|" + Helper::IntToString(idCargo);
			for(int i = 0; i < idDistritos.size(); i++){
				data += "|" + Helper::IntToString(idDistritos[i]);
			}
		}

	}

	myOstream << "Key> " << key << " " << "Data: " << data << " ";

	return myOstream;
}

ostream& operator<<(ostream& myOstream,  Element& elem){

	string data;
	if(elem.getData()!=NULL){ //programacion defensiva
		data.append(elem.getData(),elem.getElementSize());
	}

	myOstream<<"Key> "<<elem.getKey()<<" "<<"Data: "<<data<<" ";

	return myOstream;
}
