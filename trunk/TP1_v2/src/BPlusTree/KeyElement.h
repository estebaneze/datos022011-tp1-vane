/*
 * KeyElement.h
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#ifndef KEYELEMENT_H_
#define KEYELEMENT_H_

#include "../utils/types.h"
#include "../Persistence/ISerializable.h"
#include <string>
#include <iostream>

using namespace std;
class KeyElement: public ISerializable {
private:
	Key key;
	Offset rightNode;
public:
	KeyElement();
	KeyElement(Key key,Offset rightNode);
	virtual ~KeyElement();

	Offset getrightNode();
	void setRightNode(Offset rightNode);

	void setKey(Key key);
	Key getKey();
    bool operator== (KeyElement k) {   // sobrecarga operador ==
       return this->key==k.key ;
     }
     bool operator> (KeyElement k) {    // sobrecarga operador >
       return this->key>k.key;
     }
     bool operator< (KeyElement k) {    // sobrecarga operador <
       return this->key<k.key;
     }

     friend ostream& operator<<(ostream&, KeyElement&);

     void toString(){
    	 cout<<"Key "<<this->key<<" RightOffSet: "<<rightNode<<" ";
     }
	/******************************************************
	 * 					PERSISTENCIA
	 *
	 ****************************************************/
	void unserialize(std::string &buffer);
	int getDataSize();
	std::string serialize();





};

#endif /* KEYELEMENT_H_ */
