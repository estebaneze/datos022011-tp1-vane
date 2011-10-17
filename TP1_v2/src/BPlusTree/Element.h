/*
 * Element.h
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "../utils/types.h"
#include "../Persistence/ISerializable.h"
#include <string.h>
#include <iostream>
using namespace std;
class Element: public ISerializable {
private:
	Key key;
	DataSize dataSize;
	Data data;

public:
	Element();
	//constructor de copia
	Element(const Element& el);
	Element(const Element* el);
	Element(Key key, Data data, DataSize dataSize);
	virtual ~Element();

	void setData(Data data, DataSize dataSize);
	Data getData();

	void setKey(Key key);
	Key getKey() const ;

	DataSize getElementSize();

	std::string serialize();
	void unserialize(std::string &buffer);
	int getDataSize();

	bool operator==(const Element& k) { // sobrecarga operador ==
		return this->key == k.key;
	}
	bool operator>(const Element& k) { // sobrecarga operador >
		return this->key > k.key;
	}
	bool operator<(const Element& k) { // sobrecarga operador <
		return this->key < k.key;
	}

	/**
	 * Element deberia ser definido como const, pero para que compile
	 * Los accesores tambien deberian ser definidos como const.
	 */
	friend ostream& operator<<(ostream&, Element&);

	void toSrtring(){
		string data(getData(),getElementSize());
		cout<<"Key : "<<getKey()<<" "<<"Data: "<<data<<" ";
	}
};

#endif /* ELEMENT_H_ */
