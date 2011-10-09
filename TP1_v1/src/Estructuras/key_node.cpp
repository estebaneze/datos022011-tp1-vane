#include "key_node.h"

/*CONSTRUCTORES */

Key_Node::Key_Node()
{
     ref=Refs();
}

Key_Node::Key_Node(const Key_Node& toCopy)
{
	 this->Fields=toCopy.Fields;
	  this->ref= toCopy.ref;
}

Key_Node& Key_Node::operator = (const Key_Node &asignando){
          this->Fields=asignando.Fields;
	      this->ref= asignando.ref;
	return (*this);
}

void Key_Node::AddField(Field F)
{
      this->Fields.push_back(F); 
}


vector<Field>::iterator Key_Node::GetIterator(){
        return Fields.begin();                                        
}

Key_Node::~Key_Node(){

}	

int Key_Node::GetFieldCount(){
	return this->ref.vRefs.size();
}

/* OPERADOR <*/
const bool Key_Node::operator < ( Key_Node &comparador){
       bool result;
       vector<Field>::iterator it1=this->Fields.begin();
       vector<Field>::iterator it2= comparador.GetIterator();
       
       while( it1 != Fields.end() ) {
        if((*it1)!=(*it2))
        {
            result = (*it1)<(*it2);
            it1=this->Fields.end();
        }
        else
        {
           result=false;
           it1++;
           it2++;        
        }     
       }
                       	 
       return result;
     
}


///* OPERADOR >*/
const bool Key_Node::operator > ( Key_Node &comparador){
       bool result;
       vector<Field>::iterator it1=this->Fields.begin();
       vector<Field>::iterator it2= comparador.GetIterator();
       
       while( it1 != Fields.end() ) {
        if(*it1!=*it2)
        {
            result = (*it1)>(*it2);
            it1=this->Fields.end();
        }
        else
        {
           result=false;
           it1++;
           it2++;        
        }     
       }
                       	 
       return result;
     
}
//
///* OPERADOR ==*/
//
const bool Key_Node::operator == ( Key_Node &comparador){
       bool result=false;
       vector<Field>::iterator it1=this->Fields.begin();
       vector<Field>::iterator it2= comparador.GetIterator();
       
       while( it1 != Fields.end() ) {
        if(*it1!=*it2)
        {
            result = false;
            it1=this->Fields.end();
        }
        else
        {
           result=true;
           it1++;
           it2++;        
        }     
       }
                       	 
       return result;
     
}
///* OPERADOR !=*/
//
const bool Key_Node::operator != ( Key_Node &comparador){
       bool result;
       vector<Field>::iterator it1=this->Fields.begin();
       vector<Field>::iterator it2= comparador.GetIterator();
       
      while( it1 != Fields.end() ) {
        if(*it1!=*it2)
        {
            result = true;
            it1=this->Fields.end();
        }
        else
        {
           result=false;
           it1++;
           it2++;        
        }     
       }
                       	 
       return result;
     
}
//
///* OPERADOR <=*/
//
const bool Key_Node::operator <= ( Key_Node &comparador){
       bool result;
       vector<Field>::iterator it1=this->Fields.begin();
       vector<Field>::iterator it2= comparador.GetIterator();
       
       while( it1 != Fields.end() ) {
        if(*it1!=*it2)
        {
            result = (*it1)<=(*it2);
            it1=this->Fields.end();
        }
        else
        {
           result=true;
           it1++;
           it2++;        
        }     
       }
                       	 
       return result;
     
}
//
///* OPERADOR >=*/
//
const bool Key_Node::operator >= ( Key_Node &comparador){
       bool result;
       vector<Field>::iterator it1=this->Fields.begin();
       vector<Field>::iterator it2= comparador.GetIterator();
       
       while( it1 != Fields.end() ) {
        if(*it1!=*it2)
        {
            result = (*it1)>=(*it2);
            it1=this->Fields.end();
        }
        else
        {
           result=true;
           it1++;
           it2++;        
        }     
       }
                       	 
       return result;
     
}

int Key_Node::compareTo(Key_Node &comparador)
{
       int result;
       
       int si=Fields.size();
       
       vector<Field>::iterator it1=this->Fields.begin();
       vector<Field>::iterator it2= comparador.GetIterator();
       
       while( it1 != Fields.end() ) {
        if(*it1!=*it2)
        {
            result = -1;
            it1=this->Fields.end();
        }
        else
        {
           result=0;
           it1++;
           it2++;        
        }     
       }
                       	 
       return result;
     
}

const int Key_Node::toInt()
{
    int toReturn = 0;

    for (unsigned int i = 0; i < Fields.size(); i++)
		toReturn += (Fields.at(i)).toInt();

	return toReturn; 
}


void Key_Node::Serialize (std::ofstream *f)
{

	*f<<"Begin_Key_Node"<<endl;
	for(int i=0;i<Fields.size();i++)
	{
		*f<<Fields[i].Serialize()<<endl;
	}

	*f<<"End_Key_Node"<<endl;
}

void Key_Node::Print ()
{

	cout<< "Begin_Key_Node - Clave: ";
	cout << this->toInt() << endl;

	for(int i = 0; i < Fields.size(); i++)
	{
		//cout << Fields[i].Serialize() << endl;
		cout << Fields[i].getStr() << endl;
	}

	cout<<"End_Key_Node"<<endl;

}

void Key_Node::DesSerialize (std::ifstream *f)
{

	Fields.clear();
	//ref.posBloq=-1;
	//ref.posReg=-1;
	string aux;
	getline(*f,aux);
	while((aux!="End_Key_Node")&&(!(*f).eof()))
	{

		if(aux!="Begin_Key_Node"){
			Field Faux=Field();
			Faux.DesSerialize(aux);
			Fields.push_back(Faux);
		}

		getline(*f,aux);
	}
 

}
