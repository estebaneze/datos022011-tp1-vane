#include "ElementAlreadyExists.h"

ElementAlreadyExists::ElementAlreadyExists() throw() {

}

ElementAlreadyExists::~ElementAlreadyExists() throw() {
}

const char* ElementAlreadyExists::what() const throw(){
	return "El elemento ya existe.";
}



