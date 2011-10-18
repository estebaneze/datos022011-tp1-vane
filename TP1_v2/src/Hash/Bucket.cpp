/*
 * TextIndex.cpp
 *
 */
#include "Bucket.h"

/* Constructor */
Bucket::Bucket(){
	Bucket(0);
}

/* Constructor Sobrecargado de Bucket::Bucket(). */
Bucket::Bucket(unsigned int limite){
	this->_elements.clear();
	this->_limit = limite;
	this->setInsertionSizeLimit(1.0);
	this->depth = 0;
}

/* Destructor */
Bucket::~Bucket(){
	this->_elements.clear();
}

/* Cantidad de Elementos en el Bucket */
unsigned int Bucket::countElements(){
	return this->_elements.size();
}

/** Setea la capacidad de carga del bucket */
void Bucket::setInsertionSizeLimit(float isl){
	this->_insertSizeLimit = isl;
}

/**
 * Define la capacidad modificar un elemento.
 **/
bool Bucket::modificable (string oldData, string newData){

	// obtengo el tamanio de los elementos actuales.
	unsigned int tam = this->getDataSize();

	// le sumo la diferencia del nuevo tamaño.
	int delta = newData.size() - oldData.size();
	tam += delta;

	// si el elemento supera la capacidad de carga lanzo excepcion
	unsigned int BlockSize = newData.size() + oldData.size() + (4*sizeof(unsigned int));
	if (this->_limit < BlockSize) throw new HashExceptions::ExtendedSizeException();

	return (tam < this->_limit);
}

/**
 * Define la capacidad insertar un elemento.
 **/
bool Bucket::insertable(Key key, string value){

	// obtengo el tamanio de los elementos actuales.
	unsigned int tam = this->getDataSize();
	tam += key.size() + value.size() + (2 * sizeof(int));

	// le sumo el nuevo elemento. junto con la capacidad de carga.
	unsigned int limit = ((float) this->_limit) * this->_insertSizeLimit;
	if (this->_insertSizeLimit > 1) limit = this->_limit;

	unsigned int BlockSize = key.size() + value.size() + (5*sizeof(int));
	// si el elemento supera la capacidad de carga lanzo excepcion
	if (limit < BlockSize) throw new HashExceptions::ExtendedSizeException();
	return (((float)tam) <= limit);
}

/**
 * Inserta un nuevo elemento, retorna es estado de esta operacion
 */
void Bucket::insert (Key key, string value){

	// si existe detiene la operacion
	if (this->exist(key)) throw new HashExceptions::ElementAlreadyExistsException();

	// si no es insertable, corto el proceso.
	if (! this->insertable(key, value)) throw new HashExceptions::ElementSizeException();

	// de poder hacerlo inserto el elemento.
	this->_elements.insert ( pair <Key, string>(key, value));
}

/**
 * Busca una clave en el bucket, y retorna la palabra de encontrarla,
 * o lanza una excepcion.
 */
string Bucket::find (Key key){

	if (this->exist(key)) return this->_elements.find(key)->second;
	throw new HashExceptions::ElementNotFoundException();
}

/**
 * Elimina un elemento del bucket, devolviendo el estado de la operacion.
 */
bool Bucket::deleteKey (Key key){

	// si no existe detiene la operacion
	if (!this->exist(key)) throw new HashExceptions::ElementNotFoundException();

	return (bool)(this->_elements.erase(key) != 0);
}

/**
 * Determina si la clave buscada se encuentra en el bucket.
 */
bool Bucket::exist (Key key){
	return (bool)(this->_elements.end() != this->_elements.find(key));
}


/**
 * Modifica el elemento definido por la key recibida por parametro.
 */
bool Bucket::modify (Key key, string data){

	// si no existe detiene la operacion
	if (!this->exist(key)) throw new HashExceptions::ElementNotFoundException();

	//Obtengo el valor actual
	string oldData = this->_elements.find(key)->second;

	if (this->modificable(oldData, data)){
		// como hay espacio, cambio el valor.
		this->_elements[key]=data;
		return true;
	}
	return false;
}

