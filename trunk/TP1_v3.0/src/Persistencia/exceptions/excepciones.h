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
	class BloqueAdministradorNoPotenciaDeDosBytesException: public exception{};
	class BloqueVotanteNoPotenciaDeDosBytesException: public exception{};
}

#endif /* EXCEPCIONES_H_ */
