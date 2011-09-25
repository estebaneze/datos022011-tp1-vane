#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <memory.h>

#ifndef TYPE_T
#define TYPE_T
typedef enum {FNULL,INTEGER, REAL, STRING, DATE, CHAR, BOOLEAN, SHORT, LONG} type_t;
#endif


using namespace std;

class Field{
	
	private:
		type_t type;
		void * data;
		string str;		
	public:
        Field();				
		Field(type_t Type, string &indata);
		
		Field(type_t inType,void * indata);
		
		Field(std::string &inStr);
		Field(float &value);
		Field(int &value);
		Field(long &value);
		Field(short &value);
		Field(char &value);
		Field(bool &value);
		Field(const Field& toCopy);
		
	   	~Field();		
		
        							
		Field& operator = (const Field &asignando);		
		
        const void * getValue();
        const std::string getStr();
        const type_t getType();
		
		const bool operator < ( Field &comparador);
		const bool operator < ( float &comparador);
		const bool operator < ( int &comparador);
		const bool operator < ( char &comparador);
		const bool operator < ( bool &comparador);
		const bool operator < ( std::string &comparador);
		const bool operator < ( short &comparador);
		const bool operator < ( long &comparador);
		
  	    const bool operator > ( Field &comparador);
  		const bool operator > ( float &comparador);
  		const bool operator > ( int &comparador);
  		const bool operator > ( char &comparador);
  		const bool operator > ( bool &comparador);
  		const bool operator > ( std::string &comparador);
  		const bool operator > ( short &comparador);
  		const bool operator > ( long &comparador);
  		
  		const bool operator == ( Field &comparador);
  		const bool operator == ( float &comparador);
  		const bool operator == ( int &comparador);
  		const bool operator == ( char &comparador);
  		const bool operator == ( bool &comparador);
  		const bool operator == ( std::string &comparador);
  		const bool operator == ( short &comparador);
  		const bool operator == ( long &comparador);
  		
  		const bool operator != ( Field &comparador);
  		const bool operator != ( float &comparador);
  		const bool operator != ( int &comparador);
  		const bool operator != ( char &comparador);
  		const bool operator != ( bool &comparador);
  		const bool operator != ( std::string &comparador);
  		const bool operator != ( short &comparador);
  		const bool operator != ( long &comparador);
  		
  		const bool operator <= ( Field &comparador);
  		const bool operator <= ( float &comparador);
  		const bool operator <= ( int &comparador);
  		const bool operator <= ( char &comparador);
  		const bool operator <= ( bool &comparador);
  		const bool operator <= ( std::string &comparador);
  		const bool operator <= ( short &comparador);
  		const bool operator <= ( long &comparador);
  		
  		const bool operator >= ( Field &comparador);
  		const bool operator >= ( float &comparador);
  		const bool operator >= ( int &comparador);
  		const bool operator >= ( char &comparador);
  		const bool operator >= ( bool &comparador);
  		const bool operator >= ( std::string &comparador);
  		const bool operator >= ( short &comparador);
  		const bool operator >= ( long &comparador);
        	
		const int toInt();
		
		std::string Serialize();
		void DesSerialize(std::string);
};


#endif

