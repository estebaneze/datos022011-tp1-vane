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
	this->dirFile = new PersistorBase(tmp,BUFFERTABLE);
	this->bktFile = new PersistorBase(dirfile.append(".bk"),maxBucketSize);

	//Creo instancias de Tabla y Bucket vacios para trabajar.
	this->table = new Table();
	this->bucketActual = new Bucket (maxBucketSize);
	this->bucketActual->setInsertionSizeLimit(this->insertionSizeLimit);

	// si no hay bloques en el archivo agrego un bucket vacio.
	if (bktFile->blocks() == 0)
		bktFile->add(bucketActual);

	// Inserto la primer posicion en la Tabla
	this->table->insert(bucketActual->getOffset(),0,0);
	// si no hay bloques en el archivo agrego el inicio de una nueva Tabla.
	if (dirFile->blocks() > 0)
		 dirFile->load(0,table);
	else dirFile->add(table);

	this->setDepth();
}

Directory::~Directory(){
	// Borrar instancias de elementos utilizados.
	delete this->dirFile;
	delete this->bktFile;
	delete this->table;
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
	unsigned int bloques = this->dirFile->blocks();

	if ( bloques <2 )
		acumulado = this->table->getSize();
	else acumulado = this->table->getSize() * bloques;

	int i = 1;
	//Calculo con i cuál es la profundidad
	while (acumulado > i){
		i *= 2;
		this->depth++;
	}
}

/**
 * Inserta una clave y el numero de bloque al que pertenece
 * Recibe la clave y el numero de bloques
 * Devuelve true o false segun si se pudo realizar o no
 */
void /*bool*/ Directory::insert (Key key, string value){

	string message = "Inserto (";
	message.append(key);
	message.append(",");
	message.append(value);
	message.append(")");
	Log::WriteLog(message, "Hash.log");
	cout << message << endl;

	// busco la posicion de la tabla correspondiente a la dispersion.
	unsigned int pos = findPosofTable(key);

	// obtengo el offset del Bucket correspondiente a esa posicion.
	Offset offset = table->getElement(pos);
	// Leo el Bucket
	bktFile->load(offset,bucketActual);

	try{
		this->bucketActual->insert(key, value);
		bktFile->modify(bucketActual);
	}catch(HashExceptions::ElementSizeException* e){
		delete e;
		//si no se pudo insertar, es porque no hay espacio,
		Bucket* auxBucket = new Bucket(maxBucketSize);
		auxBucket->setInsertionSizeLimit(this->insertionSizeLimit);

		//Obtendo las profundidades, y los incremento en ambos bloques.
		unsigned int auxDepth = bucketActual->getDepth();
		auxBucket->setDepth(auxDepth+1);
		bucketActual->setDepth(auxDepth+1);
		bktFile->add(auxBucket);

		// se duplica la tabla en el caso de tenes profundidades iguales.
		// y se marca la posicion correspondiente con el nuevo bucket
		if (auxDepth == depth)
			duplicateTable(pos,auxBucket->getOffset());
		else
			// vuelvo a intentar redistribuir la tabla.
			redistributeTable(auxBucket, pos);
		// una vez terminada la correccion de la tabla,
		// organizo la información de los buckets.
		organizeBuckets(auxBucket);
		bktFile->modify(auxBucket);
		bktFile->modify(bucketActual);
		delete auxBucket;
		insert(key,value);
	}
	//return true;
}

/*
 *	Redistribuye la carga de un bucket una vez que
 *	cambia su profundidad.
 **/
