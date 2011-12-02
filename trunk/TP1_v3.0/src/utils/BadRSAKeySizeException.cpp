/*
 * BadRSAKeySizeException.cpp
 *
 *  Created on: 01/12/2011
 *      Author: minnie
 */

#include "BadRSAKeySizeException.h"

BadRSAKeySizeException::BadRSAKeySizeException() throw() {

}

BadRSAKeySizeException::~BadRSAKeySizeException() throw() {
}

const char* BadRSAKeySizeException::what() const throw(){
	return "El valor del parametro tamClaveRSA es incorrecto.";
}
