#include "OverflowException.h"

OverflowException::OverflowException() throw(){

}

OverflowException::OverflowException(string description) throw(){
	this->description=description;
}
OverflowException::~OverflowException() throw(){
}

const char* OverflowException::what() const throw(){
	return this->description.c_str();
}
