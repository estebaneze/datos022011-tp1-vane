/*
 * RSA.h
 *
 *  Created on: 29/11/2011
 *      Author: loo
 */

#ifndef RSA_H_
#define RSA_H_

class RSA {

private:
	//long int p,q,n;

public:
	static char* encriptar(char * m);
	static char* desencriptar(char* c);
};

#endif /* RSA_H_ */
