
#include "Index.h"
#include "bp_tree.h"

Index::Index(){
  
}

Index::Index(std::string Name, std::string tableName){
       this->IndexName=Name;
       this->TableName=tableName;                
	
	this->typeIndexPrimario=FNULL;
       this->LoadIndex();
}

Index::Index(std::string Name, std::string tableName, index_t indextype,tindex_t tindextype)
{
this->IndexName=Name;
this->TableName=tableName;
this->IndexType=indextype;
this->tIndexType=tindextype;
this->IndexPrimario="=";
this->typeIndexPrimario=FNULL;
ifstream file(GetFileName(this->IndexName,this->TableName).c_str());
  if (file.is_open())
  {
     file.close();
     LoadIndex();
  }  
  else 
  {
      SaveIndex();
  }
                   
}

void Index::setIndexPrimario(string IPrimario,type_t tIPrimario)
{
    this->IndexPrimario=IPrimario;
    this->typeIndexPrimario=tIPrimario;
}

string Index::getIndexPrimario()
{
    return  this->IndexPrimario;
}

type_t Index::getTypeIndexPrimario()
{
    return  this->typeIndexPrimario;
}



void Index::Create(int Prop)
{
     if(this->IndexType=HASH)
     {
                  bool Primario= (this->tIndexType==GRIEGO);
                  HashExtensible Hash= HashExtensible(GetFileNameHash(this->IndexName,this->TableName),Prop);   
                  Hash.save();                              
     }  
	 if(this->IndexType=BPTREE)
     {
                  bool Primario= (this->tIndexType==GRIEGO);
                  Bp_Tree tree= Bp_Tree(GetFileNameBtree(this->IndexName,this->TableName),Prop);   
                  tree.save();                              
     }  
}

void Index::SaveIndex(){
  ofstream file(GetFileName(this->IndexName,this->TableName).c_str(),ios::in|ios::out|ios::trunc);    
  file<<TableName<<endl;
  file<<IndexName<<endl;
  file<<(int)IndexType<<endl;
  file<<(int)tIndexType<<endl;
   file<<IndexPrimario<<endl;
    file<<(int)typeIndexPrimario<<endl;
  vector<std::pair<std::string,type_t> >::iterator it = Fields.begin();
  
  while (it!=Fields.end())
  {
        file<<(*it).first<<","<<(int)(*it).second<<endl;    
        it++;   
  }
  
  
 file.close(); 
}   

string Index::Serialize(){
   stringstream ss;    
  ss<<TableName<<endl;
  ss<<IndexName<<endl;
  ss<<(int)IndexType<<endl;
  ss<<(int)tIndexType<<endl;
   ss<<IndexPrimario<<endl;
    ss<<(int)typeIndexPrimario<<endl;
  vector<std::pair<std::string,type_t> >::iterator it = Fields.begin();
  
  while (it!=Fields.end())
  {
        ss<<(*it).first<<","<<(int)(*it).second<<endl;    
        it++;   
  }
  ss<<"END";
  
 return ss.str();
}   

std::vector<std::pair<std::string,type_t> > Index::getFields()
{
		return this->Fields;
}

void Index::DesSerialize(string serInd)
{                
                 Fields.clear();
                 stringstream ss(serInd);   
     
				string aux;
                ss>>TableName;
				ss>>IndexName;
				int intIndexType;
				ss>>intIndexType;
				
				IndexType=(index_t)intIndexType;			
                int inttIndexType;
				 ss>>inttIndexType;
				
				tIndexType=(tindex_t)inttIndexType;                          
			    
			    ss>>IndexPrimario;
			    int inttypeIndexPrimario;
			    ss>>inttypeIndexPrimario;
			    
			    typeIndexPrimario=(type_t)inttypeIndexPrimario;
				
				std::pair<std::string,type_t> auxpair;
                
                string auxFirst;
                string auxSecond;
                ss>>aux;
                while (aux!="END")
		        {                  
                      if (aux!="")
                      {
                          auxFirst= aux.substr(0,aux.find(","));
                          auxSecond= aux.substr(aux.find(",")+1,aux.size());
                          auxpair.first=auxFirst;
                          auxpair.second=(type_t)atoi(auxSecond.c_str());
                          Fields.push_back(auxpair);
                      }
                      ss>>aux;
                }
}


void Index::LoadIndex()
{                
                 Fields.clear();
                 ifstream file(GetFileName(this->IndexName,this->TableName).c_str(),ios::in|ios::out);   
     
				string aux;
                getline(file,TableName);
				getline(file,IndexName);
				getline(file,aux);
                int intIndexType=atoi(aux.c_str());
                IndexType=(index_t)intIndexType;
				             
                getline(file,aux);
				int inttIndexType=atoi(aux.c_str());
			    tIndexType=(tindex_t)inttIndexType;
				
				getline(file,IndexPrimario);
				getline(file,aux);
				int inttypeIndexPrimario=atoi(aux.c_str());
			    typeIndexPrimario=(type_t)inttypeIndexPrimario;
				
				
				std::pair<std::string,type_t> auxpair;
                
                string auxFirst;
                string auxSecond;
                while (!file.eof())
		        {
                      getline(file,aux);
                      if (aux!="")
                      {
                          auxFirst= aux.substr(0,aux.find(","));
                          auxSecond= aux.substr(aux.find(",")+1,aux.size());
                          auxpair.first=auxFirst;
                          auxpair.second=(type_t)atoi(auxSecond.c_str());
                          Fields.push_back(auxpair);
                      }
                }
                file.close();
}
 

