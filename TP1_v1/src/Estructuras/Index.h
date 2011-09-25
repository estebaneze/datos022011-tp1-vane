#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "key_node.h"
#include "HashExtensible.h"

using namespace std;

typedef enum {BPTREE, HASH} index_t;
typedef enum {ROMANO, GRIEGO} tindex_t;

class Index
{
private:
       std::string IndexName; 
       std::string TableName;
       int FieldsCount;
       std::vector<std::pair<std::string,type_t> > Fields;
       index_t IndexType;
       tindex_t tIndexType;      
       
       std::string IndexPrimario;
       type_t typeIndexPrimario;
       
       string GetFileName(std::string Name, std::string TableName);
       string GetFileNameHash(std::string Name, std::string TableName);
       string GetFileNameBtree(std::string Name, std::string TableName);
public:	
		Index();
       Index(std::string Name, std::string tableName);
       
       Index(std::string Name, std::string tableName, index_t indextype,tindex_t tindextype);
       
       
       void setIndexPrimario(string IPrimario,type_t tIPrimario);
       
       string getIndexPrimario();
       
       type_t getTypeIndexPrimario();
       
       void SaveIndex(); 
       
       void LoadIndex();     
       
       void addField(std::string FieldName, type_t FieldType);

	std::vector<std::pair<std::string,type_t> > getFields();
       
       int GetRef(std::vector<Field> inFields, Refs &outRefs);
       
       std::vector<Refs> GetRefFrom(std::vector<Field> inFields, bool include);
       
       std::vector<Refs> GetRefTo(std::vector<Field> inFields, bool include);
       
       std::vector<Refs> GetRefRange(std::vector<Field> inFieldsLow,std::vector<Field> inFieldsHigh, bool include);
       
       int PutRef(std::vector<Field> inFields,ref Value);
       
       int DelRef(std::vector<Field> inFields);
       
       int UpdateRef(std::vector<Field> inFields,Refs Value);
       
       void Create(int Prop);
       
       string Serialize();
       
       void DesSerialize(string serInd);
       
       ~Index();   
	
};
