/**
	
 */
 
#ifndef BP_NODE_H
#define BP_NODE_H

#include "bp_subnode.h"
#include "key_node.h"

#include <queue>
#include <vector>

class Bp_Node{

private:
	
	vector<Bp_SubNode *> keys;	// en definitiva es un vector de claves
	vector<Bp_SubNode *>::iterator kit;
	
	
	int level;			// nivel del nodo
	int key_count;			// contador de claves
	
	bool leave;			// true si es hoja. 
	bool root;			// true si es root. 
	
	Bp_Node *a_menor;
	Bp_Node *a_mayor;
	

public:

	void keys_clear(){ this->keys.clear();}
	void keys_clear_firsts( int end);
	void keys_clear_lasts( int begin);
		
	vector<Bp_SubNode *> get_vector_keys(int begin, int end); //coon end = -1  hago que lea hsta vector.end()
	void get_keys(Key_Node *key, vector<Key_Node *> &output, bool izq);// con izq = true busca los <= de la 	
									// clave, con izq = false los mayores e 
									// iguales
	void get_interval_keys( Key_Node *begin,Key_Node *end, vector<Key_Node *> &output);
	void copy_keys( vector<Bp_SubNode *> input_vec ); 
	
	Bp_SubNode* get_first();
	Bp_SubNode* get_last();
	
	Bp_Node* get_follow_pointer( Key_Node key );
	
	
	Bp_Node();
	Bp_Node( int in_level );

	
	~Bp_Node();

// 	void find_key(Key_Node key,Bp_Node p_swap);
	bool is_leave(){ return this->leave; }
	void set_leave(bool is_leave){ this->leave = is_leave;}
		
	void insert_key(Key_Node &key){ this->bpn_insert_key(key, true); }
	int bpn_insert_key( Key_Node &key, bool update);	// update fuerza a actualizar o solo devuelve
	int bpn_erase_key(Key_Node key);

	void inc_key_count(){ this->key_count++;}
	void dec_key_count(){ this->key_count--;}
	
	void set_key_count(int new_count){ this->key_count = new_count;}
	int get_kc(){ return this->key_count;}			
	
	void set_menor( Bp_Node *menor){ this->a_menor = menor ; }
	void set_mayor( Bp_Node *mayor){ this->a_mayor = mayor ; }
	
	Bp_Node* get_menor(){ return this->a_menor; }
	Bp_Node* get_mayor(){ return this->a_mayor; }
	
	void set_root( bool is_root ){ this->root = is_root; }
	bool get_root(){ return this->root; }
	
	bool empty_keys();

	void set_level( int in_level){  this->level = in_level;}
	int get_level(){ return this->level;}
	
	int insert_subnode(Bp_SubNode *in_subnode);
	Bp_SubNode* get_separador(Bp_Node *hijo_izq, Bp_Node *hijo_der);
	
	void print_vec();
	
 	void save_vec(ofstream *file);
	
	void get_p_hijos( vector<Bp_Node *> &q_out );

	
	void update_sep( Bp_SubNode *p_sep, Bp_Node *izq, Bp_Node *der );
	
	int bpn_get_key(Key_Node &key);
};

#endif
