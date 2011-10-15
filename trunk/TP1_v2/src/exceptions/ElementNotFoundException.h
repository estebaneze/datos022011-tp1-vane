/*
 * ElementNotFoundException.h
 *
 *  Created on: 16/04/2010
 *      Author: daniel
 */

#ifndef ELEMENTNOTFOUNDEXCEPTION_H_
#define ELEMENTNOTFOUNDEXCEPTION_H_

#include <exception>

class ElementNotFoundException : public std::exception {
public:
	ElementNotFoundException() throw();
	virtual ~ElementNotFoundException() throw();
	const char* what() const throw();
};

#endif /* ELEMENTNOTFOUNDEXCEPTION_H_ */
