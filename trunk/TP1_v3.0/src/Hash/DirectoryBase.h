/*
 * directorio.h
 *
 */

#ifndef DIRECTORYBASE_H_
#define DIRECTORYBASE_H_

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


class DirectoryBase{

	protected:

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

		virtual PersistorBase* GetDirectoryFile();
		virtual PersistorBase* GetBucketFile();

	public:
		DirectoryBase(string, unsigned int);
		DirectoryBase();
		virtual ~DirectoryBase();
		virtual void setInsertionSizeLimit(float);
		virtual void insert(Key,string);
		virtual bool remove(Key);
		virtual bool modify(Key, string);
		virtual string find(Key);
		virtual void inform();
		virtual ostream& inform (ostream& myOstream);
		virtual ostream& inform (Offset blockNumber, ostream& myOstream);
		virtual void inform(Offset blockNumber);
		virtual bool existKey (Key key);
		//void Log(Key key, string value);

		virtual vector<KeyValue> getAllValues();
};

#endif /* DIRECTORIOBASE_H_ */
