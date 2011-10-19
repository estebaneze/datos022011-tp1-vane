/*
 * ABMEleccion.cpp
 *
 *  Created on: 19/10/2011
 *      Author: minnie
 */

#include "ABMEleccion.h"

ABMEleccion::ABMEleccion(string btreeFile, string indexByFechaFile, string indxByCargoFile) {

	this->bpTreeFile= Helper::concatenar(btreeFile,"bpt",".");
	this->bplusTree = new BPlusTree(2048,this->bpTreeFile);

	this->indexByFecha = new Index(Helper::concatenar(btreeFile,"Fecha","_"));
	this->indexByCargo = new Index(Helper::concatenar(btreeFile,"Cargo","_"));

}

ABMEleccion::~ABMEleccion() {
	// TODO Auto-generated destructor stub
}
