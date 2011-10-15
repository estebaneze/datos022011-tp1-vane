/*
 * OperationNotFoundException.h
 *
 *  Created on: Apr 29, 2010
 *      Author: carlos
 */

#ifndef OPERATIONNOTFOUNDEXCEPTION_H_
#define OPERATIONNOTFOUNDEXCEPTION_H_
#include <exception>
class OperationNotFoundException :public std::exception{
public:
	OperationNotFoundException() throw();
	virtual ~OperationNotFoundException() throw();
};

#endif /* OPERATIONNOTFOUNDEXCEPTION_H_ */
