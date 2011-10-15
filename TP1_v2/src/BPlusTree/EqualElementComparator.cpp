/*
 * EqualElementComparator.cpp
 *
 *  Created on: Apr 26, 2010
 *      Author: carlos
 */

#include "EqualElementComparator.h"
EqualElementComparator::EqualElementComparator() {

}

EqualElementComparator::~EqualElementComparator() {
}

bool EqualElementComparator::operator () ( const Element& elem,const Element& elem2) const {
	return elem.getKey()==elem2.getKey();
}