void Directory::organizeBuckets(Bucket* auxBucket){
	std::map<Key, string>::iterator it;
	unsigned int pos = 0;
	Offset offset = 0;
	dirFile->load(offset,table);

	for (it = this->bucketActual->begin() ; it != this->bucketActual->end() ; it++){

		pos = HashFunction::MakeAddress(it->first,this->depth);
		dirFile->load((pos/ LIMIT_TABLE),table);
		offset = table->getElement(pos % table->getSize());

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
void Directory::duplicateTable(unsigned int pos,Offset offset){

	int end = this->dirFile->blocks();
	Table* tempTable = NULL;
	int changePos = pos + (LIMIT_TABLE* table->getOffset());
	this->dirFile->load(0,table);
	if (table->getSize() < LIMIT_TABLE){
		table->duplicate();
		table->insert(offset,pos,pos);
		this->dirFile->modify(table);
	}else
		for (Offset block =0 ; block < end ; block++){
			tempTable = new Table();
			this->dirFile->load(block,tempTable);
			if (((LIMIT_TABLE * block) <= changePos) && (changePos < (LIMIT_TABLE * (block+1)))){
				this->dirFile->load(block,table);
				table->insert(offset,pos,pos);
				this->dirFile->modify(table);
			}
			this->dirFile->add(tempTable);
			delete tempTable;
		}

	//Incremento la profundidad y actualizo el total de celdas
	this->depth ++;
}

/**
 * Redistribuye los offsets de la tabla con el nuevo registro.
 **/
void Directory::redistributeTable(Bucket* auxBucket, unsigned int pos){

	unsigned int inter = 1 << auxBucket->getDepth() ;
    unsigned int i = 0;
    Offset offTable = table->getOffset();
    unsigned int prePos = pos+(table->getSize()*(offTable));
    unsigned int actualPos = pos;
    bool Cicle=false;

    while(!Cicle){
        table->insert(auxBucket->getOffset(), actualPos, actualPos);
        dirFile->modify(table);
        for(i = 0;i < inter;i++){
        	if (++actualPos >= table->getSize() ){
        		actualPos = 0;
        		if ((unsigned)++offTable >= dirFile->blocks()) offTable = 0;
        	}
        }
    	Cicle = (actualPos+(table->getSize()*(offTable)) == prePos);
    	dirFile->load(offTable,table);
    }
}

/**
 * Reemplaza las posiciones donde se encuentra el offset
 * recibido por parametro al nuevo.
 */
void Directory::replaceTable(Offset oldOffset, Offset newOffset){
	for(unsigned int block = 0 ; block < dirFile->blocks() ; block++){
		dirFile->load(block,table);
		table->replace(oldOffset,newOffset);
		dirFile->modify(table);
	}
}
/*
 * Busca en los Bucket si la clave existe
 * retorna el resultado de la busqueda
 * o tira la excepcion en caso de no encontrar el elemento
 **/
string Directory::find (Key key){
	// busco la posicion de la tabla correspondiente a la dispersion.
	unsigned int pos = findPosofTable(key);
	// obtengo el offset del Bucket correspondiente a esa posicion.
	Offset offset = table->getElement(pos);

	// Leo el Bucket
	bktFile->load(offset,bucketActual);

	return bucketActual->find(key);
}

/*
 * TRUE si la key existe sno FALSE
 */
bool Directory::existKey (Key key){
	// busco la posicion de la tabla correspondiente a la dispersion.
	unsigned int pos = findPosofTable(key);
	// obtengo el offset del Bucket correspondiente a esa posicion.
	Offset offset = table->getElement(pos);

	// Leo el Bucket
	bktFile->load(offset,bucketActual);

	return bucketActual->exist(key);
}


/**
 * Elimina una clave del bloque al que pertenece
 * Recibe una clave
 * Devuelve si pudo eliminar o no.
 */
bool Directory::remove (Key key){

	unsigned int pos = this->findPosofTable(key);
	Offset offset = this->table->getElement(pos);

	this->bktFile->load(offset,this->bucketActual);
	bool temp = false;

	temp = this->bucketActual->deleteKey(key);
	bktFile->modify(bucketActual);
	if (bucketActual->countElements() == 0){
		tryCombine(pos);
		reduceTable();
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
	dirFile->load(0,table);
	unsigned int sizeTable = table->getSize() * dirFile->blocks();

	unsigned int pos1 = (myPos + delta) % (sizeTable);
	unsigned int pos2 = 0;
	if (myPos > delta)
		pos2 = (myPos - delta) % (sizeTable);
	else pos2 = (sizeTable + myPos - delta) % (sizeTable);

	dirFile->load((pos1/LIMIT_TABLE),table);
	Offset offset1 = table->getElement((pos1 % table->getSize()));

	dirFile->load((pos2/LIMIT_TABLE),table);
	Offset offset2 = table->getElement((pos2 % table->getSize()));

	if (offset1 == offset2){
		replaceTable(bucketActual->getOffset(),offset1);
		bktFile->removeBlock(bucketActual->getOffset());
		bktFile->load(offset1,temp);
		if (temp->getDepth() > 0)
			temp->setDepth(temp->getDepth()-1);
		bktFile->modify(temp);
	}
	delete temp;
}

/**
 * Reduce la tabla de ser posible,
 * Se ejecuta esta función tantas veces como sea posible.
 */
void Directory::reduceTable(){

	unsigned int end = this->dirFile->blocks();
	unsigned int halfEnd = end / 2;
	bool reduce = true;

	Table auxTable;
	Table secondHalfTable;

	//Cargo el bloque
	this->dirFile->load(0,&auxTable);

	if (auxTable.getSize() ==1)
		// si solo tengo un elemento no puedo reducir
		reduce = false;
	else if (end < 2){
			//Tengo un solo bloque, entonces solo tengo que mirar éste para ver si

			//Puedo intentar reducir
			reduce = auxTable.reduce();

			//Grabo los cambios
			if (reduce) this->dirFile->modify(&auxTable);

		} else {
			//Tengo más de 1 bloque, tengo que revisar la tabla

			//Me fijo si un bloque es igual a su homólogo
			for (unsigned int k = 0 ; k < halfEnd && reduce; k++){
				this->dirFile->load(k,&auxTable);
				this->dirFile->load(k+halfEnd, &secondHalfTable);
				reduce = (auxTable == secondHalfTable);
			}

			if (reduce){
				//Pude reducir, borro la mitad de la tabla
				for (unsigned int block = halfEnd ; block < end ; block++){
					this->dirFile->removeBlock(block);
				}
			}
		}

	//decremento la profundidad de la tabla
	if (reduce) {
		this->depth --;
		this->reduceTable();
	}
}

/**
 * Busca una clave y devuelve el bloque al que está asociado
 * Recibe la clave
 * devuelve el numero de bloque en el archivo de datos
 */
unsigned int Directory::findPosofTable (Key key){

	Offset offset= 0;
	unsigned int acount= 0;
	int pos = HashFunction::MakeAddress(key,this->depth);

	this->dirFile->load(offset,this->table);
	while (pos >= (++offset * LIMIT_TABLE)){
		acount += LIMIT_TABLE;
		this->dirFile->load(offset,this->table);
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
		unsigned int pos = this->findPosofTable(key);
		Offset offset = this->table->getElement(pos);
		this->bktFile->load(offset,this->bucketActual);

		//Devuelvo el resultado de modificar el registro
		bool modified = this->bucketActual->modify(key, data);
		this->bktFile->modify(bucketActual);
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

	this->bktFile->load(blockNumber,this->bucketActual);
	std::cout << "	Bucket "<< blockNumber << ": (" << this->bucketActual->getDepth() << "," << this->bucketActual->countElements() << ")" << endl;
	this->bucketActual->toHuman();
	std::cout << std::endl;

}

vector<KeyValue> Directory::getValue(Offset blockNumber){

	this->bktFile->load(blockNumber,this->bucketActual);
	return this->bucketActual->get();
}

vector<KeyValue> Directory::getAllValues(){

	vector<KeyValue> values;
	std::set<Offset> offsets;

	for (Offset block= 0 ; (unsigned)block < this->dirFile->blocks() ; block++){

		this->dirFile->load(block,this->table);
		this->table->toHuman(&offsets);
	}

	for (std::set<Offset>::iterator it = offsets.begin(); it != offsets.end(); it++){

		vector<KeyValue> vs = this->getValue(*it);	//Valores del bucket actual
		for(int i = 0; i < vs.size(); i++){
			values.push_back(vs[i]);
		}
	}

	return values;

}

void Directory::inform (){

	string message = "-Tabla (Profundidad global: ";
	message.append(Helper::IntToString((int)this -> depth));
	message.append(")");
	Log::WriteLog(message, "Hash.log");

	std::cout << "-Tabla (Profundidad global: " << this->depth << ") " << std::endl;

	std::set<Offset> offsets;
	for (Offset block= 0 ; (unsigned)block < this->dirFile->blocks() ; block++){
		this->dirFile->load(block,this->table);
		this->table->toHuman(&offsets);
	}
	std::cout << std::endl << std::endl;
	std::cout << "-Buckets : Profundidad, Cantidad de Elementos " << std::endl;
	for (std::set<Offset>::iterator it = offsets.begin(); it != offsets.end(); it++){
		this->inform(*it);
	}
	std::cout << "=========================================" << std::endl;
}
