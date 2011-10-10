#include <math.h>
#include "HashExtensible.h"

HashExtensible::HashExtensible(){

}

HashExtensible::HashExtensible(std::string filename)
{
  this->directory= Directory();
  this->actualbits=directory.getActualBits();
  
  this->filename=filename;
  
  ifstream file(filename.c_str());
  if (file.is_open())
  {
     file.close();
     load();
  }  
  else 
  {
      ofstream ofile(filename.c_str(),ios::trunc);
      ofile.close();
  }
  
    
}

HashExtensible::HashExtensible(std::string filename, int bucketCap)
{
   

  this->bucketCapacity=bucketCap;
  
   this->filename=filename;
  ifstream file(filename.c_str());
  
  
  
  if (file.is_open())
  {
     file.close();
     load();
  }  
  else 
  {
      ofstream ofile(filename.c_str(),ios::trunc);
      ofile.close();
  }
  
  this->buckets= Buckets(this->bucketCapacity);

  this->directory= Directory();
   this->actualbits=directory.getActualBits();  
  
  
  
    save();      
}




int HashExtensible::fHash(Key_Node &key) 
{    
	if (actualbits != 0)
	{	
		//int intKey = key.toInt();
		//int K = (int) pow(2, this->actualbits);
		//double aux2 = 1000*fmod(intKey*CTEHASH,1);
		//return  (int)fmod(aux2,K);
		return (int)fmod (key.toInt(), this->actualbits);
	}

	return 0;   
}



void HashExtensible::add(Key_Node &key, Refs value)
{ 
    //load();
	//cout << "HashExtensible::add: " << key.toInt() << endl;
	if (!contains(key))
	{ 
		int Dir = fHash(key);
		
		//Obtengo el bucket al que apunta la direcci�n que devolvi� la funci�n de Hash.
		int	nBucket = directory.getNBlockBucket(Dir);
		 
		if (nBucket == -1)
		{
			//No existe la direccion -> creo un Bucket, creo una nueva direcci�n que lo apunte e inserto la clave	
			int nBlockBucket = buckets.createBucket();
			directory.insertDir(Dir,nBlockBucket);	
			buckets.addRef(nBlockBucket);
			buckets.insertKey(nBlockBucket, key, value);
        }			
		else
		{
			while (buckets.isFull(nBucket))
			{
				//Si no se puede dividir -> duplico el directorio
				if (buckets.getBucket(nBucket).getRef() == 1)
				{
					buckets.duplicateRef(directory.getDirectory());
					directory.duplicateDirectory();
					this->actualbits++;
					directory.updateBits(actualbits);
				}
	
				//Creo un nuevo Bucket y redistribuyo
				int newBlockBucket = buckets.createBucket();
				//Redirecciono al nuevo Bucket y actualizo las referencias
				directory.redirect(nBucket, newBlockBucket, buckets.getBucket(nBucket).getRef());	

				int nRef = buckets.getBucket(nBucket).getRef()/2;
				buckets.updateRef(nBucket,nRef);
				buckets.updateRef(newBlockBucket, nRef);

				//Inserto las claves que colisionaron y redistribuyo.
				Bucket TempBuck = buckets.getBucket(nBucket);
				buckets.clearBucket(nBucket);
				for (int n= 0; n < TempBuck.size(); n++)
				{
					Key_Node k=Key_Node(TempBuck.at(n).first);
					Dir = fHash(k);
					nBucket = directory.getNBlockBucket(Dir);
					buckets.insertKey(nBucket, k, TempBuck.at(n).second );
					//this->add(k,TempBuck.at(n).second);		
				}
				
				//Obtengo la nueva direccion
				Dir = fHash(key);
				//Obtengo el bucket al que apunta la direcci�n que devolvi� la funci�n de Hash.
				nBucket = directory.getNBlockBucket(Dir);
			}
			
			buckets.insertKey(nBucket, key, value);
		}
	
	}
	else
    {
     cout<<"Error la clave ya existe"<<endl;;    
    }
	
}


void HashExtensible::del( Key_Node &key) 
{
	int Dir = fHash(key);	
	//Obtengo el bucket al que apunta la direcci�n que devolvi� la funci�n de Hash.
	int	nB = directory.getNBlockBucket(Dir);

	buckets.deleteKey(nB, key);

	//Si el bucket est� vac�o y tiene una sola referencia, reorganizo el directorio y los buckets.
	if ( (buckets.getBucket(nB).empty()) && (buckets.getBucket(nB).getRef() == 1) )
	{
		int newDir = this->getPrevDir(Dir);
		int nuevoBucket = directory.getNBlockBucket(newDir);
		directory.updateDir(Dir,nuevoBucket);
		buckets.addRef(nuevoBucket);
		buckets.deleteBucket(nB);

		//Si el m�nimo de referencias a todos los bucketes es 2, saco un bit y reorganizo el directorio.
		if (buckets.minRef(directory.getDirectory()) == 2)
		{
			this->actualbits--;
			directory.updateBits(actualbits);
			directory.reduceDirectory();
			buckets.divRef(directory.getDirectory());	
		}

	}
}

int	HashExtensible::getPrevDir (int Dir)
{
	int DirPrev = (int) fmod(Dir, pow(2,this->actualbits -1));

	for (int j=0; j<directory.getNDir(); j++)
		if (j != Dir && DirPrev==(int)fmod(j, pow(2,this->actualbits -1)) )
			return j;
	return 0;
}

