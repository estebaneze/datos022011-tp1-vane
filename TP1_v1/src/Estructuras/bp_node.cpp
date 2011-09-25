/***************************************************************************
 Esta clase fue escrita maliciosamente
 ***************************************************************************/
#include "bp_node.h"
#include <assert.h>


#include <vector>

using namespace std;

Bp_Node::Bp_Node(){
	
	this->a_menor = NULL;
	this->a_mayor = NULL;
	this->level = 1;
	this->key_count = 0;
	this->leave = true;
	this->root = false;
	this->kit = this->keys.begin();
	

}

Bp_Node::Bp_Node(int in_level){
	
	
	this->a_menor = NULL;
	this->a_mayor = NULL;
	this->level = in_level;
	this->key_count = 0;
	this->leave = true;
	this->root = false;
}

Bp_Node::~Bp_Node(){
	
	vector<Bp_SubNode *>::iterator it;
	for( it = this->keys.begin(); it != this->keys.begin(); it++)
		delete *it; 
		     
	
	
}

int Bp_Node::bpn_insert_key( Key_Node &key, bool update ){
	
	// return codes:	0	no existia la clave  y se inserto.
	//			1	existia	-> y se inserto
	// 			2	existia -> no se inserto
	
// ----------------------------------------------------------------------------------------------------
			
	// si esta vacio inserto directo
	if ( this->keys.empty() ){
		
		Bp_SubNode *p_aux = new Bp_SubNode();	// creo un subnodo
		p_aux->insert_key(&key);			// le meto la clave
		this->keys.push_back(p_aux);		// meto en el vector el puntero al subnodo
		inc_key_count();
		return 0; 
	}	
	
	vector<Bp_SubNode *>::iterator it = this->keys.begin();
	
	
	while( key > *(*it)->get_key()) {
		
		it++;
	
		if (it == keys.end()){
			// es la mayor. Inserto
			Bp_SubNode *p_aux = new Bp_SubNode();	// creo un subnodo
			p_aux->insert_key(&key);			// le meto la clave
			this->keys.push_back(p_aux);		// meto en el vector el puntero al subnodo
			inc_key_count();
			return 0;
		}
		
	}
	
	if ( key == *(*it)->get_key() ){
		
		
		if ( update ){
			
			Bp_SubNode *p_aux = new Bp_SubNode();	// creo un subnodo
			p_aux->insert_key(&key);		// le meto la clave
			this->keys.erase(it);			// borro la actual
			
			this->keys.insert(it, p_aux);		// actualizo (inserto la nueva)
			return 1;
		}else
			return 2;				// existe y no inserte
		
			
	// si es menor entonces inserto en el lugar, y el mayor (el actualmente apuntado) lo desplaza la STL a der
	} else if ( key < *(*it)->get_key() ){
		
		Bp_SubNode *p_aux = new Bp_SubNode();	// creo un subnodo
		p_aux->insert_key(&key);			// le meto la clave
		this->keys.insert(it, p_aux);		// meto en el vector el puntero al subnodo
		inc_key_count();
		return 0;
	}
	

}

bool Bp_Node::empty_keys(){
	
	if ( this->keys.empty() )
		return true;
	else
		return false;
}

Bp_Node* Bp_Node::get_follow_pointer( Key_Node key ){
	
	
	// devuelve el hijo a seguir segun la clave de entrada y las condiciones de orden del arbol
	vector<Bp_SubNode *>::iterator it;
		
	it = keys.begin();
	
	if (this->keys.empty())
		cout << "ERROR: No deberia estar vacio nunca\n";
	
	while( key > *(*it)->get_key()){
		
		it++;
		
		if  ( it == keys.end() ){
			it--;
			return (Bp_Node *)(*it)->get_der();	// sigo por el hijo DERECHO
			
		}
	}
	
	if( key == *(*it)->get_key() )
		return (Bp_Node *)(*it)->get_der();	// sigo por el hijo DERECHO
	else if( key < *(*it)->get_key() )
		return (Bp_Node *)(*it)->get_izq();	// sigo por el hijo IZQUIERDO*/
	else
		cout << "Error: caso imposible\n";

	
}
	
vector<Bp_SubNode *> Bp_Node::get_vector_keys(int begin, int end){
	
	
	vector<Bp_SubNode *> aux;
	vector<Bp_SubNode *>::iterator it;
		
	
	
	if( end != -1 ){
						
		it = this->keys.begin() + begin;
		 
		int steps = end - begin;
		
		for( int i = 0; i < steps ; i++ ){
		 	aux.push_back(*it);
			it++;
		}
	
	}else{
		it = this->keys.begin() + begin;
		int steps = this->keys.size() - begin;
		
		for( unsigned int i = 0; i < steps ; i++ ){
			aux.push_back(*it);
			it++;
		}
	}
		
	
	
	return aux;
}

