#include "Field.h"
#include <iostream>
 #include <sstream>
 
/*CONSTRUCTORES */

Field::Field()
{
     type=FNULL;
     data=NULL;             
}

Field::Field(const Field& toCopy)
{    
     
     type= toCopy.type;
    
     switch (type){
              case INTEGER:
                           data = malloc(sizeof(int));
                            memcpy(data,toCopy.data,sizeof(int));                  
                           break;
              case REAL:
                           data = malloc(sizeof(float));
                           memcpy(data,toCopy.data,sizeof(float));  
                           break;
              case STRING:
                           data=NULL;
                           str= toCopy.str;
                           break;
              case DATE:
                           data=NULL;
                           str= toCopy.str;
                           break;
              case CHAR:
                            data = malloc(sizeof(char));
                           memcpy(data,toCopy.data,sizeof(char));  
                           break;
              case BOOLEAN:
                            data = malloc(sizeof(bool));
                           memcpy(data,toCopy.data,sizeof(bool));  
                           break;
              case SHORT:
                           data = malloc(sizeof(short));
                           memcpy(data,toCopy.data,sizeof(short));  
                           break;
              case LONG:
                           data = malloc(sizeof(long));
                           memcpy(data,toCopy.data,sizeof(long));  
                           break;
                       
              } 
                                          
}

Field& Field::operator = (const Field &toCopy){
	 type= toCopy.type;

     switch (toCopy.type){
            case INTEGER:
                            data = malloc(sizeof(int));
                            memcpy(data,toCopy.data,sizeof(int));   
                           break;
              case REAL:
                           data = malloc(sizeof(float));
                           memcpy(data,toCopy.data,sizeof(float));  
                           break;
              case STRING:

                          data=NULL;
                           str= toCopy.str;
                           break;
              case DATE:
                           data=NULL;
                           str= toCopy.str;
                           break;
              case CHAR:
                            data = malloc(sizeof(char));
                           memcpy(data,toCopy.data,sizeof(char));  
                           break;
              case BOOLEAN:
                            data = malloc(sizeof(bool));
                           memcpy(data,toCopy.data,sizeof(bool));  
                           break;
              case SHORT:
                           data = malloc(sizeof(short));
                           memcpy(data,toCopy.data,sizeof(short));  
                           break;
              case LONG:
                           data = malloc(sizeof(long));
                           memcpy(data,toCopy.data,sizeof(long));  
                           break;                                              
              }           
	return (*this);
}



Field::Field(type_t inType,string &indata)
{
    istringstream in(indata);   
   this->type= inType;
   switch (type){
            case INTEGER:
                            data = malloc(sizeof(int));
                           in >> (*((int*)data)); 
                           break;
              case REAL:
                           data = malloc(sizeof(float));
                          in >> (*((float*)data)); 
                           break;
              case STRING:

                          data=NULL;
                           str= indata;
                           break;
              case DATE:
                           data=NULL;
                           str= indata;
                           break;
              case CHAR:
                            data = malloc(sizeof(char));
                           in >> (*((char*)data));
                           break;
              case BOOLEAN:
                            data = malloc(sizeof(bool));
                          in >> (*((bool*)data));
                           break;
              case SHORT:
                           data = malloc(sizeof(short));
                          in >> (*((short*)data)); 
                           break;
              case LONG:
                           data = malloc(sizeof(long));
                          in >> (*((long*)data));
                           break;                                              
              }           
}




Field::Field(type_t inType,void * indata)
{
   this->type= inType;
   switch (type){
            case INTEGER:
                            data = malloc(sizeof(int));
                            memcpy(data,indata,sizeof(int));   
                           break;
              case REAL:
                           data = malloc(sizeof(float));
                           memcpy(data,indata,sizeof(float));  
                           break;
              case STRING:

                          data=NULL;
                          // str= indata;
                           break;
              case DATE:
                           data=NULL;
                          // str= indata;
                           break;
              case CHAR:
                            data = malloc(sizeof(char));
                           memcpy(data,indata,sizeof(char));  
                           break;
              case BOOLEAN:
                            data = malloc(sizeof(bool));
                           memcpy(data,indata,sizeof(bool));  
                           break;
              case SHORT:
                           data = malloc(sizeof(short));
                           memcpy(data,indata,sizeof(short));  
                           break;
              case LONG:
                           data = malloc(sizeof(long));
                           memcpy(data,indata,sizeof(long));  
                           break;                                              
              }           
}

Field::Field(std::string &inStr)
{
 this->type= STRING;
 this->data = NULL;
 str = inStr;
}

