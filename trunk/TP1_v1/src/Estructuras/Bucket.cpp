#include "Bucket.h"
#include "key_node.h"

Bucket::Bucket()
{}

Bucket::Bucket(int N, int prof)
{
	this->N = N;
	this->refs = prof;
}

Bucket::Bucket(const Bucket &toCopy)
{
	this->N = toCopy.N;
	this->bucket = toCopy.bucket;
	this->refs = toCopy.refs;
}

int Bucket::getNBucket() const
{
	return this->N;
}

std::vector<std::pair<Key_Node,Refs> > Bucket::getBucket()
{
	return this->bucket;
}

std::pair<Key_Node,Refs> Bucket::at(int i)
{
	return (this->bucket.at(i));
}


bool Bucket::exists ( Key_Node &key)
{
     
	for (unsigned int i = 0; i< bucket.size(); i++)
	{
		std::pair<Key_Node,Refs> b = bucket.at(i);
        int aux = b.first.compareTo(key);
        if (aux==0)
			return true;
        }
	return false;
}


void Bucket::insertKey ( Key_Node &key, Refs value)
{
	if (exists(key))
		cout<< "Error la Clave Existe en el Bucket"<< endl;
	else
	{
		std::pair<Key_Node,Refs> Temp_KeyValue;	
		Temp_KeyValue.first = key;
        Temp_KeyValue.second=value;

	         
	    Key_Node k= Key_Node(key);
	    
		bucket.push_back(Temp_KeyValue);
		
	}
}

void Bucket::deleteKey ( Key_Node &key)
{ 
	if (!exists(key))
			cout<< "Error la Clave NO Existe en el Bucket"<< endl;
	else
	{
		std::vector<std::pair<Key_Node,Refs> >::iterator it = bucket.begin();
		unsigned int i = 0;
		while (i < bucket.size())
		{
			if (bucket.at(i).first.compareTo(key)==0)
				bucket.erase(it);
			it++;
			i++;
		}	
	}
}

bool Bucket::empty()
{
	return this->bucket.empty();
}

int Bucket::size()
{
	return this->bucket.size();
}

void Bucket::clear()
{
	return this->bucket.clear();
}

Refs * Bucket::getValue( Key_Node &key)
{
	if (!exists(key))
		return NULL;
	else
	{
		unsigned int i = 0;
		while (i < bucket.size())
		{
			if (bucket.at(i).first.compareTo(key)==0)
            {
            
             Refs * r1=new Refs();
             *r1=bucket.at(i).second;
              return r1;
            }
            i++;
		}
	}	    
}

int Bucket::getRef()
{
	return this->refs;
}

void Bucket::addRef()
{
	this->refs++;
}

void Bucket::updateRef(int ref)
{
	this->refs=ref;
}
 
void Bucket::duplicateRef()
{
	this->refs=refs*2;
}

void Bucket::divRef()
{
	this->refs=refs/2;
}



Bucket::~Bucket()
{}
