/*
 * directorio.cpp
 *
 */

#include "Directory.h"
#include "HashExceptions.h"
#include <assert.h>
#include <iostream>
#include <set>
#include <map>
#include "../Logging/Log.h"
#include "../Common/Common.h"

/**
 * Setea el archivo de Directorio y de Buckets
 * */
Directory::Directory(string dirfile, unsigned int maxBucketSize){

	this->depth = 0;
	this->maxBucketSize = maxBucketSize;
	this->insertionSizeLimit = 0.80;

	// Abro o creo los archivos de Tabla y Buckets
	string tmp = dirfile;
	tmp.append(".dir");
	this->directoryFile = new PersistorBase(tmp,BUFFERTABLE);
	this->bucketFile = new PersistorBase(dirfile.append(".bk"),maxBucketSize);

	//Creo instancias de Tabla y Bucket vacios para trabajar.
	this->tabla = new Table();
	this->bucketActual = new Bucket (maxBucketSize);
	this->bucketActual->setInsertionSizeLimit(this->insertionSizeLimit);

	// si no hay bloques en el archivo agrego un bucket vacio.
	if (bucketFile->blocks() == 0)
		bucketFile->add(bucketActual);

	// Inserto la primer posicion en la Tabla
	this->tabla->insert(bucketActual->getOffset(),0,0);
	// si no hay bloques en el archivo agrego el inicio de una nueva Tabla.
	if (directoryFile->blocks() > 0)
		 directoryFile->load(0,tabla);
	else directoryFile->add(tabla);

	this->setDepth();
}

Directory::~Directory(){
	// Borrar instancias de elementos utilizados.
	delete this->directoryFile;
	delete this->bucketFile;
	delete this->tabla;
	delete this->bucketActual;
}

void Directory::setInsertionSizeLimit(float isl)
{
	//Setea el ratio para el tamaño en inserciones
	this->insertionSizeLimit = isl;

	//Actualiza el ratio en el bucket cargado
	this->bucketActual->setInsertionSizeLimit(isl);
}

/**
 * Determina la profuncidad del Directorio a partir
 * de los elementos contenidos en el archivo de Tabla.
 */
void Directory::setDepth(){

	int acumulado = 0;
	unsigned int bloques = this->directoryFile->blocks();

	if ( bloques <2 )
		acumulado = this->tabla->getSize();
	else acumulado = this->tabla->getSize() * bloques;

	int i = 1;
	//Calculo con i cuál es la profundidad
	while (acumulado > i){
		i *= 2;
		this->depth++;
	}
}

/*void Directory::Log(Key key, string value){

	string message = "Inserto (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, "HashOperations.log");
	cout << message << endl;

	//Logueo como queda el arbol
	ofstream logFile;
	logFile.open("HashProcess.log", ios::app);
	this->inform(logFile);
	logFile.close();
}*/

/**
 * Inserta una clave y el numero de bloque al que pertenece
 * Recibe la clave y el numero de bloques
 */
void /*bool*/ Directory::insert (Key key, string value){

	// busco la posicion de la tabla correspondiente a la dispersion.
	unsigned int pos = buscarPosicionTabla(key);

	// obtengo el offset del Bucket correspondiente a esa posicion.
	Offset offset = tabla->getElement(pos);
	// Leo el Bucket
	bucketFile->load(offset,bucketActual);

	try{
		this->bucketActual->insert(key, value);
		bucketFile->modify(bucketActual);
		//this->Log(key, value);

	}catch(HashExceptions::ElementSizeException* e){

		delete e;
		//si no se pudo insertar, es porque no hay espacio,
		Bucket* auxBucket = new Bucket(maxBucketSize);
		auxBucket->setInsertionSizeLimit(this->insertionSizeLimit);

		//Obtendo las profundidades, y los incremento en ambos bloques.
		unsigned int auxDepth = bucketActual->getDepth();
		auxBucket->setDepth(auxDepth+1);
		bucketActual->setDepth(auxDepth+1);
		//cout << "nuevo bloque" << endl;
		bucketFile->add(auxBucket);

		// se duplica la tabla en el caso de tenes profundidades iguales.
		// y se marca la posicion correspondiente con el nuevo bucket
		if (auxDepth == depth)
			duplicarTabla(pos,auxBucket->getOffset());
		else
			// vuelvo a intentar redistribuir la tabla.
			redistribuirTabla(auxBucket, pos);
		// una vez terminada la correccion de la tabla,
		// organizo la información de los buckets.
		organizarBuckets(auxBucket);
		bucketFile->modify(auxBucket);
		bucketFile->modify(bucketActual);
		delete auxBucket;
		insert(key,value);
	}
	//return true;
}

