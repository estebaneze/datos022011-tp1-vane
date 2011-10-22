#include "MainTree.h"

MainTree::MainTree() {

}

int MainTree::run(int argc,char** argv){
	Task task = INDEFINIDO;

	if ((argc == 2)	&& strcasecmp(argv[1], "-h") == 0)
		task = AYUDA;
	else if (argc == 3){
		if ( strcasecmp(argv[2], "-s") == 0 )	task = VOLCAR;
		if ( strcasecmp(argv[2], "-b") == 0 )	task = BUSCAR;
		if ( strcasecmp(argv[2], "-i") == 0 )	task = INGRESAR;
		if ( strcasecmp(argv[2], "-m") == 0 )	task = MODIFICAR;
		if ( strcasecmp(argv[2], "-q") == 0 )	task = QUITAR;
		if ( strcasecmp(argv[2], "-e") == 0 )	task = ELIMINAR;
	}

	//---------------------------------------------------------------------
	if (task == INDEFINIDO)
	{
		cout << "Error, no especificó ningún comando. Pruebe con -h " << strcasecmp(argv[1], "-h") << endl;
		return -1;
	}

	//---------------------------------------------------------------------
	if (task == AYUDA)
	{
		cout <<" <arch> -B 	buscar" << endl;
		cout <<" <arch> -I 	ingresar" << endl;
		cout <<" <arch> -M 	modificar" << endl;
		cout <<" <arch> -Q 	quitar" << endl;
		cout <<" <arch> -S 	volcar" << endl;
		cout <<" <arch> -E  eliminar arbol" << endl;
		cout <<" -H 		ayuda" << endl;
		return 0;
	}

	//---------------------------------------------------------------------
	ConfigurationMananger* c = ConfigurationMananger::getInstance();
	//Abro el BPlusTree
	BPlusTree* bpt = NULL;
	try{
		bpt = new BPlusTree(c->getBufferSize(),argv[1]);
	}catch(...){
		cout << "No fue posible iniciar el progama por problema en los archivos de dato." << endl;
		cout << "Por favor, revise los archivos "<< argv[1] << " , antes de volver a correr el comando." << endl;
		return 1;
	}

	bool quit = false;

	Element* el = NULL;
	BNode* node = NULL;
	//---------------------------------------------------------------------

	//Ciclo mientras tenga datos en la entrada estandar
	string linea="";

	switch(task) {
		case ELIMINAR:
			try{
				bpt->deleteTree();
				quit = true;
			}catch(...){
				cout<< "No se pudo eliminar el arbol." << endl;
			}
			break;
		case VOLCAR:
			bpt->exportTree();
			quit = true;
			break;
	}

	while(!cin.eof() && !quit)
	{
		//Obtengo una linea. Formato: (clave;[posicion])
		getline(cin, linea);

		if(!linea.compare("quit"))
			return 0;
		//Obtengo un par (clave; posicion)

		if (linea.empty()) continue;

		inParam param = parseParam(linea);
		//Obtengo un par (clave; posicion)

		//Segun la tarea, tengo que hacer algo
		switch (task) {
			case BUSCAR:
				if (node != NULL) delete node;
				try{
					LeafNode* fnode = bpt->find(param.key);
					cout << "Se encontro (" << *fnode << ")" << endl;
				}catch(...){
					cout << "No encontré el registro con clave " << param.key << endl;
				}

				break;

			case INGRESAR:
				//if (el != NULL) delete el;
				el = new Element(param.key,param.value,param.size);
				try{
					bpt->insert(el);
					cout << linea << " agregado correctamente" << endl;
				}catch(...){
					cout << "No se pudo agregar el registro " << linea << endl;
				}

				break;

			case MODIFICAR:
				el = new Element(param.key,param.value, param.size);
				try{
					bpt->modify(el);
					cout  << linea << " Registro modificado correctamente" << endl;
				}
				catch(...){
					cout << "No se pudo modificar el registro " << linea << endl;
				}

				break;

			case QUITAR:
				try{
					bpt->remove(param.key);
					cout << "Registro con clave " << param.key << " ha sido eliminado"<< endl;
				}catch(...){
					cout << "No se pudo eliminar el registro con clave " << param.key << endl;
				}
				break;
			default:
				break;
		}
	}

	//delete bpt;
	//delete el;
	//delete node;
	return 0;
}
MainTree::~MainTree() {
}
