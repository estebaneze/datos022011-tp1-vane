#include "EqualElementComparator.h"
EqualElementComparator::EqualElementComparator() {

}

EqualElementComparator::~EqualElementComparator() {
}

bool EqualElementComparator::operator () ( const Element& elem,const Element& elem2) const {
	return elem.getKey()==elem2.getKey();
}
