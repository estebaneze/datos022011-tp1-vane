#include "Buckets.h"


Buckets::Buckets()
{
                                   
}
Buckets::Buckets(int inbucketCapacity)
{
      this->bucketCapacity = inbucketCapacity;                                
}

Buckets::Buckets(const Buckets &toCopy)
{
	this->bucketCapacity = toCopy.bucketCapacity;
}

int Buckets::createBucket()
{
	//Creo el bucket asignandole el numero de bucket y la cantidad de claves y referencias en cero
	int nB = getNBuckets()+1; //numero de bucket 
	Bucket tempBucket = Bucket( nB, 0);
	buckets.push_back(tempBucket);
	return nB;
}

void Buckets::deleteBucket(int nBlockBucket)
{
     	std::vector<Bucket>::iterator it = buckets.begin();
     	while (it != buckets.end() ) {
              if ( (*it).getNBucket()== nBlockBucket )
              {
                 buckets.erase(it);
                 //it = buckets.end();   
              } 
              it++;       
      }
}

Bucket Buckets::getBucket(int nBlockBucket) {

 	for(int i=0;i<buckets.size();i++){
          if (  buckets[i].getNBucket()== nBlockBucket )
          {
                Bucket B=buckets[i];
             return buckets[i] ;
             
          } 
    } 
}

void Buckets::updateBucket(int nBlockBucket, Bucket& bucket) 
{
 
 	for(int i=0;i<buckets.size();i++){
          if (  buckets[i].getNBucket()== nBlockBucket )
          {
             buckets[i] = bucket;
             
          } 
    }   
}

void Buckets::insertKey(int nBlockBucket, Key_Node &key, Refs value)
{
     Bucket tempBucket = getBucket(nBlockBucket);
     tempBucket.insertKey(key, value);
     updateBucket(nBlockBucket, tempBucket);
}

void Buckets::deleteKey(int nBlockBucket, Key_Node &key)
{
     Bucket tempBucket = getBucket(nBlockBucket);
     tempBucket.deleteKey(key);
     updateBucket(nBlockBucket, tempBucket);
}

unsigned int Buckets::getBucketCapacity()
{
	return this->bucketCapacity;
}


void Buckets::clearBucket(int nBlockBucket)
{
	Bucket TempBucket = getBucket(nBlockBucket);
	TempBucket.clear();
	updateBucket(nBlockBucket, TempBucket);
}

void Buckets::addRef(int nBlockBucket)
{
	Bucket TempBucket = getBucket(nBlockBucket);
	TempBucket.addRef();
	updateBucket(nBlockBucket, TempBucket);
}


void Buckets::updateRef(int nBlockBucket, int ref)
{
	Bucket TempBucket = getBucket(nBlockBucket);
	TempBucket.updateRef(ref);
	updateBucket(nBlockBucket, TempBucket);
}
 
void Buckets::duplicateRef(std::vector<std::pair<int, int> > nBlocks)
{
	unsigned int i;	
	for (i = 0; i< nBlocks.size(); i++)
	{
		Bucket TempBucket = getBucket(nBlocks.at(i).second);
		TempBucket.duplicateRef();
		updateBucket(nBlocks.at(i).second,TempBucket);
	}
}

void Buckets::divRef(std::vector<std::pair<int, int> > nBlocks)
{
	unsigned int i;	
	for (i = 0; i< nBlocks.size(); i++)
	{
		Bucket TempBucket = getBucket(nBlocks.at(i).second);
		TempBucket.divRef();
		updateBucket(nBlocks.at(i).second, TempBucket);
	}
}

int	Buckets::minRef(std::vector<std::pair<int, int> > nBlocks)
{
	int min=0;
	int refAct;
	
	unsigned int i;
	for (i = 0; i< nBlocks.size(); i++)
	{
		Bucket TempBucket = getBucket(nBlocks.at(i).second);
		refAct = TempBucket.getRef();
		if (refAct<min || min == 0)
			min = refAct;
	}
	return min;	
}

int  Buckets::getNBuckets(){
     
     return this->buckets.size();
}

bool Buckets::isFull (int nBlockBucket)
{
    Bucket TempBucket = getBucket(nBlockBucket);
	unsigned int bucketSize = TempBucket.size(); 
	return ((bucketSize+1) > (bucketCapacity));

}

Buckets::~Buckets()
{
     buckets.clear();
}