/*
 *	Redistribuye la carga de un bucket una vez que
 *	cambia su profundidad.
 **/
void Directory::organizarBuckets(Bucket* auxBucket){
	std::map<Key, string>::iterator it;
	unsigned int pos = 0;
	Offset offset = 0;
	directoryFile->load(offset,tabla);

	for (it = this->bucketActual->begin() ; it != this->bucketActual->end() ; it++){

		pos = HashFunction::MakeAddress(it->first,this->depth);
		directoryFile->load((pos/ LIMIT_TABLE),tabla);
		offset = tabla->getElement(pos % tabla->getSize());

		if (offset == auxBucket->getOffset()){
			auxBucket->insert(it->first, it->second);
			this->bucketActual->deleteKey(it->first);
		}
	}
}

/**
 * Duplica la tabla de dispersion, y guarda la posicion de offset
 * pasada por parametro en la posicion "pos".
 */
void Directory::duplicarTabla(unsigned int pos,Offset offset){

	int end = this->directoryFile->blocks();
	Table* tempTable = NULL;
	int changePos = pos + (LIMIT_TABLE* tabla->getOffset());
	this->directoryFile->load(0,tabla);
	if (tabla->getSize() < LIMIT_TABLE){
		tabla->duplicate();
		tabla->insert(offset,pos,pos);
		this->directoryFile->modify(tabla);
	}else
		for (Offset block =0 ; block < end ; block++){
			tempTable = new Table();
			this->directoryFile->load(block,tempTable);
			if (((LIMIT_TABLE * block) <= changePos) && (changePos < (LIMIT_TABLE * (block+1)))){
				this->directoryFile->load(block,tabla);
				tabla->insert(offset,pos,pos);
				this->directoryFile->modify(tabla);
			}
			this->directoryFile->add(tempTable);
			delete tempTable;
		}

	//Incremento la profundidad y actualizo el total de celdas
	this->depth ++;
}

/**
 * Redistribuye los offsets de la tabla con el nuevo registro.
 **/
void Directory::redistribuirTabla(Bucket* auxBucket, unsigned int pos){

	unsigned int inter = 1 << auxBucket->getDepth() ;
    unsigned int i = 0;
    Offset offTable = tabla->getOffset();
    unsigned int prePos = pos+(tabla->getSize()*(offTable));
    unsigned int actualPos = pos;
    bool Cicle=false;

    while(!Cicle){
        tabla->insert(auxBucket->getOffset(), actualPos, actualPos);
        directoryFile->modify(tabla);
        for(i = 0;i < inter;i++){
        	if (++actualPos >= tabla->getSize() ){
        		actualPos = 0;
        		if ((unsigned)++offTable >= directoryFile->blocks()) offTable = 0;
        	}
        }
    	Cicle = (actualPos+(tabla->getSize()*(offTable)) == prePos);
    	directoryFile->load(offTable,tabla);
    }
}

/**
 * Reemplaza las posiciones donde se encuentra el offset
 * recibido por parametro al nuevo.
 */
void Directory::replaceTable(Offset oldOffset, Offset newOffset){
	for(unsigned int block = 0 ; block < directoryFile->blocks() ; block++){
		directoryFile->load(block,tabla);
		tabla->replace(oldOffset,newOffset);
		directoryFile->modify(tabla);
	}
}
/*
 * Busca en los Bucket si la clave existe
 * retorna el resultado de la busqueda
 * o tira la excepcion en caso de no encontrar el elemento
 **/
string Directory::find (Key key){

	// busco la posicion de la tabla correspondiente a la dispersion.
	unsigned int pos = buscarPosicionTabla(key);
	// obtengo el offset del Bucket correspondiente a esa posicion.
	Offset offset = tabla->getElement(pos);

	// Leo el Bucket
	bucketFile->load(offset,bucketActual);

	return bucketActual->find(key);
}

/*
 * TRUE si la key existe sno FALSE
 */