void Index::addField(std::string FieldName, type_t FieldType)
{
     std::pair<string,type_t> auxPair;
     auxPair.first=FieldName;
     auxPair.second=FieldType;
     
     Fields.push_back(auxPair);
     
}

Index::~Index()
{
     
     Fields.clear();      
}

string Index::GetFileName(std::string Name, std::string TableName)
{
  std::string aux;
 
  aux.append(TableName);
  aux.append("-");
   aux.append(Name);
  aux.append(".idx");
       return      aux;
}


string Index::GetFileNameHash(std::string Name, std::string TableName)
{
  std::string aux;
 
  aux.append(TableName);
  aux.append("-");
   aux.append(Name);
  aux.append(".hsh");
       return      aux;
}

string Index::GetFileNameBtree(std::string Name, std::string TableName)
{
  std::string aux;
 
  aux.append(TableName);
  aux.append("-");
   aux.append(Name);
  aux.append(".bpt");
       return      aux;
}

int Index::GetRef(std::vector<Field> inFields, Refs &outRefs){
    Key_Node K= Key_Node();
    
    for (int i=0; i<inFields.size();i++){
       Field FAux=inFields.at(i);
        K.AddField(FAux);   
    } 
    
	if (IndexType==HASH)
	{
	 HashExtensible Hash= HashExtensible(GetFileNameHash(this->IndexName,this->TableName),false);
     Refs * refAux =Hash.get(K) ; 
         
     Refs * refOut= new Refs();;
     if (refAux==NULL)
      refOut=NULL;
     else
     *refOut=*refAux;
     delete(refAux);
     
     if (refOut!=NULL)
     {
        outRefs =*refOut;
        return 0;   
     }
     else
     {
         return 1;    
     }
         
	}
	if (IndexType==BPTREE)
	{
	  Key_Node * auxK = new Key_Node();
	  (*auxK)=K;
	  Bp_Tree btree= Bp_Tree(GetFileNameBtree(this->IndexName,this->TableName),3);
	  int ret;
	  ret = btree.get_key(*auxK);
	  if (ret==0)
	  {
         outRefs=(*auxK).ref;
         return 0;
      }
         else 
         return 1;
	
	}	
   
   return 1;
   
     
}



std::vector<Refs> Index::GetRefFrom(std::vector<Field> inFields, bool include){
    Key_Node K= Key_Node();
    
    for (int i=0; i<inFields.size();i++){
       Field FAux=inFields.at(i);
        K.AddField(FAux);   
    } 
    
	if (IndexType==HASH)
	{
	 HashExtensible Hash= HashExtensible(GetFileNameHash(this->IndexName,this->TableName),false);
     return Hash.getFrom(K,include) ;         
         
	}
	if (IndexType==BPTREE)
	{
	    Bp_Tree btree= Bp_Tree(GetFileNameBtree(this->IndexName,this->TableName));
        Key_Node * pK= new Key_Node();
        
        *pK=K;
        
        std::vector<Refs> auxvRefs;
        std::vector<Key_Node*> auxvKeyNode= btree.secuencial_search(pK, NULL );
        
        delete(pK);
        
        std::vector<Key_Node*>::iterator it = auxvKeyNode.begin();
        
        while (it!=auxvKeyNode.end())
        {
            auxvRefs.push_back((*(*it)).ref);
              it++;
        }
        return 	  auxvRefs;
	
	}	
   

   
     
}


std::vector<Refs> Index::GetRefTo(std::vector<Field> inFields, bool include){
    Key_Node K= Key_Node();
    
    for (int i=0; i<inFields.size();i++){
       Field FAux=inFields.at(i);
        K.AddField(FAux);   
    } 
    
	if (IndexType==HASH)
	{
	 HashExtensible Hash= HashExtensible(GetFileNameHash(this->IndexName,this->TableName),false);
     return Hash.getUpTo(K,include);
         
	}
	if (IndexType==BPTREE)
	{
	   Bp_Tree btree= Bp_Tree(GetFileNameBtree(this->IndexName,this->TableName));
        Key_Node * pK= new Key_Node();
        
        *pK=K;
        
        std::vector<Refs> auxvRefs;
        std::vector<Key_Node*> auxvKeyNode= btree.secuencial_search(NULL, pK );
        
        delete(pK);
        
        std::vector<Key_Node *>::iterator it = auxvKeyNode.begin();
        
        while (it!=auxvKeyNode.end())
        {
              auxvRefs.push_back((*(*it)).ref);
              it++;
        }
        return 	  auxvRefs;
	
	}	
   
   
     
}

