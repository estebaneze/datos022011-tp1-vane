/*
 * BPlusTreeTest.cpp
 *
 *  Created on: Apr 17, 2010
 *      Author: carlos
 */

#include "BPlusTreeTest.h"
#include "BPlusTree/BPlusTree.h"
#include "Persistencia/PersistorBase.h"
#include "Persistencia/Persistor.h"
#include "utils/ConfigurationMananger.h"
#include "Common/Helper.h"

using namespace std;

BPlusTreeTest::BPlusTreeTest() {
}

void BPlusTreeTest::run() {

	system("rm testTree");
	system("rm testTree.fs");

	this->bplus = new BPlusTree(
			ConfigurationMananger::getInstance()->getBufferSizeTree(),
			"testTree");

	BPlusTree& bplus = *this->bplus;
	cout << "***************************************" << endl;
	cout << "Ejecutando el primer set de test" << endl;
	cout << "***************************************" << endl;
	this->firstSetTest();

	/*cout << "***************************************" << endl;
	cout << "Ejecutando el segundo set de test" << endl;
	cout << "***************************************" << endl;
	this->secondSetTest();
	cout << "***************************************" << endl;
	cout << "Ejecutando el tercer set de test" << endl;
	cout << "***************************************" << endl;
	this->thirdSetTest();*/
}

void BPlusTreeTest::firstSetTest() {
	system("rm testTree");
	system("rm testTree.fs");

	BPlusTree& bplus = *this->bplus;
	int i;

	//<< "Insertamos los elementos 100, 101, 102,103,104 todos con 4 bytes de datos: total de cada registro en el nodo hoja= 12 bytes"
	//<< endl;
	for (i = 100; i < 105; i++) {

		Key key =  Helper::IntToString(i);

		cout << "Insertando el elemento: " << key << endl;
		string str = key.append("xxx");
		Data data = (Data)str.c_str();
		bplus.insert(new Element(key, data, 4));

		//bplus.exportTree();
		//getchar();
	}
	cout << endl;

	bplus.exportTree();

	cout << "Buscando el elemento 104" << endl;
	Element& element = *bplus.findExact("104");
	cout << "************Elemento encontrado: " << element << endl << endl;

	cout << "Modificando elemento elmentos 101 y 103 sin split" << endl;
	bplus.modify(new Element("101", "12xxxxxxxxxx", 12));
	bplus.modify(new Element("102", "12xxxxxxxxxx", 12));
	bplus.exportTree();
/*
	cout << "Modificando elemento elmento 103 generando split" << endl;
	bplus.modify(new Element("103", "9xxxxxxxx", 9));
	bplus.exportTree();
	cout << "Eliminamos el elemento 103" << endl;
	bplus.remove("103");
	bplus.exportTree();
	cout << "Modificamos el elemento 102" << endl;
	bplus.modify(new Element("102", "1", 1));
	bplus.exportTree();
	cout << "eliminamos la clave 104 y se produce un balanceo" << endl;
	bplus.remove("104");
	bplus.exportTree();
	cout << "eliminamos la clave 100" << endl;
	bplus.remove("100");
	bplus.exportTree();
	cout << "eliminamos la clave 101" << endl;
	bplus.remove("101");
	bplus.exportTree();
	cout << "eliminamos la clave 102" << endl;
	bplus.remove("102");
	bplus.exportTree();
*/
	cout << "end..........." << endl;

}

void BPlusTreeTest::secondSetTest() {
/*	system("rm testTree");
	system("rm testTree.fs");
	BPlusTree& bplus = *this->bplus;
	int i;
	cout
			<< "Insertamos los elementos 100, 101, 102,103,104 todos con 4 bytes de datos: total de cada registro en el nodo hoja= 12 bytes"
			<< endl;
	for (i = 100; i < 105; i++) {
		cout << "Insertando el elemento: " << i << endl;
		bplus.insert(new Element(i, "4xxx", 4));
		//bplus.exportTree();
		//getchar();
	}
	cout << endl;

	bplus.exportTree();

	cout << "Buscando el elemento 104" << endl;
	Element& element = *bplus.findExact(104);
	cout << "************Elemento encontrado: " << element << endl << endl;

	cout << "Modificando elemento elmentos 101 y 103 sin split" << endl;
	bplus.modify(new Element(101, "12xxxxxxxxxx", 12));
	bplus.modify(new Element(102, "12xxxxxxxxxx", 12));
	bplus.exportTree();

	cout << "Modificando elemento elmento 103 generando split" << endl;
	bplus.modify(new Element(103, "9xxxxxxxx", 9));
	bplus.exportTree();
	cout << "Eliminamos el elemento 103" << endl;
	bplus.remove(103);
	bplus.exportTree();
	cout << "Modificamos el elemento 102" << endl;
	bplus.modify(new Element(102, "1", 1));
	bplus.exportTree();
	cout << "eliminamos la clave 104 y se produce un balanceo" << endl;
	bplus.remove(104);
	bplus.exportTree();
	cout << "reinsertamos la clave 104 para ver que si inserta correctamente"
			<< endl;
	bplus.insert(new Element(104, "4xxx", 4));
	bplus.exportTree();
	cout << "eliminamos la clave 100" << endl;
	bplus.remove(100);
	bplus.exportTree();
	cout
			<< "Modificamos el elemento 101 para que quede en overflow y le pida al hermano derecho"
			<< endl;
	bplus.modify(new Element(101, "1", 1));
	bplus.exportTree();
	cout << "eliminamos la clave 101" << endl;
	bplus.remove(101);
	bplus.exportTree();
	cout << "eliminamos la clave 102" << endl;
	bplus.remove(102);
	bplus.exportTree();
	cout << "eliminamos la clave 104" << endl;
	bplus.remove(104);
	bplus.exportTree();

	cout << "end..........." << endl;
*/
}