Field::Field(float &value)
{
 this->type = REAL;
 int i =sizeof(value);
 data = malloc(sizeof(value));
 memcpy(data,&value,sizeof(value));
}

Field::Field(int &value)
{
 this->type= INTEGER;
 int i =sizeof(int);
 data = malloc(sizeof(value));
 memcpy(data,&value,sizeof(value));
 i = *(int*)data;
}
Field::Field(char &value)
{
 this->type= CHAR;
 data = malloc(sizeof(value));
 *((char*)data)= value;
}
Field::Field(bool &value)
{
 this->type= BOOLEAN;
 data = malloc(sizeof(value));
 *((bool*)data)= value;
}
Field::Field(short &value)
{
 this->type= SHORT;
 data = malloc(sizeof(value));
 *((short*)data)= value;
}
Field::Field(long &value)
{
 this->type= LONG;
 data = malloc(sizeof(value));
 *((long*)data)= value;
}


Field::~Field()
{
  free(data);
  str.clear();
}

const void * Field::getValue()
{
    return data;   
}

const std::string Field::getStr()
{
    return str;   
}

const type_t Field::getType()
{
    return type;   
}


/* OPERADOR <*/
const bool Field::operator < ( Field &comparador){
       bool result=false;
        if( type==comparador.type)
       switch (type){
              case INTEGER:
                           result =(*((int*)data) < (*((int*)comparador.data))); 
                           break;
              case REAL:
                   result =(*((float*)data) < (*((float*)comparador.data)));
                           break;
              case STRING:
                   result =str <comparador.str;
                           break;
              case DATE:
                  result =str <comparador.str;
                           break;
              case CHAR:
                   result =(*((char*)data) < (*((char*)comparador.data)));
                           break;
              case BOOLEAN:
                   result =(*((bool*)data) < (*((bool*)comparador.data)));
                           break;
              case SHORT:
                   result =(*((short*)data) < (*((short*)comparador.data)));
                           break;
              case LONG:
                   result =(*((long*)data) < (*((long*)comparador.data)));
                           break;
                       
              }
       
                        	 
       return result;
     
}

const bool Field::operator < ( float &comparador){
       return (*((float*)data) < comparador); 
}
const bool Field::operator < ( int &comparador){
       return (*((int*)data) < comparador); 
}
const bool Field::operator < ( char &comparador){
            return (*((char*)data) < comparador); 
}
const bool Field::operator < ( bool &comparador){
       return (*((bool*)data) < comparador); 
}
const bool Field::operator < ( short &comparador){;
       return (*((short*)data)< comparador); 
}
const bool Field::operator < ( long &comparador){
       return (*((long*)data) < comparador); 
}
const bool Field::operator < ( std::string &comparador){
       return (this->str < comparador); 
}



/* OPERADOR >*/
const bool Field::operator > ( Field &comparador){
       bool result=false;
        if( type==comparador.type)
       switch (comparador.type){
              case INTEGER:
                           result =(*((int*)data) > (*((int*)comparador.data))); 
                           break;
              case REAL:
                   result =(*((float*)data) > (*((float*)comparador.data)));
                           break;
              case STRING:
                   result =str >comparador.str;
                           break;
              case DATE:
                  result =str >comparador.str;
                           break;
              case CHAR:
                   result =(*((char*)data) > (*((char*)comparador.data)));
                           break;
              case BOOLEAN:
                   result =(*((bool*)data) > (*((bool*)comparador.data)));
                           break;
              case SHORT:
                   result =(*((short*)data) > (*((short*)comparador.data)));
                           break;
              case LONG:
                   result =(*((long*)data) > (*((long*)comparador.data)));
                           break;
                       
              }
       
                        	 
       return result;
     
}

const bool Field::operator > ( float &comparador){
       return (*((float*)data) > comparador); 
}
const bool Field::operator > ( int &comparador){
       return (*((int*)data) > comparador); 
}
const bool Field::operator > ( char &comparador){
            return (*((char*)data) > comparador); 
}
const bool Field::operator > ( bool &comparador){
       return (*((bool*)data) > comparador); 
}
const bool Field::operator > ( short &comparador){;
       return (*((short*)data)> comparador); 
}
const bool Field::operator > ( long &comparador){
       return (*((long*)data) > comparador); 
}
const bool Field::operator > ( std::string &comparador){
       return (this->str > comparador); 
}

