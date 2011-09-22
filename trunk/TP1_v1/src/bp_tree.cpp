/***************************************************************************
             *
 ***************************************************************************/
#include <iostream>
#include <queue>
#include <vector>

#include "bp_tree.h"
#include "bp_node.h"
#include "bp_subnode.h"
#include <assert.h>

using namespace std;

// cuando creo el arbol creo un nodo vacio. Esto puede ser ineficiente solo cuand el arbol 
// no se carga con ninguna clave, entonces tengo un nodo vacio que usa espacio. 

// Bp_Tree::Bp_Tree(std::string filename){
Bp_Tree::Bp_Tree(std::string filename,int d){

 	
 	this->altura = 1;
	this->min_int_node_keys = 1;	// por definicion de B+ un nodo interno no puede tener menos de 2 claves
	this->d = d; 
	this->max_keys = 2 * d;
	
	
	this->root = new Bp_Node(this->altura);
	this->root->set_root( true );
	this->root->set_leave( true );
	
	
	this->filename=filename;
	
	ifstream file(filename.c_str());
      if (file.is_open())
      {
         file.close();
         load();
      }  
      else 
      {
          ofstream ofile(filename.c_str(),ios::trunc);
          ofile.close();
      }   
    
}

Bp_Tree::Bp_Tree(std::string filename){

    this->altura = 1;
	this->min_int_node_keys = 1;	// por definicion de B+ un nodo interno no puede tener menos de 2 claves
	this->d = 2; 
	this->max_keys = 2 * d;
	
	
	this->root = new Bp_Node(this->altura);
	this->root->set_root( true );
	this->root->set_leave( true );

	
	this->filename=filename;
	
	ifstream file(filename.c_str());
      if (file.is_open())
      {
         file.close();
         load();
      }  
      else 
      {
          ofstream ofile(filename.c_str(),ios::trunc);
          ofile.close();
      }   
 
	
    
}


void Bp_Tree::load()
{
     ifstream *file=new ifstream(this->filename.c_str());
     std::string aux;

	 cout<<"load"<<endl;
    
      Key_Node auxk=  Key_Node();
     while(!file->eof())
     {
                        
                        getline(*file,aux);
                       
                       if ( aux.compare("D")==0)
                        {
                              getline(*file,aux);
                            stringstream D(aux);
                            
                           D>>this->d;
                           this->max_keys = 2 * d;
            
                        }
                       
                        if ( aux.compare("Begin_Key_Node")==0)
                        {

                            auxk.DesSerialize(file);   
            
                        }
                          if ( aux.compare("Value")==0)
                        {
                                     getline(*file,aux);
                    				stringstream ss(aux);
            
                    				Refs auxRef= Refs(ss.str());
                    				
                    				Key_Node * pKN= new Key_Node();
                    				auxk.ref=auxRef;
                    				*pKN=auxk;
                    				
                    				
                  				
                                     add_key(*pKN ,true);    
                                     print_tree();  
                        }
                        
     }                                                                
}

void Bp_Tree::save()
{
    std::ofstream *file= new ofstream(this->filename.c_str(),ios::trunc);
   
	vector<Bp_Node *> cola;
	cola.push_back(this->root);
	Bp_Node *aux;
	vector<Bp_Node *>::iterator it;	
	
	*file<<"D"<<endl;
	*file<<this->d<<endl;
	
	while( !cola.empty() ){
				
		aux = cola.front();
		aux->save_vec(file);

		cola.erase(cola.begin());
		
		if ( !aux->is_leave() )
			aux->get_p_hijos( cola );
		it = cola.begin();
	
		if( cola.size() > 1 ){
			while( (it +1) != cola.end() ){
   				if ( ( (*it) == *( it +1 )) )
	
					cola.erase(it);
				else
					it++;		
			}
		}	
	
	}
     
   file->close();
   delete(file); 
}


Bp_Tree::~Bp_Tree(){
	
	delete this->root;
	
	
	
}

