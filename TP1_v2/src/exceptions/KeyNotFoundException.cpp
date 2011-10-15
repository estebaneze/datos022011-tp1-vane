/*
 * KeyNotFoundException.cpp
 *
 *  Created on: 01/05/2010
 *      Author: Daniel
 */

#include "KeyNotFoundException.h"

KeyNotFoundException::KeyNotFoundException() throw(){
}

KeyNotFoundException::~KeyNotFoundException() throw(){
}

const char* KeyNotFoundException::what() const throw(){
	return "No se encuentra la clave";
}