/* OPERADOR ==*/
const bool Field::operator == ( Field &comparador){
       bool result=false;
        if( type==comparador.type)
       switch (comparador.type){
              case INTEGER:
                           result =(*((int*)data) == (*((int*)comparador.data))); 
                           break;
              case REAL:
                   result =(*((float*)data) == (*((float*)comparador.data)));
                           break;
              case STRING:
                   result =str ==comparador.str;
                           break;
              case DATE:
                  result =str ==comparador.str;
                           break;
              case CHAR:
                   result =(*((char*)data) == (*((char*)comparador.data)));
                           break;
              case BOOLEAN:
                   result =(*((bool*)data) == (*((bool*)comparador.data)));
                           break;
              case SHORT:
                   result =(*((short*)data) == (*((short*)comparador.data)));
                           break;
              case LONG:
                   result =(*((long*)data) == (*((long*)comparador.data)));
                           break;
                       
              }
       
                        	 
       return result;
     
}

const bool Field::operator == ( float &comparador){
       return (*((float*)data) == comparador); 
}
const bool Field::operator == ( int &comparador){
       return (*((int*)data) == comparador); 
}
const bool Field::operator == ( char &comparador){
            return (*((char*)data) == comparador); 
}
const bool Field::operator == ( bool &comparador){
       return (*((bool*)data) == comparador); 
}
const bool Field::operator == ( short &comparador){;
       return (*((short*)data)== comparador); 
}
const bool Field::operator == ( long &comparador){
       return (*((long*)data) == comparador); 
}
const bool Field::operator == ( std::string &comparador){
       return (this->str == comparador); 
}



/* OPERADOR !=*/
const bool Field::operator != ( Field &comparador){
       bool result=false;

       if( this->type==comparador.type)
       switch (comparador.type){
              case INTEGER:
                            result =(*((int*)data) != (*((int*)comparador.data)));
                           break;
              case REAL:
                           result =(*((float*)data) != (*((float*)comparador.data)));
                           break;
              case STRING:
                           result =(str !=comparador.str);
                           break;
                           
              case DATE:
                           result =!(str !=comparador.str);
                           break;
              case CHAR:
                   result =(*((char*)data) != (*((char*)comparador.data)));
                           break;
              case BOOLEAN:
                   result =(*((bool*)data) != (*((bool*)comparador.data)));
                           break;
              case SHORT:
                   result =(*((short*)data) != (*((short*)comparador.data)));
                           break;
              case LONG:
                   result =(*((long*)data) != (*((long*)comparador.data)));
                           break;
                       
              }
                        	 
       return result;
     
}

const bool Field::operator != ( float &comparador){
       return (*((float*)data) != comparador); 
}
const bool Field::operator != ( int &comparador){
       return (*((int*)data) != comparador); 
}
const bool Field::operator != ( char &comparador){
            return (*((char*)data) != comparador); 
}
const bool Field::operator != ( bool &comparador){
       return (*((bool*)data) != comparador); 
}
const bool Field::operator != ( short &comparador){;
       return (*((short*)data)!= comparador); 
}
const bool Field::operator != ( long &comparador){
       return (*((long*)data) != comparador); 
}
const bool Field::operator != ( std::string &comparador){
       return (this->str != comparador); 
}


/* OPERADOR <=*/
const bool Field::operator <= ( Field &comparador){
       bool result=false;
        if( type==comparador.type)
       switch (comparador.type){
              case INTEGER:
                           result =(*((int*)data) <= (*((int*)comparador.data))); 
                           break;
              case REAL:
                   result =(*((float*)data) <= (*((float*)comparador.data)));
                           break;
              case STRING:
                   result =str <=comparador.str;
                           break;
              case DATE:
                  result =str <=comparador.str;
                           break;
              case CHAR:
                   result =(*((char*)data) <= (*((char*)comparador.data)));
                           break;
              case BOOLEAN:
                   result =(*((bool*)data) <= (*((bool*)comparador.data)));
                           break;
              case SHORT:
                   result =(*((short*)data) <= (*((short*)comparador.data)));
                           break;
              case LONG:
                   result =(*((long*)data) <= (*((long*)comparador.data)));
                           break;
                       
              }
       
                        	 
       return result;
     
}

const bool Field::operator <= ( float &comparador){
       return (*((float*)data) <= comparador); 
}
const bool Field::operator <= ( int &comparador){
       return (*((int*)data) <= comparador); 
}
const bool Field::operator <= ( char &comparador){
            return (*((char*)data) <= comparador); 
}
const bool Field::operator <= ( bool &comparador){
       return (*((bool*)data) <= comparador); 
}
const bool Field::operator <= ( short &comparador){;
       return (*((short*)data)<= comparador); 
}
const bool Field::operator <= ( long &comparador){
       return (*((long*)data) <= comparador); 
}
const bool Field::operator <= ( std::string &comparador){
       return (this->str <= comparador); 
}

