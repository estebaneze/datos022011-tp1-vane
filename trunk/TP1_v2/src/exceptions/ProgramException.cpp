/*
 * ProgramException.cpp
 *
 *  Created on: May 3, 2010
 *      Author: carlos
 */

#include "ProgramException.h"

ProgramException::ProgramException() throw() {

}
ProgramException::ProgramException(string description) throw() {
	this->description=description;

}

ProgramException::~ProgramException() throw() {

}

const char* ProgramException::what() const throw(){
	return this->description.c_str();
}