int Bp_Tree::add_key( Key_Node &key , bool update){
	
	int ret_code = -1;
	
	if ( this->root->is_leave() ){
		// si la raiz es hoja
		
		ret_code = this->root->bpn_insert_key(key, update);			
			
		
		if ( this->root->get_kc() ==  (this->get_mk() + 1 ))	// si la cant de k == max+1 split.	
			
			this->split_root(this->root);
		
					
		//si la raiz no es hoja		
	}else{
		
		Bp_Node *p_aux = NULL;
		
		p_aux = this->search_tree( key );	//  ahora en p_aux tengo apuntado el nodo hoja 
		ret_code = p_aux->bpn_insert_key( key, update );
		
		// me fijo si hay overflow
		
		if ( p_aux->get_kc() > this->get_mk() )		 // si esta llena		
		
			this->split_leave(p_aux);		// divido la hoja
		
		
	}
	
	return ret_code;

}
	
Bp_Node* Bp_Tree::search_tree( Key_Node key ){
	
	
	
	Bp_Node *p_aux = this->get_root();
	
	
	
	while( !p_aux->is_leave() ){
		
		
		p_aux = p_aux->get_follow_pointer(key);
						
	}
	
	
	return p_aux;
		
}

bool Bp_Tree::empty_tree(){
	
	if (this->root->is_leave() && ( this->root->get_kc() == 0 ) )
		return true;
	else
		return false;
}

void Bp_Tree::up_key_sep( Bp_Node *into_node, Bp_SubNode *subnode_in){
	
	
	into_node->insert_subnode(subnode_in);
		
	if ( into_node->get_kc() > this->max_keys ){ //lleno?
		
		
		if ( into_node->get_level() == 1 ){
			
			cout << "WARNING!!!  Lo PARTO como HOJA- no deberia darse\n" << endl;
			split_leave(into_node);
			assert(into_node->get_level() == 1);
			
		}else{
			
			if ( into_node->get_level() == this->altura )
			
				split_root(into_node);			// Si es root parto la raiz
			
			
			else
				split_leave( into_node );
				
			
		}
		
	}
	
}

void Bp_Tree::split_root(Bp_Node *actual_root){

	Bp_Node *p_aux_izq = new Bp_Node(actual_root->get_level());	//los nuevos nodos tienen el nivel de la actual raiz
	Bp_Node *p_aux_der = new Bp_Node(actual_root->get_level());
	this->altura++;						// incremento la altura del arbol
	
	
	if ( actual_root->get_level() == 1 ){			// si root era hoja. a los nvos nodos
	
		p_aux_izq->set_leave( true );			// los seteo como hoja
		p_aux_der->set_leave( true);
		p_aux_izq->set_menor(NULL);
		p_aux_izq->set_mayor(p_aux_der);
		p_aux_der->set_mayor(NULL);
		p_aux_der->set_menor(p_aux_izq);
		
	}else{
	
		p_aux_izq->set_leave( false );			// Por si acaso
		p_aux_der->set_leave( false );
	
		p_aux_izq->set_menor(NULL);
		p_aux_izq->set_mayor(NULL);
		p_aux_der->set_mayor(NULL);
		p_aux_der->set_menor(NULL);
	}
	
	p_aux_izq->set_root( false );			
	p_aux_der->set_root( false );
	actual_root->set_leave(false);		// ya no es mas hoja, por si lo era
	
	
	
	// reparto las claves
	int max_izq = (this->d) + 1;
	
	// copio las claves, la mitad + 1 al nodo izq y el resto al der.
	p_aux_izq->copy_keys( actual_root->get_vector_keys( 0 , max_izq ) );
	p_aux_der->copy_keys( actual_root->get_vector_keys( max_izq, -1 ) );	// -1 para ir hasta vector.end()
	
	// borro las keys (punteros) que hay el nodo root
	actual_root->keys_clear();						// vacio el ex root
	actual_root->set_key_count(0);
		
	
	// a mi root actual le subo el separador que saco del hijo derecho, y actualizo su altura, etc.
	// get_separador devuelve un objeto sub_node
	
	Bp_SubNode *aux = p_aux_der->get_separador(p_aux_izq, p_aux_der) ;
	
	int temp = actual_root->get_level() + 1;
	actual_root->set_level(temp);	
	
	// apunto el separador a los hijos
	aux->set_izq(p_aux_izq);
	aux->set_der(p_aux_der);
	
// le paso el puntero al root donde tiene que insertar el separador y el puntero aux al separador (subnodo)
	up_key_sep(actual_root, aux );
	
	
}

