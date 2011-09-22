#include <math.h>
#include "Directory.h"


Directory::Directory()
{
	this->actualBits = 0;
}

Directory::Directory(const Directory &toCopy)
{
	this->directory = toCopy.directory;
}

std::vector<std::pair<int, int> > Directory::getDirectory ()
{
	return this->directory;
}

void Directory::insertDir (int Dir, int nBlockBucket)
{
	std::pair<int,int> Dir_nB;
	Dir_nB.first = Dir;
	Dir_nB.second = nBlockBucket;
	(this->directory).push_back(Dir_nB);
}

void Directory::updateDir (int Dir, int nBlockBucket)
{
	(this->directory).at(Dir).second = nBlockBucket;	
}

int Directory::getNBlockBucket(int Dir) const
{
	if (this->directory.size()>0)
	{
		unsigned int i = 0;
		while ( (this->directory.size() >= i) && ((this->directory).at(i).first != Dir) )
			i++;
			
		if (i <=this->directory.size())
			return ( this->directory.at(i).second );
	}		
	return -1;
}

void Directory::duplicateDirectory()
{
	std::pair<int,int> Dir_nB;
	int sizeIni = this->directory.size();
	for (int i= 0; i < sizeIni ; i ++)
	{
		Dir_nB.first = this->directory.at(i).first + sizeIni;
		Dir_nB.second = this->directory.at(i).second;
	
		this->directory.push_back(Dir_nB);
	}
}

std::vector<std::pair<int,int> >::iterator Directory::it(int dir)
{
	std::vector<std::pair<int,int> >::iterator it;
	int i = 0;
	for (it=directory.begin(); it!=directory.end();it++)
	{
		if (directory.at(i).first==dir)
			return it;
		i++;
	}
	return it;
}

void Directory::reduceDirectory ()
{
	//elimino desde la mitad del directorio en adelante
	this->directory.erase(it(directory.size()/2),directory.end());
}

int Directory::getNDir()
{
	return this->directory.size();
}

/*int Directory::getNRef (int nB)
{
	int nRef = 0;
	for (unsigned int i=0; i<directory.size(); i++)
	{
		if (directory.at(i).second == nB)
			nRef++;
	}
	return nRef;
}
*/

void Directory::redirect(int nB, int newBlockBucket, int nRef)
{
	//Redirecciono las n/2 últimas referencias (que apuntaban al buecket en conflicto) al nuevo bucket
	int redir = nRef/2;
	int i = directory.size();
	
	while (i>0 and redir>0)
	{
		if (directory.at(i-1).second == nB)
		{
			directory.at(i-1).second = newBlockBucket;
			redir--;
		}
		i--;		
	}	
}

	
int	Directory::getActualBits()
{
	return this->actualBits;
}

void Directory::updateBits(int actualBits)
{
	this->actualBits = actualBits;
}

Directory::~Directory()
{

}

std::pair<int,int> Directory::at (unsigned int i)
{
	return this->directory.at(i);
}

unsigned int Directory::size()
{
	return this->directory.size();
}

bool Directory::exists(int Dir)
{
	for (unsigned int i = 0; i < directory.size(); i++)
		if (directory.at(i).first == Dir)
			return true;
	return false;
}

void Directory::destroy()
{
	directory.clear();
}
