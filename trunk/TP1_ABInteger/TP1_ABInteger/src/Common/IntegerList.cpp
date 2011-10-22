/*
 * IntegerList.cpp
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

/********* ESTO HAY QUE MEJORARLO ***********/

#include "IntegerList.h"

IntegerList::IntegerList() {

	_size = 0;
}

void IntegerList::Remove(int elem){

	_size = _size--;

	//TODO: IMPLEMENTAR
}

bool IntegerList::IsInList(int elem){

	if(_size == 0){
		return false;
	}

	int i = 0;
	for (i = 0; i < _size; ++i) {
		if(_lista[i] == elem){
			return true;
		}
	}

	return false;
}

int IntegerList::Get(int index){
	if(_size == 0){
		return NULL;
	}
	else if(index >= _size){
		return NULL;
	}
	else {
		return _lista[index];
	}
}

int IntegerList::GetSize(){
	return _size;
}

void IntegerList::Add(int elem){

	if(_size == 0){
		_lista = new int[1];
		_lista[0] = elem;
	}

	int temp[_size + 1];
	int i = 0;
	//Copio la lista actual, despues le agrego el nuevo elem
	for (i = 0; i < _size; ++i) {
		temp[i] = _lista[i];
	}

	temp[_size] = elem;

	_lista = temp;
	_size = _size++;

	delete[] temp;
}

IntegerList::~IntegerList() {
	// TODO Auto-generated destructor stub
}
