#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "Index.h"

using namespace std;


class TableIndex
{
private:
       std::string TableName;
       std::vector<Index> Indices; 
       
       string GetFileName(std::string Name);
     //  string GetFileNameHash(std::string Name, std::string TableName);
     //  string GetFileNameBtree(std::string Name, std::string TableName);
public:	
		
       TableIndex(std::string tableName);
       
       void save(); 
       
       void load();     
       
       void insertIndex(Index I);
       
	std::vector<Index> getIndices();

       ~TableIndex();   
	
};
