/*
 * BadRSAKeySizeException.h
 *
 *  Created on: 01/12/2011
 *      Author: minnie
 */

#ifndef BADRSAKEYSIZEEXCEPTION_H_
#define BADRSAKEYSIZEEXCEPTION_H_

#include <exception>

class BadRSAKeySizeException : std::exception{
public:
	BadRSAKeySizeException() throw();
	virtual ~BadRSAKeySizeException() throw();
	const char* what() const throw();
};

#endif /* BADRSAKEYSIZEEXCEPTION_H_ */
