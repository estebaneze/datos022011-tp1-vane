/*
 * UnderflowStrategy.cpp
 *
 *  Created on: Apr 28, 2010
 *      Author: carlos
 */

#include "UnderflowStrategy.h"
UnderflowStrategy::UnderflowStrategy() {

}
/**
 * Vemos si se le puede pedir al nodo hermano derecho.
 * Sino, le pedimos al nodo izquierdo.
 * Si no disparamos una fusion. Por optimizacion si el underflow
 * viene de un insert entonces no deberiamos llamar a la fusion.
 * Devolvemos true si cambio parent
 */
bool UnderflowStrategy::doBalance(Node* parent, BNode* child,BalanceStrategy* parentStrategy){
	//vemos si el hermano izquierdo tiene para prestarnos.
	bool parentHasChanged=false;

	if(child->isUnderflowded()){
		if(parentStrategy->getTypeOfStrategy()==INSERT){
			//Como es un insert solo verifico que el nodo hermano derecho pueda prestarme.
			parentHasChanged=this->doBalaceForRightNode(parent,child);
		}else{
			parentHasChanged=this->doBalanceForLeftNode(parent,child);
			if(!parentHasChanged){
				parentHasChanged=this->doBalaceForRightNode(parent,child);
			}
			if(!parentHasChanged){
				parentHasChanged=this->join(parent,child);
			}
		}
	}else{
		PersistorBTree* p=Persistor::getInstance();
		p->modify(child);
	}

	return parentHasChanged;
}

/**
 * Tratamos de hacer un join con el nodo izquierdo, sino puedo porque es el primer hijo, hago el split con el nodo derecho.
 * Split nodo izquierdo: tengo elminar la clave que guardaba el parent del child.
 * Split nodo derecho: tengo que cambiar la clave del nodo derecho por la mas pequeña de child.
 *
 * Algoritmo
 */
bool UnderflowStrategy::join(Node* parent,BNode* childInUnderflow){
		bool hasChanged=false;
		PersistorBTree* p=Persistor::getInstance();
		BNode* leftSibling=parent->getLeftSibling(childInUnderflow);
		if(leftSibling!=NULL){
			leftSibling->join(childInUnderflow);
			parent->removeKey(childInUnderflow);
			p->removeBlock(childInUnderflow->getOffset());
			p->modify(leftSibling);
			hasChanged=true;
		}else{
			BNode* rightSibling=parent->getRightSibling(childInUnderflow);
			childInUnderflow->join(rightSibling);
			p->removeBlock(rightSibling->getOffset());
			parent->removeKey(rightSibling);
			p->modify(childInUnderflow);
			hasChanged=true;
		}
		return hasChanged;
}

/**
 * Verificamos que el hermano izquierdo tiene para prestarnos.
 * De ser asi hay que cambiar la clave del padre que apunta a child por la nueva clave
 *
 * Devolvemos true si cambio parent y por consiguiente pudo balancear
 */
bool UnderflowStrategy::doBalanceForLeftNode(Node* parent, BNode* childInUnderflow){
	bool hasChanged=false;
	PersistorBTree* p=Persistor::getInstance();

	BNode* leftSibling=parent->getLeftSibling(childInUnderflow);
	if(leftSibling!=NULL){
		hasChanged=leftSibling->leftBalanceWith(childInUnderflow);
		if(hasChanged){
			p->modify(leftSibling);
			p->modify(childInUnderflow);
			parent->changeKey(childInUnderflow);
			hasChanged=true;
		}
	}
	return hasChanged;
}
/**
 * Verificarmos si el hermano  derecho tiene para prestarnos.
 * De ser asi hay que cambiar la clave del padre que apunta al nodo derecho, por
 * la nueva clave.
 *
 * Devolvemos true si cambio parent y por consiguiente pudo balancear
 *
 */
bool UnderflowStrategy::doBalaceForRightNode(Node* parent, BNode* childInUnderflow){
	bool hasChanged=false;
	PersistorBTree* p=Persistor::getInstance();
	BNode* rightSibling=parent->getRightSibling(childInUnderflow);
	if(rightSibling!=NULL){
		hasChanged=rightSibling->rightBalanceWith(childInUnderflow);
		if(hasChanged){
			//como cambio persisto el hijo derecho y quito la clave del padre cambiandola por la nueva
			p->modify(rightSibling);
			p->modify(childInUnderflow);

			parent->changeKey(rightSibling);
		}
	}
	return hasChanged;

}

UnderflowStrategy::~UnderflowStrategy() {
}
