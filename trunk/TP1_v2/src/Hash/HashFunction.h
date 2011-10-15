/*
 * HashFunction.h
 *
 */

#ifndef HASHFUNCTION_H_
#define HASHFUNCTION_H_

#include <string>
using namespace std;

class HashFunction {
public:
	HashFunction(){};
	virtual ~HashFunction(){};

	static int Hash (string key);
	static int MakeAddress(string key, unsigned int depth);
	static int MakeAddress(unsigned int key, unsigned int depth);
};

#endif /* HASHFUNCTION_H_ */
