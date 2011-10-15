/*
 * table.h
 *
 */

#ifndef TABLE_H_
#define TABLE_H_

#include "../Persistence/Block.h"
#include <string>
#include <iostream>
#include <vector>
#include <set>

class Table: public Block {
private:
	std::vector<Offset> buckets;
public:
	Table();
	virtual ~Table();

	void insert(Offset bucketAddr, int first, int last);

	void duplicate();
	bool reduce();
    unsigned int getSize();
    Offset getElement(int);
    void replace(Offset,Offset);

	std::string serialize();
	void unserialize(std::string &buffer);
	int getDataSize();
	void toHuman(std::set<Offset>* offsets);
	void getOffsets(std::set<Offset>* offsets);

	bool operator==(const Table&) const;
};

#endif /* TABLE_H_ */
