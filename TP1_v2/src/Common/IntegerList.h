/*
 * IntegerList.h
 *
 *  Created on: 25/09/2011
 *      Author: minnie
 */

/********* ESTO HAY QUE MEJORARLO ***********/

#include <cstdlib>

#ifndef INTEGERLIST_H_
#define INTEGERLIST_H_

class IntegerList {

	public:
		IntegerList();
		virtual ~IntegerList();
		void Add(int elem);
		int GetSize();
		int Get(int index);
		bool IsInList(int elem);
		void Remove(int elem);

	private:
		int* _lista;
		int _size;
};

#endif /* INTEGERLIST_H_ */
