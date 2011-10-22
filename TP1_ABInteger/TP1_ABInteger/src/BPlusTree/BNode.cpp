#include "BNode.h"


BNode::BNode(PersistorBTree* p) {
        this->p = p;
}

BNode::~BNode() {
}


void BNode::setLevel(Level level) {
        this->level = level;
}

PersistorBTree* BNode::getPersistorInstance(){
        return this->p;
}


Level BNode::getLevel() {
        return level;
}

int BNode::getDataSize() {
        return sizeof(Level) + sizeof(RegisterCounter);
}

void BNode::modify(){
        this->p->modify(this);
}
std::string  BNode::serialize() {
        std::string buffer = "";
        RegisterCounter registerCounter=this->getRegisterCounter();
        buffer.append((char*)&level,sizeof(Level));
        buffer.append((char*)&registerCounter,sizeof(RegisterCounter));

        return buffer;
}

void BNode::unserialize(std::string &buffer) {
        buffer.copy((char*)&level,sizeof(Level));
        buffer.erase(0,sizeof(Level));

        //buffer.copy((char*)&registerCounter,sizeof(RegisterCounter));
        //buffer.erase(0,sizeof(RegisterCounter));
}


