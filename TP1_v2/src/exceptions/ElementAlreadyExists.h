/*
 * ElementAlreadyExists.h
 *
 *  Created on: 17/04/2010
 *      Author: Daniel
 */

#ifndef ELEMENTALREADYEXISTS_H_
#define ELEMENTALREADYEXISTS_H_

#include <exception>

class ElementAlreadyExists : std::exception{
public:
	ElementAlreadyExists() throw();
	virtual ~ElementAlreadyExists() throw();
	const char* what() const throw();
};

#endif /* ELEMENTALREADYEXISTS_H_ */
