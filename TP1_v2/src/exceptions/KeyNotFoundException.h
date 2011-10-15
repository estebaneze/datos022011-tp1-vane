/*
 * KeyNotFoundException.h
 *
 *  Created on: 01/05/2010
 *      Author: Daniel
 */

#ifndef KEYNOTFOUNDEXCEPTION_H_
#define KEYNOTFOUNDEXCEPTION_H_

#include <exception>

class KeyNotFoundException : std::exception{

public:
	KeyNotFoundException() throw();
	virtual ~KeyNotFoundException() throw();
	const char* what() const throw();
};

#endif /* KEYNOTFOUNDEXCEPTION_H_ */
