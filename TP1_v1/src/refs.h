#ifndef REFS_H
#define REFS_H

#include <vector>
#include <sstream>
#include "Field.h"
/**
	@author asd
*/

using namespace std;

struct ref{
       	long posReg;
    	long posBloq;
    	Field Key;       
       }
       ;
class Refs{	
public:
	vector<ref> vRefs;
    Refs();
    
    Refs(string serRefs);
    
    ~Refs();
    
    string Serialize();   

};

#endif