Refs * HashExtensible::get( Key_Node &key)
{
	int Dir = fHash(key);
	
	//Obtengo el bucket al que apunta la direcci�n que devolvi� la funci�n de Hash.
	int	nB = directory.getNBlockBucket(Dir);

	//Cargo el bucket y busco la clave. 
	return buckets.getBucket(nB).getValue(key);
}


bool HashExtensible::contains ( Key_Node &key)
{
	int Dir = fHash(key);
	if (directory.exists(Dir))
	{
		int	nB = directory.getNBlockBucket(Dir);
		return (buckets.getBucket(nB).exists(key));
	}
	else
		return false;
}

bool HashExtensible::isEmpty()
{
	return (directory.getNDir() == 0);
}

void HashExtensible::view()
{
	int nB ;
	Key_Node clave;
	Refs value;
	
	for (int j=0; j<directory.getNDir(); j++)
	{
		nB =  directory.getNBlockBucket(j);
		printf ("%s%d\t%s%d%s%d\n", "Dir: ",j, " nBucket: ", nB,", ref= " , buckets.getBucket(nB).getRef());
				
		for (int k = 0; k<buckets.getBucket(nB).size(); k++ )
		{
			clave = (buckets.getBucket(nB)).at(k).first;
			value = (buckets.getBucket(nB)).at(k).second;
			//printf ("%d\n", ((Integer*)clave.toDataObject().getAttribute(0))->getValue()) ;
		//	std::cout << ((opf::common::types::String*)clave.toDataObject().getAttribute(0))->getValue() << std::endl;
		} 
	}
}

std::vector< Refs > HashExtensible::getUpTo( Key_Node &key, bool includeKeyValue)
{
	std::vector< Refs > toReturn;
	for (unsigned int i = 0; i < directory.size(); i++)
	{
		int nBlock = directory.at(i).second;
		for (int j = 0; j < buckets.getBucket(nBlock).size(); j++)
		{
			std::pair<Key_Node,Refs> tempPair = buckets.getBucket(nBlock).at(j);
			if (tempPair.first.compareTo(key)==-1 || (tempPair.first.compareTo(key)==0 && includeKeyValue) )
				toReturn.push_back(tempPair.second);
		}
	}	
	return toReturn;
}


std::vector< Refs > HashExtensible::getFrom( Key_Node &key, bool includeKeyValue)
{
	std::vector< Refs > toReturn;
	for (unsigned int i = 0; i < directory.size(); i++)
	{
		int nBlock = directory.at(i).second;
		for (int j = 0; j < buckets.getBucket(nBlock).size(); j++)
		{
			std::pair<Key_Node,Refs> tempPair = buckets.getBucket(nBlock).at(j);
			if (tempPair.first.compareTo(key)==1 || (tempPair.first.compareTo(key)==0 && includeKeyValue))
				toReturn.push_back(tempPair.second);

		}
	}	
	return toReturn;
}


std::vector< Refs > HashExtensible::getRange( Key_Node &leftBound,  Key_Node&rightBound, bool includeLeftValue, bool includeRightValue)
{
	std::vector< Refs > toReturn;
	for (unsigned int i = 0; i < directory.size(); i++)
	{
		int nBlock = directory.at(i).second;
		for (int j = 0; j < buckets.getBucket(nBlock).size(); j++)
		{
			std::pair<Key_Node,Refs> tempPair = buckets.getBucket(nBlock).at(j);
			if ( ((tempPair.first.compareTo(leftBound)==1) || (tempPair.first.compareTo(leftBound)==0 && includeLeftValue)) && 
				 ((tempPair.first.compareTo(rightBound)==-1)  || (tempPair.first.compareTo(rightBound)==0 && includeRightValue)) )
				toReturn.push_back(tempPair.second);
		}
	}	
	return toReturn;
}

HashExtensible::~HashExtensible()
{
  
}


void HashExtensible::save()
{
     std::ofstream *file= new ofstream(this->filename.c_str(),ios::trunc);
     
     pair<int,int> auxPair;
     Bucket auxBucket;
     
     pair<Key_Node,Refs> auxKey;
     
     *file<< "Bucket_Capacity"<<endl;
     *file<< this->bucketCapacity <<endl;
     
     for(int i=0; i<directory.size();i++)
     {           
          auxPair=directory.at(i);
          auxBucket=buckets.getBucket(auxPair.second);
          
          for(int j=0; j<auxBucket.size();j++)
          {
                auxKey=auxBucket.at(j);   
                auxKey.first.Serialize(file);
                *file<< "Value"<<endl;
                *file<< auxKey.second.Serialize()<<endl;
	//	*file<< auxKey.second.posReg<<endl;
                *file<< "Value_End"<<endl;              
          }
          
          
     }
   file->close();
   delete(file); 
}

void HashExtensible::load()
{
     ifstream *file=new ifstream(this->filename.c_str());
     std:string aux;

	
     Key_Node auxk= Key_Node();
     
     while(!file->eof())
     {
                        
                        getline(*file,aux);
                        
                        if ( aux.compare("Bucket_Capacity")==0)
                        {
                              getline(*file,aux);
                            stringstream ssBucketcap(aux);
                            
                           ssBucketcap>>this->bucketCapacity;
                            this->buckets= Buckets(this->bucketCapacity);
            
                        }
                        
                        if ( aux.compare("Begin_Key_Node")==0)
                        {

                            auxk.DesSerialize(file);   
            
                        }
                          if ( aux.compare("Value")==0)
                        {
                                     getline(*file,aux);
                    				stringstream ss(aux);
            
                    				Refs auxRef= Refs(ss.str());
                                     add(auxk,auxRef);  
                                     auxk= Key_Node();     
                        }
                        
     }                                                                
}
