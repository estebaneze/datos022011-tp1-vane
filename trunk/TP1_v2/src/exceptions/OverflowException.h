/*
 * OverflowException.h
 *
 *  Created on: May 1, 2010
 *      Author: carlos
 */

#ifndef OVERFLOWEXCEPTION_H_
#define OVERFLOWEXCEPTION_H_
#include <string>
using namespace std;
class OverflowException : std::exception{
private:
	string description;
public:
	OverflowException()throw();
	OverflowException(string desc) throw();
	virtual ~OverflowException() throw();
	const char* what() const throw();
};

#endif /* OVERFLOWEXCEPTION_H_ */
