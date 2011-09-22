
/**
	Esta clase es el subnodo que contiene la clave/
	  
	
 */
 
 
#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include <iostream>
#include <vector>
#include "key_node.h"

#define LONG 5 


using namespace std;

class Bp_SubNode{	// nodo general que incluye un puntero a izq y a der y un objeto tipo clave

private:
	
	Key_Node *pk_node;	// puntero a key_node 
	void *izq;		
	void *der;		
	
	
public:
	Bp_SubNode();
	
	Bp_SubNode(Key_Node *input_key);
	
	~Bp_SubNode();

	
	void set_izq( void *dir_izq){ this->izq = dir_izq;}
	void* get_izq(){ return this->izq; }
	void set_der( void *dir_der){ this->der = dir_der;}
	void* get_der(){ return this->der; }
	
	Key_Node* get_key(){ return this->pk_node;}
	
	void insert_key(Key_Node *key){ this->pk_node = key; }

	
	
};

#endif


