bool Directory::existKey (Key key){
	// busco la posicion de la tabla correspondiente a la dispersion.

	unsigned int pos = buscarPosicionTabla(key);
	// obtengo el offset del Bucket correspondiente a esa posicion.
	Offset offset = tabla->getElement(pos);

	// Leo el Bucket
	bucketFile->load(offset,bucketActual);

	return bucketActual->exist(key);
}


/**
 * Elimina una clave del bloque al que pertenece
 * Recibe una clave
 * Devuelve si pudo eliminar o no.
 */
bool Directory::remove (Key key){

	unsigned int pos = this->buscarPosicionTabla(key);
	Offset offset = this->tabla->getElement(pos);

	this->bucketFile->load(offset,this->bucketActual);
	bool temp = false;

	temp = this->bucketActual->deleteKey(key);
	bucketFile->modify(bucketActual);
	if (bucketActual->countElements() == 0){
		tryCombine(pos);
		reducirTabla();
	}

	//Devuelvo el resultado de eliminar la clave
	return temp;
}

/**
 * Intenta organizar la tabla para luego reducirla.
 * Recibe la posicion de la tabla correspondiente al bucket eliminado.
 */
void Directory::tryCombine(unsigned int myPos){

	unsigned int delta = (1 << bucketActual->getDepth())/2;
	Bucket* temp = new Bucket();
	temp->setInsertionSizeLimit(this->insertionSizeLimit);
	directoryFile->load(0,tabla);
	unsigned int sizeTable = tabla->getSize() * directoryFile->blocks();

	unsigned int pos1 = (myPos + delta) % (sizeTable);
	unsigned int pos2 = 0;
	if (myPos > delta)
		pos2 = (myPos - delta) % (sizeTable);
	else pos2 = (sizeTable + myPos - delta) % (sizeTable);

	directoryFile->load((pos1/LIMIT_TABLE),tabla);
	Offset offset1 = tabla->getElement((pos1 % tabla->getSize()));

	directoryFile->load((pos2/LIMIT_TABLE),tabla);
	Offset offset2 = tabla->getElement((pos2 % tabla->getSize()));

	if (offset1 == offset2){
		replaceTable(bucketActual->getOffset(),offset1);
		bucketFile->removeBlock(bucketActual->getOffset());
		bucketFile->load(offset1,temp);
		if (temp->getDepth() > 0)
			temp->setDepth(temp->getDepth()-1);
		bucketFile->modify(temp);
	}
	delete temp;
}

/**
 * Reduce la tabla de ser posible,
 * Se ejecuta esta función tantas veces como sea posible.
 */
void Directory::reducirTabla(){

	unsigned int end = this->directoryFile->blocks();
	unsigned int halfEnd = end / 2;
	bool reduce = true;

	Table auxTable;
	Table secondHalfTable;

	//Cargo el bloque
	this->directoryFile->load(0,&auxTable);

	if (auxTable.getSize() ==1)
		// si solo tengo un elemento no puedo reducir
		reduce = false;
	else if (end < 2){
			//Tengo un solo bloque, entonces solo tengo que mirar éste para ver si

			//Puedo intentar reducir
			reduce = auxTable.reduce();

			//Grabo los cambios
			if (reduce) this->directoryFile->modify(&auxTable);

		} else {
			//Tengo más de 1 bloque, tengo que revisar la tabla

			//Me fijo si un bloque es igual a su homólogo
			for (unsigned int k = 0 ; k < halfEnd && reduce; k++){
				this->directoryFile->load(k,&auxTable);
				this->directoryFile->load(k+halfEnd, &secondHalfTable);
				reduce = (auxTable == secondHalfTable);
			}

			if (reduce){
				//Pude reducir, borro la mitad de la tabla
				for (unsigned int block = halfEnd ; block < end ; block++){
					this->directoryFile->removeBlock(block);
				}
			}
		}

	//decremento la profundidad de la tabla
	if (reduce) {
		this->depth --;
		this->reducirTabla();
	}
}

/**
 * Busca una clave y devuelve el bloque al que está asociado
 * Recibe la clave
 * devuelve el numero de bloque en el archivo de datos
 */
unsigned int Directory::buscarPosicionTabla (Key key){

	Offset offset= 0;
	unsigned int acount= 0;
	int pos = HashFunction::MakeAddress(key,this->depth);

	this->directoryFile->load(offset,this->tabla);
	while (pos >= (++offset * LIMIT_TABLE)){
		acount += LIMIT_TABLE;
		this->directoryFile->load(offset,this->tabla);
	}

	return pos-acount;
}

