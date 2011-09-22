#include "TableIndex.h"

TableIndex::TableIndex(std::string Name){
       this->TableName=Name;                
       ifstream file(GetFileName(this->TableName).c_str());
          if (file.is_open())
          {
             file.close();
             this->load();
          }  
          else 
          {
               file.close();
              save();
          }
}


string TableIndex::GetFileName(std::string TableName)
{
  std::string aux;
 
  aux.append(TableName);
  aux.append(".tix");
       return      aux;
}

void TableIndex::insertIndex(Index I)
{
     Indices.push_back(I);     
}

void TableIndex::save()
{
  ofstream file(GetFileName(this->TableName).c_str(),ios::in|ios::out|ios::trunc);    
  file<<TableName<<endl;
  
  vector<Index>::iterator it = Indices.begin();
  
  while (it!=Indices.end())
  {
        file<<"=Indice"<<endl;
         file<<(*it).Serialize()<<endl;
         file<<"=EndIndice"<<endl;
        it++;   
  }
  
  

  file.close(); 
}   

void TableIndex::load()
{                
                 Indices.clear();
                 ifstream file(GetFileName(this->TableName).c_str(),ios::in|ios::out);   
     
				string aux;
                getline(file,TableName);
                
                
                getline(file,aux);
                bool enIndice=false;
                string sIndice;
                
                while (!file.eof())
		        {
                      if(aux=="=Indice")
                      {
                          enIndice=true;                                                    
                                       
                      }
                      
                      if(aux=="=EndIndice")
                      {
                          enIndice=false;                                                    
                          
                          Index iAux= Index();
                          iAux.DesSerialize(sIndice);
                          
                          Indices.push_back(iAux);
                          sIndice.clear();
                          
                                       
                      }
                      
                      if (aux!="=Indice" &&aux!="=EndIndice" && enIndice)
                      {
                           sIndice= sIndice + aux + '\n'; 
                                        
                      }
                      
                      getline(file,aux);
                }
                
                
				
                file.close();
}

std::vector<Index> TableIndex::getIndices()
{

	return Indices;
}

TableIndex::~TableIndex()
{
 Indices.clear();
 TableName.clear();                         
}
