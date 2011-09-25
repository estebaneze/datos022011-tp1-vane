
#include "Comparable.h"
#include <iostream>
 #include <sstream>
 
/*CONSTRUCTORES */

Comparable::Comparable()
{
                  
}

Comparable::Comparable(std::string &inStr)
{
 this->type= STRING;
 this->data = NULL;
 str = inStr;

}

Comparable::Comparable(float &value)
{
 type = REAL;
 data = malloc(sizeof(value));
 *((float*)data)= value;
}

Comparable::Comparable(int &value)
{
 type= INTEGER;
 data = malloc(sizeof(value));
 *((int*)data)= value;
}
Comparable::Comparable(char &value)
{
 type= CHAR;
 data = malloc(sizeof(value));
 *((char*)data)= value;
}
Comparable::Comparable(bool &value)
{
 type= BOOLEAN;
 data = malloc(sizeof(value));
 *((bool*)data)= value;
}
Comparable::Comparable(short &value)
{
 type= SHORT;
  data = malloc(sizeof(value));
 *((short*)data)= value;
}
Comparable::Comparable(long &value)
{
 type= LONG;
  data = malloc(sizeof(value));
 *((long*)data)= value;
}


const void * Comparable::getValue()
{
  return  data;       
}

const string Comparable::getStr()
{
  return  str;       
}

Comparable::~Comparable()
{
                  
}