void Bp_Tree::split_leave(Bp_Node *over_node){			//apunta al nodo saturado

	
	
	if (over_node->get_level() > 1 ){			// no es hoja, es nodo intermedio

	// aca decido si la bifurcacion es iqz, der o central.
					
		
		
		
// 		
		switch ( check_which_case_of_split( over_node ) ){
			case 1:{
				
				Bp_Node *p_aux_izq = new Bp_Node(over_node->get_level());
				p_aux_izq->set_leave(false);
				p_aux_izq->set_root(false);
				
				
				// copio los punteros a sub_node del vector del nodo saturado al nuevo nodo
				int mkeys =  (this->d + 1) ; 
		
				// copio las ulitmas claves, empezando de d+1
				p_aux_izq->copy_keys( over_node->get_vector_keys( 0, mkeys) );
		
				// borro desde d+1 hasta el final
				over_node->keys_clear_firsts(mkeys);
		
				// buscar padre
                		// primero me agarro una clave de muestra (cualquiera) para acelerar la busqueda

				Key_Node *aux_key = (p_aux_izq->get_first())->get_key();
				Bp_Node *padre = this->get_padre(aux_key, p_aux_izq->get_level());
		
				// Creo un objeto separador, copia del primer elem del nodo nuevo,  
				Bp_SubNode *p_separador = over_node->get_separador( p_aux_izq , over_node );
				// actualizo el separador siguiente al que inserte. Solo pasa en nodos internos
		
		
				padre->update_sep( p_separador, NULL, p_aux_izq );
				// subo la clave derecha y le paso los punteros de sus hijos
				up_key_sep( padre, p_separador );
		
		
				break;
			
			}case 2:{	// split izq
			
				Bp_Node *p_aux_izq = new Bp_Node(over_node->get_level());

				p_aux_izq->set_leave(false);
				p_aux_izq->set_root(false);
				// copio los punteros a sub_node del vector del nodo saturado al nuevo nodo
				int mkeys =  (this->d + 1) ; 
		
				// copio las ulitmas claves, empezando de d+1
				p_aux_izq->copy_keys( over_node->get_vector_keys( 0, mkeys) );
		
				// borro desde d+1 hasta el final
				over_node->keys_clear_firsts(mkeys);
		
		 		// buscar padre
                		// primero me agarro una clave de muestra (cualquiera) para acelerar la busqueda

				Key_Node *aux_key = (p_aux_izq->get_first())->get_key();
				Bp_Node *padre = this->get_padre(aux_key, p_aux_izq->get_level());

                		// subo la clave derecha y le paso los punteros de sus hijos
				up_key_sep( padre, over_node->get_separador( p_aux_izq , over_node ) );
								
				break;
			
			}case 3:{	// split der
				
				Bp_Node *p_aux_der = new Bp_Node(over_node->get_level());
				
				p_aux_der->set_leave(false);
				p_aux_der->set_root(false);
		
				// copio los punteros a sub_node del vector del nodo saturado al nuevo nodo
				int mkeys =  (this->d + 1) ; 
		
				// copio las ulitmas claves, empezando de d+1
				p_aux_der->copy_keys( over_node->get_vector_keys( mkeys, -1 ) );
		
				// borro desde d+1 hasta el final
				over_node->keys_clear_lasts(mkeys);
		
		
		
				// buscar padre
                		// primero me agarro una clave de muestra (cualquiera) para acelerar la busqueda
		
				Key_Node *aux_key = (p_aux_der->get_first())->get_key();
		
				Bp_Node *padre = this->get_padre(aux_key, p_aux_der->get_level());
		
                		// subo la clave derecha y le paso los punteros de sus hijos
				up_key_sep( padre, p_aux_der->get_separador( over_node , p_aux_der ) );
				
				break;
			}
				
			
		}
		
	}else if ( (over_node->get_menor() != NULL) && (over_node->get_mayor() != NULL) ) {	// si es hoja del 
												// medio

	
		Bp_Node *p_aux_izq = new Bp_Node(over_node->get_level());

		// los apunto
		
		p_aux_izq->set_menor(over_node->get_menor());
		p_aux_izq->set_mayor(over_node);
		
		// al actual mayor del nodo saturado, le pongo el nuevo menor, o sea el nodo creado
		over_node->get_menor()->set_mayor(p_aux_izq);
		
		// actualizo el mayor del nodo saturado, o sea el nuevo nodo
		over_node->set_menor(p_aux_izq);
		
			
		// copio los punteros a sub_node del vector del nodo saturado al nuevo nodo
		int mkeys =  (this->d + 1) ; 
		
		// copio las ulitmas claves, empezando de d+1
		p_aux_izq->copy_keys( over_node->get_vector_keys( 0, mkeys) );
		
		// borro desde d+1 hasta el final
		over_node->keys_clear_firsts(mkeys);
		
		// buscar padre
                // primero me agarro una clave de muestra (cualquiera) para acelerar la busqueda

		Key_Node *aux_key = (p_aux_izq->get_first())->get_key();
		Bp_Node *padre = this->get_padre(aux_key, p_aux_izq->get_level());
		
		// Creo un objeto separador, copia del primer elem del nodo nuevo,  
		Bp_SubNode *p_separador = over_node->get_separador( p_aux_izq , over_node );
		// actualizo el separador siguiente al que inserte. Solo pasa en nodos internos
		
		
		padre->update_sep( p_separador, NULL, p_aux_izq );
		// subo la clave derecha y le paso los punteros de sus hijos
		up_key_sep( padre, p_separador );
	
		
	}else if ( over_node->get_menor() == NULL ){				// si es hoja izquierda
		
		Bp_Node *p_aux_izq = new Bp_Node(over_node->get_level());

		// los apunto
		p_aux_izq->set_menor(NULL);
		p_aux_izq->set_mayor(over_node);
		
		// al actual mayor del nodo saturado, le pongo el nuevo menor, o sea el nodo creado
		over_node->set_menor(p_aux_izq);
		//
		
		
		// copio los punteros a sub_node del vector del nodo saturado al nuevo nodo
		int mkeys =  (this->d + 1) ; 
		
		// copio las ulitmas claves, empezando de d+1
		p_aux_izq->copy_keys( over_node->get_vector_keys( 0, mkeys) );
		
		// borro desde d+1 hasta el final
		over_node->keys_clear_firsts(mkeys);
		
		
		
		 // buscar padre
                // primero me agarro una clave de muestra (cualquiera) para acelerar la busqueda

		Key_Node *aux_key = (p_aux_izq->get_first())->get_key();
		Bp_Node *padre = this->get_padre(aux_key, p_aux_izq->get_level());

                // subo la clave derecha y le paso los punteros de sus hijos
		up_key_sep( padre, over_node->get_separador( p_aux_izq , over_node ) );
		
		
	
	}else if (over_node->get_mayor() == NULL) {
		
		
		Bp_Node *p_aux_der = new Bp_Node(over_node->get_level());
		
		// los apunto
		p_aux_der->set_menor(over_node);
		
		p_aux_der->set_mayor(NULL);
		
		// al actual mayor del nodo saturado, le pongo el nuevo menor, o sea el nodo creado
		over_node->set_mayor(p_aux_der);
		
		
		// copio los punteros a sub_node del vector del nodo saturado al nuevo nodo
		int mkeys =  (this->d + 1) ; 
		
		// copio las ulitmas claves, empezando de d+1
		p_aux_der->copy_keys( over_node->get_vector_keys( mkeys, -1 ) );
		
		// borro desde d+1 hasta el final
		over_node->keys_clear_lasts(mkeys);
		
		
		
		// buscar padre
                // primero me agarro una clave de muestra (cualquiera) para acelerar la busqueda
		
		Key_Node *aux_key = (p_aux_der->get_first())->get_key();
		
		Bp_Node *padre = this->get_padre(aux_key, p_aux_der->get_level());
		
                // subo la clave derecha y le paso los punteros de sus hijos
		up_key_sep( padre, p_aux_der->get_separador( over_node , p_aux_der ) );
		
			
	}else
		cout << " ERROR: No es ni hoja del medio, ni izq, ni der\n";
}

