/*
 * directorio.h
 *
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include "Table.h"					//Internal
#include "Bucket.h"						//Internal
#include "HashFunction.h"				//Internal
#include "../Persistencia/PersistorBase.h"	//External
#include "../Persistencia/exceptions/PersistExceptions.h"
#include "../utils/types.h"	//External

#include <vector>
#include <string>

using namespace std;

#define BUFFERTABLE 512
#define LIMIT_TABLE 64


class Directory{

	private:
		PersistorBase* directoryFile;
		PersistorBase* bucketFile;

		Table* tabla;
		Bucket * bucketActual;
		unsigned int depth;
		unsigned int maxBucketSize;
		float insertionSizeLimit;

		void setDepth();
		void duplicarTabla (unsigned int pos,Offset offset);
		void reducirTabla ();
		void replaceTable(Offset,Offset);
		unsigned int buscarPosicionTabla(Key);
		void organizarBuckets(Bucket*);
		void tryCombine(unsigned int);
		void redistribuirTabla(Bucket * auxBucket, unsigned int pos);
		vector<KeyValue> getValue(Offset blockNumber);


	public:
		Directory(string, unsigned int);
		virtual ~Directory();
		void setInsertionSizeLimit(float);
	   	void insert(Key,string);
		bool remove(Key);
		bool modify(Key, string);
		string find(Key);
		void inform();
		ostream& inform (ostream& myOstream);
		ostream& inform (Offset blockNumber, ostream& myOstream);
		void inform(Offset blockNumber);
		bool existKey (Key key);
		//void Log(Key key, string value);

		vector<KeyValue> getAllValues();
};

#endif /* DIRECTORIO_H_ */
