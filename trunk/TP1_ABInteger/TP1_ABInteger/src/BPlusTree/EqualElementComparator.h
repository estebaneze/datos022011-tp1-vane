#ifndef EQUALELEMENTCOMPARATOR_H_
#define EQUALELEMENTCOMPARATOR_H_


#include "Element.h"
#include <functional>
class EqualElementComparator:public std::binary_function<Element,Element,bool>  {
public:
	EqualElementComparator();
	virtual ~EqualElementComparator();
	bool operator () (const Element& elem,const Element& elem2)const;
};

#endif /* EQUALELEMENTCOMPARATOR_H_ */
