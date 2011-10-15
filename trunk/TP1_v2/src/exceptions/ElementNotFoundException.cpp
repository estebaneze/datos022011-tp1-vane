/*
 * ElementNotFoundException.cpp
 *
 *  Created on: 16/04/2010
 *      Author: daniel
 */

#include "ElementNotFoundException.h"

ElementNotFoundException::ElementNotFoundException() throw() {

}

ElementNotFoundException::~ElementNotFoundException() throw() {
}

const char* ElementNotFoundException::what() const throw(){
	return "No se encontr� el elemento";
}
