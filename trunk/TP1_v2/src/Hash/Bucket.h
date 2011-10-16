/*
 * TextIndex.h
 *
 */
#ifndef BUCKET_H_
#define BUCKET_H_

#include "../Persistence/Block.h"
#include "../utils/types.h"
#include "HashExceptions.h"
#include "DistributionTable.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

struct KeyValue{
	string Key;
	string Value;
};


class Bucket:public Block {
protected:
	unsigned int _limit;
	float _insertSizeLimit;
	unsigned int depth;
	map <Key, string> _elements;

	bool insertable(Key ,string);
	bool modificable(string, string);

public:
	Bucket();
	Bucket(unsigned int);
	virtual ~Bucket();
	bool exist (Key);

	void insert (Key , string);
	string find (Key);
	bool deleteKey (Key);
	bool modify (Key, string);

	void setInsertionSizeLimit(float);

	unsigned int countElements();

	string serialize();
	void unserialize(string &buffer);
	int getDataSize();
	void toHuman();

	map <Key, string>::iterator begin(){
		return _elements.begin();
	}
	map <Key, string>::iterator end(){
			return _elements.end();
	}
    unsigned int getDepth() const{return depth; }
    void setDepth(unsigned int depth){this->depth = depth;}

    //Devuelve (clave, valor)
    vector<KeyValue> get();
};

#endif /* BUCKET_H_ */