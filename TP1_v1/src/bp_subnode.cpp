/***************************************************************************
             *
 ***************************************************************************/
#include "bp_subnode.h"


Bp_SubNode::Bp_SubNode(){

	this->izq = NULL;
	this->der = NULL;

}

Bp_SubNode::Bp_SubNode(Key_Node *input_key){

  	
	
	this->pk_node = input_key;

	
	

}


Bp_SubNode::~Bp_SubNode(){
	delete this->pk_node;
	
}