/**
 * Modifica un elemento buscandolo por su clave,
 * de no encontrarse, devuelve una excepcion.
 */
bool Directory::modify (Key key , string data){

	try
	{
		unsigned int pos = this->buscarPosicionTabla(key);
		Offset offset = this->tabla->getElement(pos);
		this->bucketFile->load(offset,this->bucketActual);

		//Devuelvo el resultado de modificar el registro
		bool modified = this->bucketActual->modify(key, data);
		this->bucketFile->modify(bucketActual);
		if (!modified){
			//No puedo modificar porque no hay espacio
			this->remove(key);
			this->insert(key, data);
		}
	} catch (std::exception* e){
		delete e;
		return false;
	}
	return true;
}


void Directory::inform (Offset blockNumber){

	this->bucketFile->load(blockNumber,this->bucketActual);
	std::cout << "	Bucket "<< blockNumber << ": (" << this->bucketActual->getDepth() << "," << this->bucketActual->countElements() << ")" << endl;
	this->bucketActual->toHuman();
	std::cout << std::endl;

}

ostream& Directory::inform (Offset blockNumber, ostream& myOstream){

	this->bucketFile->load(blockNumber,this->bucketActual);
	myOstream << "		Bucket: "<< blockNumber << " (depth: " << this->bucketActual->getDepth() << ", cantBuckets: " << this->bucketActual->countElements() << ")" << endl;
	this->bucketActual->toHumanLog(myOstream);
	myOstream << std::endl;

	return myOstream;
}

vector<KeyValue> Directory::getValue(Offset blockNumber){

	this->bucketFile->load(blockNumber,this->bucketActual);
	return this->bucketActual->get();
}

vector<KeyValue> Directory::getAllValues(){

	vector<KeyValue> values;
	std::set<Offset> offsets;

	for (Offset block= 0 ; (unsigned)block < this->directoryFile->blocks() ; block++){

		this->directoryFile->load(block,this->tabla);
		this->tabla->toHumanOffsets(&offsets);
	}

	for (std::set<Offset>::iterator it = offsets.begin(); it != offsets.end(); it++){

		vector<KeyValue> vs = this->getValue(*it);	//Valores del bucket actual
		for(int i = 0; i < vs.size(); i++){
			values.push_back(vs[i]);
		}
	}

	return values;

}

ostream& Directory::inform (ostream& myOstream){

	string message = "-Tabla (Profundidad global: ";

	message.append(Helper::IntToString((int)this -> depth));
	message.append(")");

	myOstream << "-Tabla (Profundidad global: " << this->depth << ") " << std::endl;

	std::set<Offset> offsets;
	for (Offset block= 0 ; (unsigned)block < this->directoryFile->blocks() ; block++){

		this->directoryFile->load(block,this->tabla);
	//	this->inform(this->tabla->getOffset(),myOstream);
		this->tabla->toHuman(&offsets, myOstream);
	}

	myOstream << std::endl << std::endl;
	myOstream << "-Buckets : Profundidad, Cantidad de Elementos " << std::endl;
	for (std::set<Offset>::iterator it = offsets.begin(); it != offsets.end(); it++){
		//this->inform(*it);

		this->inform(*it,myOstream);
	}

	myOstream << "=========================================" << std::endl;

	return myOstream;
}

void Directory::inform (){

	string message = "-Tabla (Profundidad global: ";
	message.append(Helper::IntToString((int)this -> depth));
	message.append(")");
	Log::WriteLog(message, "Hash.log");

	std::cout << "-Tabla (Profundidad global: " << this->depth << ") " << std::endl;

	std::set<Offset> offsets;
	for (Offset block= 0 ; (unsigned)block < this->directoryFile->blocks() ; block++){
		this->directoryFile->load(block,this->tabla);
		this->tabla->toHuman(&offsets);
	}
	std::cout << std::endl << std::endl;
	std::cout << "-Buckets : Profundidad, Cantidad de Elementos " << std::endl;
	for (std::set<Offset>::iterator it = offsets.begin(); it != offsets.end(); it++){
		this->inform(*it);
	}
	std::cout << "=========================================" << std::endl;
}
