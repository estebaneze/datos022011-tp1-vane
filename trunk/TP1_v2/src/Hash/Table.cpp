#include "Table.h"

Table::Table() {
	this->buckets.clear();
	this->buckets.push_back(0);
}

Table::~Table() {
	this->buckets.clear();
}

void Table::insert(Offset bucketAddr, int first, int last){
	//Asigno un offset de bloque a un rango de entradas de la tabla
	for(int i=first; i<= last;i++)
		this->buckets[i] = bucketAddr;
}

void Table::duplicate(){
	std::vector<Offset> temporal (this->buckets);

	//Ajusto el tamaño de la tabla actual
	this->buckets.clear();
	this->buckets.resize(temporal.size() * 2,0);

	//Copio los elementos de una tabla a la otra
	for (unsigned int j = 0; j < temporal.size() ; ++j){
		this->buckets[j] = temporal[j];
		this->buckets[temporal.size()+j] = temporal[j];
	}

	//Vacío temporal
	temporal.clear();
}

bool Table::reduce(){

	//Calculo el nuevo tamaño
	unsigned int newSize = this->buckets.size() / 2;

	//Me aseguro que todas las entradas estén habilitadas para colapsar
	for(unsigned int i =0; i < newSize; i++)
		if(this->buckets[i] != this->buckets[newSize+i]) return false;

	std::vector<Offset> temporal (this->buckets);

	this->buckets.clear();
	this->buckets.resize(newSize,0);

	//Copio los elementos a la tabla definitiva
	for (unsigned int j = 0; j < (unsigned)newSize; j++){
		this->buckets[j] = temporal[j];
	}
	temporal.clear();
	return true;
}

unsigned int Table::getSize(){
    //Devuelve el tamaño
	return buckets.size();
}

int Table::getDataSize(){
	//Devuelve el tamaño de los datos serializados
	return 	(sizeof(unsigned int) + sizeof(Offset) + this->buckets.size()*sizeof(Offset));
}

std::string Table::serialize(){
	std::string buffer = "";

	//Serializo la cantidad de elementos
	unsigned int size = this->buckets.size();
	buffer.append((char*)&size,sizeof(unsigned int));

	std::vector<Offset>::iterator it ;

	//Serializo cada uno de los elementos
	for(it = this->buckets.begin(); it < this->buckets.end(); it++){
		buffer.append((char*)&(*it),sizeof(Offset));
	}

	//Devuelvo la cadena serializada
	return buffer;
}

void Table::unserialize(std::string & buffer){

	unsigned int size;
	Offset bucket;

	//Deserializo la cantidad de elementos
	buffer.copy((char*)&size,sizeof(unsigned int));
	buffer.erase(0,sizeof(unsigned int));
	this->buckets.clear();

	//Deserializo cada uno de los elementos
	for(unsigned int i = 0 ; i < size ; i++){
		bucket = 0;
		buffer.copy((char*)&bucket,sizeof(Offset));
		buffer.erase(0,sizeof(Offset));

		this->buckets.push_back(bucket);
	}
}

Offset Table::getElement(int pos){
	//Dada una posición, devuelvo el offset al que apunta
	return this->buckets[pos];
}

void Table::replace(Offset oldOffset, Offset newOffset){
	std::vector<Offset>::iterator it;

	//Recorro el vector de offsets, y donde encuentro oldOffset lo cambio por newOffset
	for ( it = buckets.begin(); it != buckets.end() ; it++){
		if ((*it) == oldOffset){
			*it = newOffset;
		}
	}
}

void Table::getOffsets (std::set<Offset>* offsets){
	std::vector<Offset>::iterator it ;

	//Muestro por pantalla los datos almacenados
	for(it = this->buckets.begin(); it < this->buckets.end(); it++){
		offsets->insert(*it);
	}
}

void Table::toHuman(std::set<Offset>* offsets){

	std::vector<Offset>::iterator it ;

	//Muestro por pantalla los datos almacenados
	for(it = this->buckets.begin(); it < this->buckets.end(); it++){
		offsets->insert(*it);
		std::cout << "  " << (*it);
	}
}

ostream& Table::toHuman(std::set<Offset>* offsets, ostream& myOstream){

	std::vector<Offset>::iterator it ;

	//Muestro por pantalla los datos almacenados
	for(it = this->buckets.begin(); it < this->buckets.end(); it++){
		offsets->insert(*it);
		myOstream << "  " << (*it);
	}

	return myOstream;
}

void Table::toHumanOffsets(std::set<Offset>* offsets){

	std::vector<Offset>::iterator it ;

	for(it = this->buckets.begin(); it < this->buckets.end(); it++){
		offsets->insert(*it);
	}
}

bool Table::operator==(const Table& other) const
{
	//Si no tengo la misma cantidad de elementos, ya se que son distintos
	if (this->buckets.size() != other.buckets.size()) return false;
	bool result = true;

	//Comparo elemento a elemento si son iguales
	for (unsigned int k = 0 ; k < this->buckets.size() && result ; k++){
		result = (this->buckets[k] == other.buckets[k]);
	}
	return result;
}
