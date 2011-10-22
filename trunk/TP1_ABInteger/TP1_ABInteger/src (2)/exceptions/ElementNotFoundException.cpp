#include "ElementNotFoundException.h"

ElementNotFoundException::ElementNotFoundException() throw() {

}

ElementNotFoundException::~ElementNotFoundException() throw() {
}

const char* ElementNotFoundException::what() const throw(){
	return "No se encontr� el elemento";
}
