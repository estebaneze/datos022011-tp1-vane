#include "refs.h"

Refs::Refs()
{
 vRefs.clear();
}

Refs::Refs(string serRefs)
{

  
  long lBloq;
  long lReg;
  string sKey;
  
  
 
  int campo=0;
  vRefs.clear();
  
  string auxString;
  
  for ( int i=0;i<serRefs.size();i++)
  {
      if(serRefs.at(i)=='=')
      {      
             bool entro=false;
         if(campo==2&&!entro)
             {                    
                     ref auxRef;    
                     auxRef.posBloq=lBloq;
                     auxRef.posReg=lReg;
                     Field auxField ;
                     auxField.DesSerialize(auxString);
                     
                     auxRef.Key=auxField;
                     campo=0;
                     vRefs.push_back(auxRef);
                     auxString.clear();
                     i++;
                     entro=true;
                     
             }
          if(campo==1&&!entro)
             {
                    stringstream ss;
                      ss<<  auxString;
                     ss>>lReg;
                     
                     campo++;
                         auxString.clear();
                     i++;
                     entro=true;
             }
         if(campo==0&&!entro)
             {          
                     stringstream ss;
                     ss<<  auxString;
                     ss>>lBloq;
                    
                     campo++;
                        auxString.clear();
                     i++;
                     entro=true;
                     
             }
                         
      }
      auxString=auxString+serRefs[i]; 
      
  }
  

}

string Refs::Serialize()
{
 string s;
 
 vector<ref>::iterator it= vRefs.begin();
 
 stringstream ss;
 
 while (it!=vRefs.end())
 {
  ss<<(*it).posBloq;
  ss<<"=";
   ss<<(*it).posReg;
   ss<<"=";
  ss<<(*it).Key.Serialize();
  ss<<"=";   
  it++;
 }
 return ss.str();
}

Refs::~Refs()
{
	vRefs.clear();
}


