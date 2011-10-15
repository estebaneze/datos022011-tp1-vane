/*
 * ProgramException.h
 *
 *  Created on: May 3, 2010
 *      Author: carlos
 */

#ifndef PROGRAMEXCEPTION_H_
#define PROGRAMEXCEPTION_H_

#include <exception>
#include <string>

using namespace std;
class ProgramException : public std::exception{
private:
	std::string description;
public:
	ProgramException() throw();
	ProgramException(string description) throw();
	virtual ~ProgramException() throw();
	const char* what() const throw();
};

#endif /* PROGRAMEXCEPTION_H_ */