void Bp_Node::get_keys(Key_Node *key, vector<Key_Node *> &output, bool izq){
	
	vector<Bp_SubNode *>::iterator it = keys.begin();
	
	bool encon = false;
	
	
	if ( key == NULL ){
		
		while( ( it != keys.end() ) && !encon ){
			
			Key_Node *kaux = new Key_Node();
			*kaux = *((*it)->get_key());		// clono las claves
			output.push_back(kaux);			// agrego la clave al vector que 
									// entrego	
			it++;
		}
	
	}else if ( izq ){
		
		bool encon = false;
		while( ( it != keys.end() ) && !encon ){
		
			if ( *((*it)->get_key()) >= *key ){
				Key_Node *kaux = new Key_Node();
				*kaux = *((*it)->get_key());		// clono las claves
				output.push_back(kaux);			// agrego la clave al vector que 
									// entrego	
				it++;
			}else{
				it++;
				
			}
			
			
		}
	}else{
		
		while ( it != keys.end() ){
			
			if (*((*it)->get_key()) <= *key ){
				Key_Node *kaux = new Key_Node();
				*kaux = *((*it)->get_key());		// clono las claves
				output.push_back(kaux);			// agrego la clave al vector que 
			}
			
			it++;
		}
	}
	
		
}
void Bp_Node::get_interval_keys( Key_Node *begin, Key_Node *end , vector<Key_Node *> &output){

	vector<Bp_SubNode *>::iterator it = keys.begin();
		
	if ( (begin != NULL) && (end != NULL) ){ 
		while ( *(*it)->get_key() < *begin )
			it++;
		bool encon = false;
		while (  ( it != keys.end()) && !encon ){
			
			if (*((*it)->get_key()) <= *end ){
				Key_Node *kaux = new Key_Node();
				*kaux = *((*it)->get_key());		// clono las claves
				output.push_back(kaux);			// agrego la clave al vector que 
				it++;
			}else
				encon = true;
				
		}
	}else if( (begin == NULL) && (end == NULL) ){
		
		it = keys.begin();
		
		while( it != keys.end()) {
			
			Key_Node *kaux = new Key_Node();
			*kaux = *((*it)->get_key());		// clono las claves
			output.push_back(kaux);			// agrego la clave al vector que 
			it++;
		
		}
	
	
	}else if( end == NULL ){
		while ( *(*it)->get_key() < *begin )
			it++;
		
		while( it != keys.end()) {
			
		
			Key_Node *kaux = new Key_Node();
			*kaux = *((*it)->get_key());		// clono las claves
			output.push_back(kaux);			// agrego la clave al vector que 
			it++;
			
		}
	}else if ( begin == NULL ){
		
		it = keys.begin();
		
		bool encon = false;
		while (  ( it != keys.end()) && !encon ){
			
			if (*((*it)->get_key()) <= *end ){
				Key_Node *kaux = new Key_Node();
				*kaux = *((*it)->get_key());		// clono las claves
				output.push_back(kaux);			// agrego la clave al vector que 
				it++;
			}else
				encon = true;
				
		}
	}else
		cout << "ERROR: caso imposible\n";






}

void Bp_Node::copy_keys( vector<Bp_SubNode *> input_vec ){
	
	vector<Bp_SubNode *>::iterator it = keys.begin();
	

	
	for (unsigned int i = 0; i < input_vec.size(); i++ ){
			
		this->keys.push_back( input_vec[i] );
		this->inc_key_count();				// subo el contador de claves
	
	}	
	int i = 0;
	
}

Bp_SubNode* Bp_Node::get_separador(Bp_Node *hijo_izq, Bp_Node *hijo_der){
	// devuelve (un p_subnodo) un puntero a separador
	 
	vector<Bp_SubNode *>::iterator it = keys.begin();
	// lo llamo desde el nodo que tiene la clave a subir (la 1ra del vector)
	// le paso los hijos que esta clave va a tener, y me devuelve un subnode a insertar.
	Bp_SubNode *bpn_aux = new Bp_SubNode( (*it)->get_key() );	// llamo a bp_subnode pasandole la key que
									// quiero que me duplique
	bpn_aux->set_izq((void *)hijo_izq);				// referencio a los hijos
	bpn_aux->set_der((void *)hijo_der);
	
	return bpn_aux;
	
	
}

