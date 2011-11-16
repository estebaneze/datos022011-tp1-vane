
#ifndef MAINTREE_H_
#define MAINTREE_H_
#include "BPlusTree.h"
#include "Element.h"
#include "BNode.h"
#include "../utils/ConfigurationMananger.h"
#include "../utils/utiles.h"
#include <string>
#include <iostream>
#include <strings.h>

class MainTree {
private:
	enum Task {BUSCAR, INGRESAR, MODIFICAR, QUITAR, VOLCAR, AYUDA, ELIMINAR, INDEFINIDO};
	struct inParam{
		KeyInt key;
		Data value;
		DataSize size;
	};

	inParam parseParam (string param){

		inParam result;
		result.key=0;
		result.value = NULL;
		result.size = 0;

		string temp="";

		//Saca el parentesis
		param = param.substr(1,param.size()-2);
		int p = param.find(";",0);
		if (p > 0) { //Tengo el ;
			KeyInt key;
			char* buffer;

			temp = param.substr(0,p);
			key = Util::toInt(temp);

			temp = param.substr(p+1);
			if (temp.size() > 0) {
				buffer = new char[temp.size()];
				temp.copy(buffer,temp.size());
			}
			result.key = key;
			result.size = temp.size();
			result.value = (Data)buffer;

		}
		return result;
	}

public:
	MainTree();
	int run(int argc,char** argv);
	virtual ~MainTree();
};

#endif /* MAINTREE_H_ */
