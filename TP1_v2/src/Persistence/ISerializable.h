/*
 * ISerializable.h
 *
 *  Created on: Apr 6, 2010
 *      Author: Daniel
 */

#ifndef ISERIALIZABLE_H_
#define ISERIALIZABLE_H_

#include <string>

class ISerializable {
	public:
		virtual std::string serialize() = 0;
		virtual void unserialize(std::string &buffer) = 0;
		virtual int getDataSize() = 0;
};

#endif /* ISERIALIZABLE_H_ */
