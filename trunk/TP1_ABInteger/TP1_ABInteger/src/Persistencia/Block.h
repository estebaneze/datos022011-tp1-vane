#ifndef BLOCK_H_
#define BLOCK_H_

#include "ISerializable.h"
#include "../utils/types.h"

class Block : public ISerializable {
private:
	Offset offset;

public:
	Block();
	virtual ~Block();
	Offset getOffset();
	void setOffset (Offset offset);
};

#endif /* BLOCK_H_ */
