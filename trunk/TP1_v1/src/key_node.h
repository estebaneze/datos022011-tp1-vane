#ifndef KEY_NODE_H
#define KEY_NODE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include "Field.h"
#include "refs.h"

using namespace std;

class Key_Node{
	
	private:
		std::vector<Field> Fields;
        	string name;	
		
	public:
		Refs ref;
		Key_Node();		
        		
	   	~Key_Node();				      		      
        
        Key_Node(const Key_Node& toCopy);		
		
        Key_Node& operator = (const Key_Node &asignando);		
		
        void AddField(Field F);
        
        vector<Field>::iterator GetIterator();
        		
		const bool operator < ( Key_Node &comparador);
		
		const bool operator > ( Key_Node &comparador);

    	const bool operator == ( Key_Node &comparador);

		const bool operator != ( Key_Node &comparador);
		
		const bool operator <= ( Key_Node &comparador);
	
		const bool operator >= ( Key_Node &comparador);

        int compareTo( Key_Node &key);
        
        void Print ();
        
       void Serialize (ofstream *f);
        
        void DesSerialize (ifstream *f);
        
        const int toInt();
				
};


#endif