/* OPERADOR >=*/
const bool Field::operator >= ( Field &comparador){
       bool result=false;
       if( type==comparador.type)
       switch (type){
              case INTEGER:
                           result =(*((int*)data) >= (*((int*)comparador.data))); 
                           break;
              case REAL:
                         result =(*((float*)data) >= (*((float*)comparador.data)));
                           break;
              case STRING:
                           result =str >=comparador.str;
                           break;
              case DATE:
                           result =str >=comparador.str;
                           break;
              case CHAR:
                         result =(*((char*)data) >= (*((char*)comparador.data)));
                           break;
              case BOOLEAN:
                             result =(*((bool*)data) >= (*((bool*)comparador.data)));
                           break;
              case SHORT:
                           result =(*((short*)data) >= (*((short*)comparador.data)));
                           break;
              case LONG:
                          result =(*((long*)data) >= (*((long*)comparador.data)));
                           break;
                       
              }
       
                        	 
       return result;
     
}

const bool Field::operator >= ( float &comparador){
       return (*((float*)data) >= comparador); 
}
const bool Field::operator >= ( int &comparador){
       return (*((int*)data) >= comparador); 
}
const bool Field::operator >= ( char &comparador){
            return (*((char*)data) >= comparador); 
}
const bool Field::operator >= ( bool &comparador){
       return (*((bool*)data) >= comparador); 
}
const bool Field::operator >= ( short &comparador){;
       return (*((short*)data)>= comparador); 
}
const bool Field::operator >= ( long &comparador){
       return (*((long*)data) >= comparador); 
}
const bool Field::operator >= ( std::string &comparador){
       return (this->str >= comparador); 
}



const int Field::toInt()
{
     int toReturn = 0;    
       if 
       ((this->type==INTEGER)||(this->type==CHAR)||(this->type==BOOLEAN)||(this->type==SHORT)||(this->type==LONG))
          toReturn= *(int *) data;
          
        if ((this->type==STRING)||(this->type==DATE)){
                	for (unsigned int i= 0; i < str.length(); i++)
                		toReturn += (int) str[i];                                                                     
        }                            	 
	return toReturn; 
}

std::string Field::Serialize(){
            
            if( type==FNULL)
                return "";
            
            std::string aux;
	    std::stringstream ss;
           std::stringstream ss2;
	   ss2 << (int)this->type;         
            aux.append(ss2.str());
            aux.append(",");
            aux.append(str);
            aux.append(","); 
            
		ss.clear();
            switch (type){
              case INTEGER:
                           {
                           ss << (*((int*)data));
                           aux.append(ss.str());
                           break;
                           }
              case REAL:
                           ss << (*((float*)data));
                           aux.append(ss.str());

                           break;

              case CHAR:
                           ss << (*((char*)data));
                           aux.append(ss.str());
                           break;
              case BOOLEAN:
                           ss << (*((bool*)data));
                           aux.append(ss.str());
                           break;
              case SHORT:
                           ss << (*((short*)data));
                           aux.append(ss.str());
                           break;
              case LONG:
                           ss << (*((long*)data));
                           aux.append(ss.str());
                           break;
                       
              }

            
            return aux;
            
}

void Field::DesSerialize(std::string instr){
       string aux;
       
        if(instr.size()==0)
        {
            data=NULL;
            type=FNULL;
            return;
                               
        }
        
       size_t found1;
       size_t found2;
		
       aux=instr.substr(0,1);
  
       this->type=(type_t)atoi(aux.c_str()); 
        
       found1=instr.find(",");
       found2=instr.find_last_of(",");
       aux=instr.substr(found1+1,found2-2);
       this->str=aux;
       
       found2=instr.find_last_of(",");
        aux=instr.substr(found2+1);
       // this->Value=(double)atoi(aux.c_str());
        
        float input2;
                     
       istringstream in(aux);
        
            switch (type){
              case INTEGER:
                           data = malloc(sizeof(int));
                           in >> (*((int*)data));
                           break;
                           
              case REAL:
                           data = malloc(sizeof(float));
                           in >> (*((float*)data));

                           break;
             
              case CHAR:
                           data = malloc(sizeof(char));
                           in >> (*((char*)data));
                           break;
              case BOOLEAN:
                           data = malloc(sizeof(bool));
                           in >> (*((bool*)data));
                           break;
              case SHORT:
                         data = malloc(sizeof(short));
                           in >> (*((short*)data));
                           break;
              case LONG:
                           data = malloc(sizeof(long));
                           in >> (*((long*)data));
                           break;
                       
              }

           //         
        
}
