#ifndef BPlusTree_h
#define BPlusTree_h

#include "../utils/const.h"
#include "BNode.h"
#include "Node.h"
#include "LeafNode.h"
#include <string>
#include "Element.h"
#include "../Persistence/Persistor.h"
#include "NodeFactory.h"
#include "../exceptions/ElementNotFoundException.h"
#include "../Persistence/exceptions/PersistExceptions.h"

using namespace std;
class BPlusTree {

 private://variables privadas
    BNode* root;
    LeafNode* current;

 private://metodos privados
    /**
     * Recibe el elemento y un entero que indica si hayque modificar o insertar
     */
    void insert(Element* elem,int modifyOrInsert);

    /**
     * Devuelve el nodo hoja izquierdo
     */
    LeafNode* getLeftLeafNodo(BNode* actualNode);

    void validateElementSize(Element* elem);
 public:
    /**
     * Este constructor se utiliza cuando el Persistor ya fue inicializado
     */
    BPlusTree();
    /**
     * Tamaño del nodo que tendra el arbol y el nombre del archivo con el cual se va a guardar
     */
    BPlusTree(int nodeSize, string fileName);

    /**
     * Exporta el arbol desde su raiz.
     */
    void exportTree();


    /**
     * Exporta un nodo del arbol
     */
    void exportTree(int blockNumber);
    /**
     *  Destructor del arbol.
     */
    virtual ~BPlusTree();

	/**
	 * Inserta un nuevo Element en el arbol su clave (key).
	 * Si la clave está presente en el arbol antes de su inserción, este
	 * metodo lanzará una excepcion.
	 */
    void insert(Element* element);

	/**
	 * Elimina un elemento del arbol por su clave.
	 * En el caso que la clave no se encuentre en el arbol, este
	 * metodo lanzará una excepcion.
	 */
    void remove(Key key);

	/**
	 * Modifica la información del elemento definido por su clave.
	 */
    void modify(Element* elem);


	/**
	 * Buscador del árbol. Devuelve el Nodo contenedor de la clave buscada.
	 */
    LeafNode* find(Key key);
    Element* findExact(Key key);
	/**
	 * Navega por la lista secuencial de los nodos
	 * hojas hacia adelante.
	 */
    BNode* next();

	/**
	 * Navega por la lista secuencial de los nodos
	 * hojas hacia atras.
	 */
    BNode* prev();

	/**
	 * Metodo para eliminar el Arbol de su ubicación física.
	 */
    void deleteTree();


};



#endif // BPlusTree_h