Bp_Node* Bp_Tree::get_padre(Key_Node *test_key, int level_hijo){
	
	Bp_Node *p_padre = this->root;
	
	
	if ( ( this->get_altura() - level_hijo ) > 1 ){
			
			
		while ( p_padre->get_level() >= (level_hijo + 2) )
			p_padre = p_padre->get_follow_pointer( *test_key);
		
	}
	
	return p_padre;
	
}

void Bp_Tree::print_tree(){

	vector<Bp_Node *> cola;
	cola.push_back(this->root);
	
	Bp_Node *aux;
	vector<Bp_Node *>::iterator it;	
	
	while ( !cola.empty() ){

		aux = cola.front();
		cout << "\n Nivel : " << aux->get_level() << endl;
		aux->print_vec();
		
		cola.erase(cola.begin());
		
		if ( !aux->is_leave() )

			aux->get_p_hijos( cola );
		

//		borro duplicados	
		it = cola.begin();
	
		if( cola.size() > 1 ){
			while( (it +1) != cola.end() ){
			
				
				if ( ( (*it) == *( it +1 )) )
	
					cola.erase(it);
				else
					it++;		
			}
		}
	}
	
}	

int Bp_Tree::get_key( Key_Node &key ){
	// ret codes:
	//		0 	existe, la devuelvo	
	//		1	no existe la clave
	
	Bp_Node *aux = search_tree(key);
	int ret = -1;
	ret = aux->bpn_get_key(key);
	
	return ret;	
	
	
	
	
}

