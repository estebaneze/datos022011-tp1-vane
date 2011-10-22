/*
 * Exceptions.h
 *
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>

namespace PersistExceptions{
	class ElementNotFoundException : public std::exception{};
	class FailFileWriteException : public std::exception{};
	class FileNotFoundexception : public std::exception{};
	class FileReadException : public std::exception{};
	class OverFlowException : public std::exception{};
	class NotFindFreeNodeException : public std::exception{};
	class PersistorInitializedException : public std::exception{};
	class PersistorNotInitializedException : public std::exception{};
	class WrongBlockSize : public std::exception{};
}

#endif /* EXCEPTIONS_H_*/
