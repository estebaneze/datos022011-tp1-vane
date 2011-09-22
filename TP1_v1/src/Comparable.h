#ifndef COMPARABLE_H
#define COMPARABLE_H

#include <iostream>
#include <cstdlib>
#include <string>

#ifndef TYPE_T
#define TYPE_T
typedef enum {INTEGER, REAL, STRING, DATE, CHAR, BOOLEAN, SHORT, LONG} type_t;
#endif

using namespace std;

class Comparable{
	
	private:
		type_t type;
		void * data;
		string str;
        		
	public:
        Comparable();		
	    
        Comparable(std::string &inStr);
		Comparable(float &value);
		Comparable(int &value);
		Comparable(long &value);
		Comparable(short &value);
		Comparable(char &value);
		Comparable(bool &value);
				
				
	   const void * getValue();
	   const string getStr();
	   
	   	~Comparable();				
        							
	
};


#endif