void BPlusTreeTest::thirdSetTest() {

	/*cout
			<< "probamos los balanceos en los nodos internos e insercciones intermedias"
			<< endl;

	BPlusTree& bplus = *this->bplus;

	cout << "Insertamos 5 elementos de longuitud 4" << endl;
	bplus.insert(new Element(100, "4xxx", 4));
	bplus.insert(new Element(105, "4xxx", 4));
	bplus.insert(new Element(110, "4xxx", 4));
	bplus.insert(new Element(115, "4xxx", 4));
	bplus.insert(new Element(120, "4xxx", 4));
	bplus.exportTree();

	cout << "Insertando el 101 con long 4" << endl;
	bplus.insert(new Element(101, "4xxx", 4));
	bplus.exportTree();
	cout << "Insertando el 103 con long 4" << endl;
	bplus.insert(new Element(103, "4xxx", 4));
	bplus.exportTree();
	cout << "Insertando el 106 con long 4" << endl;
	bplus.insert(new Element(106, "4xxx", 4));
	bplus.exportTree();
	cout << "Insertando el 112 con long 4" << endl;
	bplus.insert(new Element(112, "4xxx", 4));
	bplus.exportTree();
	cout
			<< "Insertando el 107 con long 4 debe splitear la hoja y generar un nodo interno mas"
			<< endl;
	bplus.insert(new Element(107, "4xxx", 4));
	bplus.exportTree();

	cout << "Insertamos elementos a la izquierda" << endl;
	cout << "Insertando el 99 con long 4" << endl;
	bplus.insert(new Element(99, "4xxx", 4));
	bplus.exportTree();
	cout << "Buscando Elemento 100: " << *bplus.findExact(99) << endl;

	cout << "Insertando el 98 con long 4" << endl;
	bplus.insert(new Element(98, "4xxx", 4));
	bplus.exportTree();

	cout << "Insertando el 104 con long 4 debe generar un split hacia arriba"
			<< endl;
	bplus.insert(new Element(104, "4xxx", 4));
	bplus.exportTree();

	cout << "Insertando el 108 " << endl;
	bplus.insert(new Element(108, "4xxx", 4));
	bplus.exportTree();

	cout << "Insertando el 109 " << endl;
	bplus.insert(new Element(109, "4xxx", 4));
	bplus.exportTree();

	cout << "Insertando el 121 " << endl;
	bplus.insert(new Element(121, "4xxx", 4));
	bplus.exportTree();

	cout << "Insertando el 122 " << endl;
	bplus.insert(new Element(122, "4xxx", 4));
	bplus.exportTree();
	cout << "end..........." << endl;

	cout << "Insertando el 123 " << endl;
	bplus.insert(new Element(123, "4xxx", 4));
	bplus.exportTree();
	cout << "end..........." << endl;


	cout << "Insertando el 97 " << endl;
	bplus.insert(new Element(97, "4xxx", 4));
	bplus.exportTree();
	cout << "end..........." << endl;

	cout << "Insertando el 96 " << endl;
	bplus.insert(new Element(96, "4xxx", 4));
	bplus.exportTree();
	cout << "end..........." << endl;


	cout << "Insertando el 95 Esto genera un split de root y un nivel mas de nodos internos" << endl;
	bplus.insert(new Element(95, "4xxx", 4));
	bplus.exportTree();
	cout << "end..........." << endl;


	cout << "Insertando el 124" << endl;
	bplus.insert(new Element(124, "4xxx", 4));
	bplus.exportTree();
	cout << "end..........." << endl;

	cout << "Insertando el 125" << endl;
	bplus.insert(new Element(125, "4xxx", 4));
	bplus.exportTree();
	cout << "end..........." << endl;


	cout << "Insertando el 126" << endl;
	bplus.insert(new Element(126, "4xxx", 4));
	bplus.exportTree();
	cout << "end..........." << endl;

	int i;
	for (i=127;i<141;i++){
		cout << "Insertando el" <<i<<" "<< endl;
		bplus.insert(new Element(i, "4xxx", 4));
		bplus.exportTree();
		cout << "end..........." << endl;
	}

	cout << "Insertando el" <<i<<" Esto debe generar un split"<< endl;
	bplus.insert(new Element(i, "4xxx", 4));
	bplus.exportTree();
	cout << "end..........." << endl;

	cout<<"Insertamos elementos para que desborde el nodo interno"<<endl;


	for (i=142;i<162;i++){
		cout << "Insertando el" <<i<<" "<< endl;
		bplus.insert(new Element(i, "4xxx", 4));
		bplus.exportTree();
		cout << "end..........." << endl;
	}

	cout << "Insertando el" <<i<<" esto genera un split "<< endl;
	bplus.insert(new Element(i, "4xxx", 4));
	bplus.exportTree();
	cout << "end..........." << endl;

	cout<<"********************************"<<endl;
	cout<<"Eliminamos el utimo nodo "<<endl;
	cout<<"********************************"<<endl;
	bplus.remove(160);
	bplus.exportTree();
	bplus.remove(161);
	bplus.exportTree();
	cout<<"********************Elimino el 162 y me genera un revalanceo***********************"<<endl;
	bplus.remove(162);
	bplus.exportTree();
	cout<<"********************Elimino el 159 y me genera un revalanceo***********************"<<endl;
	bplus.remove(159);
	bplus.exportTree();

	cout<<"********************Elimino el 159 y elimina el ultimo nodo***********************"<<endl;
	bplus.remove(158);
	bplus.exportTree();

	cout<<"********************************"<<endl;
	cout<<"Eliminamos el otro nodo "<<endl;
	cout<<"********************************"<<endl;

	for (i=154;i<157;i++){
		cout<<"Eliminando "<< i<<endl;
		bplus.remove(i);
		bplus.exportTree();
	}

	cout<<"********************Elimino el 158 y genera un contraccion del nodo***********************"<<endl;
	bplus.remove(157);
	bplus.exportTree();

	cout<<"********************************"<<endl;
	cout<<"Eliminamos el otro nodo "<<endl;
	cout<<"********************************"<<endl;

	for (i=150;i<153;i++){
		cout<<"Eliminando "<< i<<endl;
		bplus.remove(i);
		bplus.exportTree();
	}

	cout<<"********************Elimino el 153 y genera un contraccion del nodo***********************"<<endl;
	bplus.remove(153);
	bplus.exportTree();

	//modificamos un nodo
	bplus.modify(new Element(141,"5xxxx",5));
	bplus.exportTree();

	cout<<"********************************"<<endl;
	cout<<"Eliminamos el otro nodo "<<endl;
	cout<<"********************************"<<endl;

	for (i=147;i<149;i++){
		cout<<"Eliminando "<< i<<endl;
		bplus.remove(i);
		bplus.exportTree();
	}


	cout<<"********************Elimino el 149 y genera un contraccion del nodo***********************"<<endl;
	bplus.remove(149);
	bplus.exportTree();

	cout<<"eliminamos el registro 101"<<endl;

	bplus.remove(101);
	bplus.exportTree();


	cout<<"********************************"<<endl;
	cout<<"Eliminamos el otro nodo "<<endl;
	cout<<"********************************"<<endl;

	for (i=120;i<135;i++){
		cout<<"Eliminando "<< i<<endl;
		bplus.remove(i);
		bplus.exportTree();
	}
	cout<<"Eliminando "<< i<<endl;
	bplus.remove(i);


	cout<<"Eliminando "<< 140<<endl;
	bplus.remove(140);
	bplus.exportTree();

	for (i=144;i<146;i++){
		cout<<"Eliminando "<< i<<endl;
		bplus.remove(i);
		bplus.exportTree();
	}

	cout<<"********************Elimino el 146 y genera un contraccion del nodo***********************"<<endl;
	bplus.remove(146);
	bplus.exportTree();

	cout<<"********************************"<<endl;
	cout<<"Eliminamos el otro nodo "<<endl;
	cout<<"********************************"<<endl;

	for (i=141;i<143;i++){
			cout<<"Eliminando "<< i<<endl;
			bplus.remove(i);
			bplus.exportTree();
		}

	cout<<"********************Elimino el 143 y genera un contraccion del nodo***********************"<<endl;
	bplus.remove(143);
	bplus.exportTree();

	cout<<"********************************"<<endl;
	cout<<"Eliminamos mas nodos para poder realizar una contraccion de un nodo hoja "<<endl;
	cout<<"********************************"<<endl;
	for (i=137;i<139;i++){
		cout<<"Eliminando "<< i<<endl;
		bplus.remove(i);
		bplus.exportTree();
	}
	cout<<"Eliminando "<< i<<endl;
	bplus.remove(i);
	bplus.exportTree();
*/
}


BPlusTreeTest::~BPlusTreeTest() {
}