/**
 * Serializa el bucket para persistirlo en disco.
 */
std::string Bucket::serialize(){
	string buffer = "";
	buffer.append((char*)&_limit,sizeof(unsigned int));
	buffer.append((char*)&depth,sizeof(unsigned int));

	int size = this->_elements.size();
	buffer.append((char*)&size,sizeof(int));

	map<Key, string>::iterator it;

	for(it = this->_elements.begin(); it != this->_elements.end() ; it++){
		Key tempKey = it->first;
		std::string tempString = it->second;

		size = tempKey.size();
		buffer.append((char*)&size,sizeof(int));
		buffer.append(tempKey.c_str(),size);

		size = tempString.size();
		buffer.append((char*)&size,sizeof(int));
		buffer.append(tempString.c_str(),size);
	}

	return buffer;
}

/**
 * Deserializa el bucket que se levanto de disco.
 */
void Bucket::unserialize(std::string & buffer){

	buffer.copy((char*)&_limit,sizeof(unsigned int));
	buffer.erase(0,sizeof(unsigned int));
	buffer.copy((char*)&depth,sizeof(unsigned int));
	buffer.erase(0,sizeof(unsigned int));

	this->_elements.clear();
	int size = 0;
	buffer.copy((char*)&size,sizeof(int));
	buffer.erase(0,sizeof(int));

	for(int it = 0; it < size ; it++){
		int tempSize = 0;
		buffer.copy((char*)&tempSize,sizeof(int));
		buffer.erase(0,sizeof(int));

		Data tempData = new char[tempSize];
		buffer.copy(tempData,tempSize);
		buffer.erase(0,tempSize);

		Key tempInt = "";
		tempInt.append(tempData,tempSize);
		delete[] tempData;

		tempSize = 0;
		buffer.copy((char*)&tempSize,sizeof(int));
		buffer.erase(0,sizeof(int));

		tempData = new char[tempSize];
		buffer.copy(tempData,tempSize);
		buffer.erase(0,tempSize);

		std::string tempString = "";
		tempString.append(tempData,tempSize);
		delete[] tempData;
		this->_elements.insert ( pair <Key, string>(tempInt, tempString));
	}
}

/**
 * Calcula el tamaño del bucket actual.
 */
int Bucket::getDataSize(){
	int interSize = 0;
	for (map<Key, string>::iterator it = this->_elements.begin() ; it != this->_elements.end() ; it++)
		interSize += it->first.size() + it->second.size() + (2 * sizeof(int));

	return interSize + (3 * sizeof(unsigned int));
}

/**
 * Presenta en pantalla la estructura del bucket.
 */
void Bucket::toHuman(){

	//DistributionTable dt;
	for (map<Key, string>::iterator it = this->_elements.begin() ; it != this->_elements.end() ; ++it){
		//dt.unserialize(it->second);
		std::cout << it->first << " => " << it->second << std::endl; /*<< dt.toHuman() << std::endl;*/
	//	dt.clear();
		//std::cout << it->first << " ";
	}
}

void Bucket::toHumanLog(ostream &myOstream){

	//DistributionTable dt;
	for (map<Key, string>::iterator it = this->_elements.begin() ; it != this->_elements.end() ; ++it){
		//dt.unserialize(it->second);
		myOstream << "			"<<it->first << " : " << it->second << std::endl; /*<< dt.toHuman() << std::endl;*/
	//	dt.clear();
		//std::cout << it->first << " ";
	}
}

vector<KeyValue> Bucket::get(){

	vector<KeyValue> values;
	KeyValue value;

	for (map<Key, string>::iterator it = this->_elements.begin() ; it != this->_elements.end() ; ++it){
		value.Key = it->first;
		value.Value = it->second;

		values.push_back(value);
	}

	return values;
}
