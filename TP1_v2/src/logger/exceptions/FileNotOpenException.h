/*
 * FileNotFoundexception.h
 *
 *  Created on: 06/04/2010
 *      Author: sergio
 */

#ifndef FILENOTOPENEXCEPTION_H_
#define FILENOTOPENEXCEPTION_H_

#include <exception>

class FileNotOpenException : public std::exception {
public:
	FileNotOpenException() throw();
	virtual ~FileNotOpenException() throw();
	const char* what() const throw();
};

#endif /* FILENOTOPENEXCEPTION_H_ */
