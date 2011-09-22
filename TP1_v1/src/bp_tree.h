/**
	Esta clase es la clase arbol B+. Utiliza para armarse
	objetos tipo nodo de la clase bp_node

*/


#ifndef BP_TREE_H
#define BP_TREE_H

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <sstream>
#include "bp_subnode.h"
#include "bp_node.h"
#include "key_node.h"

#define FROM_START 0
#define END -1




using namespace std;

typedef struct Rebalance_Pointers{
	
	Bp_Node *root;
	Bp_Node *for_balance;
	
};

class Bp_Tree{

private:
	Bp_Node *root; 		// puntero a la raiz
	int altura;		// es el nivel de la raiz. Las hojas tienen nivel 1.

	std::string filename;
	int insert_key( Key_Node &key, Bp_Node *in_node );
	// por ahora es asi pero esto deberia levantarse de un archivo;
	unsigned short int min_int_node_keys;
	unsigned short int max_keys;
	unsigned short int d;			//es el d de :  d <= keys <= 2d
	
	
		
	void up_key(Key_Node *key);
	void split_root(Bp_Node *actual_root);
	void split_leave(Bp_Node *over_node);
	Bp_Node* get_padre(Key_Node *test_key, int level_hijo);
// 	void actual_separadores();
	int get_altura(){ return this->altura;}
	
	// search supone: que si es la clave es menor que el separador, entonces izq, mayor igual, derecha.
	Bp_Node* search_tree( Key_Node key);
		
	int get_min_int_node_keys(){ return this->min_int_node_keys; }
	
	unsigned short int get_mk(){ return this->max_keys; } 
	
	Bp_Node* get_root(){ return this->root;}
	void up_key_sep( Bp_Node *into_node, Bp_SubNode *subnode_in);
	
	bool is_leave();
	bool is_root();
	bool empty_tree();
	int check_which_case_of_split(Bp_Node *from);
public:
	
	Bp_Tree(std::string filename);
	Bp_Tree(std::string filename,int d);
	
	~Bp_Tree();
	
	

	
	int add_key( Key_Node &key , bool update);	// inserta la clave en la hoja. Si update es true 
							// significa que ante la posibilidad de que existiese la
	 						// pisa,   
							// return codes:	0	no existia la clave  y se 
							// 				inserto.
							//			1	existia	-> y se inserto
							// 			2	existia -> no se inserto
							// El Modo Consulta es poniendo la Key que quiero ver si
	 						// existe y update = false. Ver retorno
	
	int get_key( Key_Node &key );	
	void print_tree();

 	void load();
 	void save();
	int erase_key( Key_Node key );
	// begin = NULL, end = NULL es desde la clave menor hasta la mayor. Se pueden combinar
	vector<Key_Node *> secuencial_search( Key_Node *begin, Key_Node *end );	 
	

};

#endif
/**
http://www.virtual.unal.edu.co/cursos/ingenieria/2001412/capitulos/cap8/85.html
se define un árbol-B+ de la siguiente manera:

   1.

      SE MANEJA COMO ARBOL B! cada nodo tiene entre d y 2d claves.
   2.

      Cada nodo, excepto la raíz, tiene entre d + 1 y 2d + 1 descendientes. Se utiliza m para expresar el numero
	de elementos por nodo.
   3.

      La nodo raíz tiene al menos dos descendientes.
   4.

      Los nodos hojas están todas al mismo nivel.
   5.

      Todas las claves se encuentran en los nodos hojas 
   6.

      Las claves de los nodos raíz e interiores se utilizan como índices.
   7.

      Búsqueda De Arboles-B+ 

El proceso de inserción: cuando desea insertarse una clave en una pagina que se encuentra llena ( m = 2d ). En este caso, la pagina afectada se divide en 2, distribuyéndose las m + 1 claves de la siguiente forma: " las d + 1 primeras claves en la pagina de la izquierda y las restantes claves en la pagina derecha ". Una copia de la clave del medio sube a la pagina antecesora. 
*/
