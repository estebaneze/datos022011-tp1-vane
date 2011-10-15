/*
 * HashExceptions.h
 *
 */
#ifndef HASHEXCEPTIONS_H_
#define HASHEXCEPTIONS_H_

#include <exception>

namespace HashExceptions{
	class ElementNotFoundException : public std::exception{};
	class ElementAlreadyExistsException : public std::exception{};
	class ElementSizeException : public std::exception{};
	class ExtendedSizeException : public std::exception{};
}

#endif /* HASHEXCEPTIONS_H_ */
