/*
 * excepciones.h
 *
 *  Created on: 24/09/2009
 *      Author: leonardo
 */

#ifndef EXCEPCIONES_H_
#define EXCEPCIONES_H_

#include "exception"
#include <string>

using namespace std;

namespace except
{
	class ExceptionOutOfRange: public exception{};
	class ExceptionBlockIsFull: public exception{};
	class ExceptionSizeTooBig: public exception{};
	class ExceptionDeseriazationFail: public exception{};
	class ExceptionNotFound: public exception{};
	class ExceptionWriteError: public exception{};
	class ExceptionAlreadyExists: public exception{};
	class ExceptionOperationNotSupported: public exception{};
	class NotFindFreeNodeException: public exception{};
}

#endif /* EXCEPCIONES_H_ */