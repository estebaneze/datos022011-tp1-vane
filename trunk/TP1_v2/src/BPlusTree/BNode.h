#ifndef BNode_h
#define BNode_h

#include "../utils/const.h"
#include "../Persistence/Block.h"
#include "../utils/types.h"
#include "Element.h"
#include <string>
#include "KeyElement.h"
#include "../utils/ConfigurationMananger.h"
#include <iostream>
using namespace std;

class LeafNode;

class BNode : public Block {
private:
	Level level;

public:
	BNode();

	virtual ~BNode();

	virtual LeafNode *find(Key key) = 0;
	virtual Element *findExact(Key key) = 0;

	/**
	 * Devuelve el ultimo key element.
	 * Este metodo se usa cuando se realiza un split.
	 */
	void setLevel(Level level);

	Level getLevel();

	virtual bool isOverflowded(int modifyOrInsert)=0;
	virtual bool isUnderflowded() = 0;
	/**
	 * True implica que se modifico el nodo.
	 * False implica que no se modifico.
	 * Para el caso de overflow el nodo se modifica dejadolo
	 * listo para que se le haga un split, esto implica que hay que grabarlo
	 * En caso de no poder insertar hay que arrojar una excepcion. El unico caso que se me ocurre por el cual no se puede insertar es
	 * por elemento duplicado
	 * Se puede arrojar una excepcion. Lo implemente con excepcion una vez y no quedo bien.
	 *
	 */
	virtual bool insertar(Element* elem)=0;

	/**
	 * Modifica el elemento cuya clave coincide con el que se pasa. En el caso de overflow el nodo inserta el elemento y es
	 * responsabilidad del padre verificar si hay que partirlo o no.
	 * En caso de Underflow es igual, el nodo se modifica y deja al padre la responsabilidad de balancear la carga o bien contraer el nodo.
	 * En caso de no encontrarlo arroja una exception.
	 */
	virtual bool modify(Element* elemToModify)=0;

	/**
	 * Elimina el elemento cuya clave es Key
	 */
	virtual bool remove(Key key)=0;
	/**
	 *Realiza el split. Nunca deja a este nodo (this) en underlfow.
	 */
	virtual KeyElement* doSplit()=0;

	/**
	 * Balancea con el sibling, devuelve true si cambiaron (ambios this y sibling)
	 * false en caso contrario.
	 * Pasa los primeros elementos de este nodo al sibling (hermano)
	 */
	virtual bool rightBalanceWith(BNode* sibling)=0;

	/**
	 * Balancea con el sibling, devuelve true si cambiaron (ambios this y sibling)
	 * false en caso contrario.
	 * Pasa los ultimos elementos de este nodo al sibling (hermano)
	 */
	virtual bool leftBalanceWith(BNode* sibling)=0;

	/**
	 * Pasa los elementos de siblin al este nodo.
	 * Los elementos de sibling se agregan al final.
	 */
	virtual bool join(BNode* sibling)=0;
	/**
	 * Devuelve la primer clave
	 */
	virtual Key getFirstKey()=0;


	/********************************************
	 * *************Persistencia ****************
	 ********************************************/
	void modify();

	virtual RegisterCounter getRegisterCounter()=0;
	virtual std::string serialize();
	virtual void unserialize(std::string &buffer);

	/* Devuelve el tama�o de los datos del nodo: Level y RegisterCount */
	virtual int getDataSize();
	friend ostream& operator<<(ostream&,BNode&);
	virtual ostream& printMe(ostream&)=0;
	virtual void exportNode()=0;
};

inline ostream& operator<<(ostream& myOstream, BNode& bnode){
	return bnode.printMe(myOstream);
}
#endif // BNode_h