int Bp_Tree::erase_key( Key_Node key ){
	//	-1	vacio antes de eliminar
	//	1	no existia pero habia claves
	//	0	existia, la elimine
	
	Bp_Node *aux = this->search_tree(key);
	int ret = aux->bpn_erase_key(key);
	return ret;
}


int Bp_Tree::check_which_case_of_split(Bp_Node *from){
	
	// puntero a nodo que voy chequeando		
	Bp_Node *p_aux = from;
	
	Bp_SubNode *sbn_aux = NULL;
	
	// voy bajando por el menor hasta la hoja
	
	
	 
	while ( p_aux->get_level() != 1 ){
	
		sbn_aux = p_aux->get_first();
		p_aux =  (Bp_Node *)(sbn_aux->get_izq());
	
	}
	// si es NULL entonces es nodo izq
	
	if ( p_aux->get_menor() == NULL )
		return 2;
	
	p_aux = from;
	
	// voy bajando por el nodo mayor hasta la hoja
	while ( p_aux->get_level() != 1 ){
		  
		
		sbn_aux = p_aux->get_last();
		p_aux =  (Bp_Node *)(sbn_aux->get_der());
		
	}
	// si es NULL entonces es nodo der
	if ( p_aux->get_mayor() == NULL )
		return 3;
	
	else 	// es centro
		return 1;

}

vector<Key_Node *> Bp_Tree::secuencial_search( Key_Node *begin, Key_Node *end ){
		 
	Bp_Node *p_begin = NULL;
	Bp_Node *p_end = NULL;
	Bp_SubNode *sbn_aux = NULL;
	
		
	if ( (begin != NULL) && (end != NULL) ){
		
		if ( *begin > *end ){		// para prevenir errores de clave mayor, menor.	
 		Key_Node *aux;
 		aux = begin;
 		begin = end;
 		end = aux;
	 	}
	}
	
	// vector de salida
	vector<Key_Node *> vec_output;
	p_begin =  this->root;
	
	// seteo el begin
	if ( begin == NULL ){
			
		while ( p_begin->get_level() != 1 ){
		  
			sbn_aux = p_begin->get_first();
			p_begin =  (Bp_Node *)(sbn_aux->get_izq());
			
		}
	
	}else{
		
		p_begin = search_tree( *begin );
		
	}
	
	// seteo el end
	p_end =  this->root;
	if ( end == NULL ){
	
		while ( p_end->get_level() != 1 ){
	  
			sbn_aux = p_end->get_last();
			p_end =  (Bp_Node *)(sbn_aux->get_der());
	
		}
	
	}else{
		
		p_end = search_tree( *end );
		
	}
	
	
	
	if ( p_begin == p_end ){
		
		// saco DESDE la clave (inclusive) en adelante.
// 		p_begin->get_keys( begin,vec_output, false );
		p_begin->get_interval_keys( begin, end, vec_output );
		
	
	
	}else{

	
		// saco DESDE la clave (inclusive) en adelante.
		p_begin->get_keys( begin,vec_output, true );
		p_begin = p_begin->get_mayor();
		
		vector<Key_Node *>::iterator it;
		it = vec_output.begin();
		
	
		while ( p_begin != p_end ){
			
			p_begin->get_keys(NULL, vec_output, false );
			p_begin = p_begin->get_mayor();
			
		}
	
		p_begin->get_keys( end, vec_output, false );	
		
	}		
	return vec_output;
	
}