int Bp_Node::insert_subnode(Bp_SubNode *in_subnode){
	
	
	if ( this->keys.empty() ){
		
		Key_Node *h = in_subnode->get_key();
		this->keys.push_back(in_subnode);
		this->inc_key_count();
	
	}else{
		// ordenado
		vector<Bp_SubNode *>::iterator it = this->keys.begin();
		
		while ( *(in_subnode->get_key()) > *(*it)->get_key() ){
			
			it++;
			if( it == this->keys.end() ) {
				this->keys.push_back(in_subnode);	
				this->inc_key_count();
				return 0;
			}
			
		}
		
	
		if( *(in_subnode->get_key()) == *(*it)->get_key() ){
	
			this->keys.erase(it);	 
			this->keys.insert(it, in_subnode);
		
		}else if(*(in_subnode->get_key()) < *(*it)->get_key() ){
	
			this->keys.insert(it, in_subnode);
		}
			
		this->inc_key_count();
		
	}
	return 0;

}	
	
void Bp_Node::keys_clear_firsts( int end){
	
	vector<Bp_SubNode *>::iterator it = this->keys.begin();
	
	for( int i = 0; i < end ; i++ ){
	 
		keys.erase(it);
		this->dec_key_count();
	}
}

void Bp_Node::keys_clear_lasts( int begin){
	
	vector<Bp_SubNode *>::iterator it = this->keys.begin() + begin;
	
	while( it != this->keys.end() ){
 
		keys.erase(it);
		this->dec_key_count();
	}
		
}

Bp_SubNode* Bp_Node::get_first(){
	// OJO solo es el puntero a la clave, sirve para comparar solamente, 	

	vector<Bp_SubNode *>::iterator it = this->keys.begin();
	
	
	return *it;
	
	
}
Bp_SubNode* Bp_Node::get_last(){
	// OJO solo es el puntero a la clave, sirve para comparar solamente, 	

	vector<Bp_SubNode *>::iterator it = (this->keys.end() -1);
	
	return *it;
	
}

void Bp_Node::print_vec(){
	
	
	vector<Bp_SubNode *>::iterator it = this->keys.begin();
	
	if (this->keys.empty())
		cout << "VACIO!!\n";
	
	while( it != keys.end() ){		
		
		cout << (*(*it)->get_key()).ref.Serialize() << " ";	
		it++;
		
	}
	
	cout << endl;
}
			
 
 
void Bp_Node::save_vec(ofstream *file)
{
	
	vector<Bp_SubNode *>::iterator it = this->keys.begin();
	
	while( it != keys.end() ){
	Key_Node auxKey=(*(*it)->get_key());
	auxKey.Serialize(file);
    *file<< "Value"<<endl;
    *file<< auxKey.ref.Serialize()<<endl;
    *file<< "Value_End"<<endl;              
	it++;
	}
	cout << endl;
} 
    	
void Bp_Node::get_p_hijos( vector<Bp_Node *> &q_out ){		
	

	
	vector<Bp_SubNode *>::iterator it = keys.begin(); 
	
	q_out.push_back((Bp_Node *)((*it)->get_izq()));
	q_out.push_back((Bp_Node *)((*it)->get_der()));
	
	it++;
	
	
	while ( it != keys.end() ){
		
		q_out.push_back( (Bp_Node *)((*it)->get_der()) );
		it++;
	}
	
	
}

void Bp_Node::update_sep( Bp_SubNode *p_sep, Bp_Node *izq, Bp_Node *der ){
	
	
	vector<Bp_SubNode *>::iterator it = this->keys.begin();
	
	bool encon = false;
	while ( (it != keys.end()) && !encon ){
		
		if((*(*it)->get_key() < *(p_sep)->get_key() ))
			it++;
		else
			encon = true;
	}
	
	it--;
		
	// hago el update de los punteros.
	(*it)->set_der( (void *)der );
	
	
}

int Bp_Node::bpn_get_key(Key_Node &key){
	// ret codes:
	//		0 	existe, la devuelvo	
	//		1	no existe la clave
	
	
	vector<Bp_SubNode *>::iterator it = this->keys.begin();
	
	while ( key != *(*it)->get_key() ){
		it++;
		if( it == this->keys.end() ) {
				
			return 1;
		}
	}
	 
	key = *(*it)->get_key();
	return 0;  
}	


int Bp_Node::bpn_erase_key(Key_Node key){
	//	-1	vacio antes de eliminar
	//	1	no existia pero habia claves
	//	0	existia, la elimine
	
	vector<Bp_SubNode *>::iterator it = this->keys.begin();
	
	if ( !keys.empty() ){
		
// 		CAMBIO
// 		(*(*it)->get_key()).Print();
		(*(*it)->get_key()).ref.Serialize();
		while ( key != *(*it)->get_key() ){
			it++;	
			
			
// 			CAMBIO
// 			(*(*it)->get_key()).Print();
			(*(*it)->get_key()).ref.Serialize();
			if( it != keys.end() )	
				return 1;
		}
		cout << "son iguales\n";
		Bp_SubNode *aux = *it; 
		this->keys.erase(it);
		delete aux;
		this->dec_key_count();
	
		
	}
	return -1;
	
	
}