std::vector<Refs> Index::GetRefRange(std::vector<Field> inFieldsLow,std::vector<Field> inFieldsHigh, bool include){
    Key_Node Kl= Key_Node();
    
    for (int i=0; i<inFieldsLow.size();i++){
       Field FAux=inFieldsLow.at(i);
        Kl.AddField(FAux);   
    } 
    
    Key_Node Kr= Key_Node();
    
    for (int i=0; i<inFieldsHigh.size();i++){
       Field FAux=inFieldsHigh.at(i);
        Kr.AddField(FAux);   
    } 
    
	if (IndexType==HASH)
	{
	 HashExtensible Hash= HashExtensible(GetFileNameHash(this->IndexName,this->TableName));
     return Hash.getRange(Kl,Kr,include,include);
     
         
	}
	if (IndexType==BPTREE)
	{
        Bp_Tree btree= Bp_Tree(GetFileNameBtree(this->IndexName,this->TableName));
        Key_Node * pKl= new Key_Node();
        Key_Node * pKr= new Key_Node();
        
        *pKl=Kl;
        *pKr=Kr;
        
        std::vector<Refs> auxvRefs;
        std::vector<Key_Node*> auxvKeyNode= btree.secuencial_search(pKl, pKr );
        
        delete(pKl);
        delete(pKr);
        
        std::vector<Key_Node*>::iterator it = auxvKeyNode.begin();
        
        while (it!=auxvKeyNode.end())
        {
             auxvRefs.push_back((*(*it)).ref);
              it++;
        }
        return 	  auxvRefs;
	
	}	
   
   
     
}
       
int Index::PutRef(std::vector<Field> inFields,ref Value){
    Key_Node K= Key_Node();
    
    for (int i=0; i<inFields.size();i++){
       Field FAux=inFields.at(i);
        K.AddField(FAux);   
    }                                  
   
     bool Primario= (this->tIndexType==GRIEGO);
   
	if (IndexType==HASH)
	{
   
    
    	HashExtensible Hash= HashExtensible(GetFileNameHash(this->IndexName,this->TableName));
    	
    	Refs * auxRefs= Hash.get(K);
    	
    	if (!Primario)
    	{        
        
        (*auxRefs).vRefs.push_back(Value);
        
        }
        else
        {
            if (auxRefs==NULL)
               {
               Refs addRef= Refs();
               addRef.vRefs.push_back(Value);
                              
               Hash.add(K,addRef);
               }
            else 
                 return 1;
        }    	    		
    	Hash.save();

	}
	if (IndexType==BPTREE)
	{
       
       
       
	  Bp_Tree btree= Bp_Tree(GetFileNameBtree(this->IndexName,this->TableName));
	  
	    int ret;
		Key_Node *auxKey = new Key_Node();
		*auxKey=K;
		ret = btree.get_key(*auxKey);
	  
	  
	  if (!Primario)
    	{        
        
        (*auxKey).ref.vRefs.push_back(Value);
        
        }
        else
        {
            if (ret==1)
               {
               Refs addRef= Refs();
               addRef.vRefs.push_back(Value);
               
               *auxKey=K;
               (*auxKey).ref=addRef;
                              
                btree.add_key(*auxKey,true);
               }
            else 
                 return 1;
        }    	    
	  
	   btree.save();
	
	}	
    return 0;
}

int Index::DelRef(std::vector<Field> inFields){
    Key_Node K= Key_Node();
    
    for (int i=0; i<inFields.size();i++){
       Field FAux=inFields.at(i);
        K.AddField(FAux);   
    }                                  
   
	if (IndexType==HASH)
	{
	 HashExtensible Hash= HashExtensible(GetFileNameHash(this->IndexName,this->TableName),true);
	 Hash.del(K);
	 
	 Hash.save();
	}
	if (IndexType==BPTREE)
	{
	
	
	//Metodos Arbol para Eliminar

	}	

   
    return 0;
}

int Index::UpdateRef(std::vector<Field> inFields,Refs Value){
    Key_Node K= Key_Node();
    
    for (int i=0; i<inFields.size();i++){
       Field FAux=inFields.at(i);
        K.AddField(FAux);   
    }                                  
   
    

	if (IndexType==HASH)
	{
	 HashExtensible Hash= HashExtensible(GetFileNameHash(this->IndexName,this->TableName),true);
    
	Hash.del(K);
	Hash.add(K,Value);
	Hash.save();
	}
	if (IndexType==BPTREE)
	{
	  Key_Node * auxK = new Key_Node();
	  (*auxK)=K;
	  (*auxK).ref=Value;
	  Bp_Tree btree= Bp_Tree(GetFileNameBtree(this->IndexName,this->TableName),2);
	  
	  btree.add_key(*auxK,true);
	  
	  btree.save();
      
	//Metodos Arbol para guardar
	
	}		

    return 0;
}
