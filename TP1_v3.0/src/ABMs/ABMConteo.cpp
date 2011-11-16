/*
 * ABMConteo.cpp
 *
 *  Created on: 12/10/2011
 *      Author: gabriel
 */
#include "ABMConteo.h"

ABMConteo::ABMConteo() {

	string mainTreeName = ConfigurationMananger::getInstance()->getConteoFile();
    int bufferSize = ConfigurationMananger::getInstance()->getBufferSizeTree();

    this->bplusTree = new BPlusTree(bufferSize,Helper::concatenar(mainTreeName,"bpt","."));

    this->indexByDistrito = new Index(Helper::concatenar(mainTreeName,"Distrito",ConfigurationMananger::getInstance()->getSeparador2()));
    this->indexByLista = new Index(Helper::concatenar(mainTreeName,"Lista",ConfigurationMananger::getInstance()->getSeparador2()));
    this->indexByEleccion = new Index(Helper::concatenar(mainTreeName,"Eleccion",ConfigurationMananger::getInstance()->getSeparador2()));

}

/**Agrega una nueva lista, si ya existe el nombre de la lista arroja una excepcion
 *Para evitar excdepcion debo antes usar metodo Directory::existKey
 */
int ABMConteo::Inicializa(string idLista, int idDistrito, int idEleccion){

	//Key key = Helper::IntToString(idConteo);

	string idListaAux =idLista;
	string str = idListaAux.append("|");
	str.append(Helper::IntToString(idDistrito)).append("|");
	str.append(Helper::IntToString(idEleccion).append("|"));
	str.append("0|");	//0 votos

	//idLista|idDistrito|idEleccion|votos|
	Data data = (Data)str.c_str();
	int longData = str.length();

	int idConteo = Identities::GetNextIdConteo();
	KeyInt key = idConteo;
	Element * element = new Element(key, data, longData);

	this->bplusTree->insert(element);

	//Actualizo los indices
	this->indexByDistrito->AppendToIndex(Helper::IntToString(idDistrito), Helper::IntToString(idConteo));
	this->indexByLista->AppendToIndex(idLista, Helper::IntToString(idConteo));

	//Esta es la clave de la eleccion dentro de conteo
	this->indexByEleccion->AppendToIndex(idEleccion, Helper::IntToString(idConteo));

	BPlusTreeLog::LogInsert(key, data,ConfigurationMananger::getInstance()->getLogOperConteoFile());
	BPlusTreeLog::LogProcess(this->bplusTree, ConfigurationMananger::getInstance()->getLogProcessConteoFile());

	return idConteo;
}

/* Le suma un voto al registro y devuelve la cantidad de votos totales */
void ABMConteo::AddVoto(int idConteo, Votante* votante){

	if(ExistsKey(idConteo)){

		Conteo* c = this->GetConteo(idConteo);
		int idEleccion = c->GetIdEleccion();

		if(votante->VotoEnEleccion(idEleccion)){
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			cout << "El votante " << votante->GetNombreYApellido() << " ya voto en la eleccion " << c->GetIdEleccion() << endl;
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			return;
		}

		c->AddVoto();

		//Key key = Helper::IntToString(idConteo);
		KeyInt key = idConteo;
		string str = c->GetIdLista();                                                                           //agrego lista
		str.append("|").append(Helper::IntToString(c->GetIdDistrito()));        //agrego id Distrot

		//Esta es la clave de la eleccion dentro de conteo
		str.append("|").append(Helper::IntToString(c->GetIdEleccion()));        //agrego id eleccion

		str.append("|").append(Helper::IntToString(c->GetCountVotos()));        //agrego cantidad de votos

		str.append("|");	//Pongo el pipe al final, para que quede idLista|idDistrito|idEleccion|cantVotos|

		Data data = (Data)str.c_str();
		int longData = str.length();

		Element * element=new Element(key, data, longData);
		this->bplusTree->modify(element);

		BPlusTreeLog::LogModify(key, data, ConfigurationMananger::getInstance()->getLogOperConteoFile());
		BPlusTreeLog::LogProcess(this->bplusTree, ConfigurationMananger::getInstance()->getLogProcessConteoFile());

		this->NotifyVotante(votante, idEleccion);

		cout <<endl<<endl<<endl <<  "El Votante " << votante->GetNombreYApellido() << " voto por la Lista " << c->GetIdLista() << ". La lista tiene un total del votos de: " << c->GetCountVotos() << endl;

	}
	else{
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\n\n\Error: no se encontro el registro de conteo para realizar la votacion " << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}

}

/* Le avisa al Votante que ya voto en esta eleccion */
void ABMConteo::NotifyVotante(Votante* votante, int idEleccion){

        //Hay que guardar en la entidad Votante el ide de eleccion, para que quede el registro de que ya voto en esta eleccion y no puede volver a votar
        ABMVotante abmVotantes = ABMVotante();
        votante->AgregarEleccion(idEleccion);

        /*//(long dni, string nombreYApellido, string clave, string domicilio, int idDistrito);
        Votante *v = new Votante(votante->GetDni(), votante->GetNombreYApellido(), votante->GetClave(), votante->GetDomicilio(), votante->GetDistrito());
        v->SetEleccionesVotadas(votante->GetEleccionesVotadas());
*/
        abmVotantes.Modify(votante);
}

Conteo* ABMConteo::GetConteo(int idConteo){

	if(ExistsKey(idConteo)){

			Element* elemento = this->bplusTree->findExact(idConteo);
			vector<string> splited = Helper::split(elemento->getData(), '|');
			int cantVotos = 0;

			if(splited.size() > 3){        //si ya tiene registrado algun voto
				if(splited[3].size() > 0)
					cantVotos = Helper::StringToInt(splited[3]);
			}

			return new Conteo(splited[0], Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), idConteo, cantVotos);
	}

	return NULL;
}

vector<Conteo> ABMConteo::GetConteoByDistrito(int idDistrito){

	vector<Conteo> conteos;
	vector<Key> ids = this->indexByDistrito->GetIds(Helper::IntToString(idDistrito));

	for(int i = 0; i < ids.size(); i++){

		int kint = Helper::StringToInt(ids[i]);
		Element* elemento = this->bplusTree->findExact(kint);

		string data = elemento->getData();

		vector<string> splited = Helper::split(data, '|');
		int cantVotos = 0;	//vane

		if(splited.size() > 3){        //si ya tiene registrado algun voto
			if(splited[3].size() > 0)
				cantVotos = Helper::StringToInt(splited[3]);
		}

		conteos.push_back(Conteo(splited[0], Helper::StringToInt(splited[1]), Helper::StringToInt(splited[2]), kint, cantVotos));
	}

	return conteos;
}

vector<Conteo> ABMConteo::GetConteoByEleccion(int idEleccion){

        vector<Conteo> conteos;

        vector<Key> ids = this->indexByEleccion->GetIds(Helper::IntToString(idEleccion));

        for(int i = 0; i < ids.size(); i++){

                int kint = Helper::StringToInt(ids[i]);

                if(ExistsKey(kint)){
					Element* elemento = this->bplusTree->findExact(kint);
					vector<string> splited = Helper::split(elemento->getData(), '|');
					int cantVotos = 0;

					if(splited.size() > 3){        //si ya tiene registrado algun voto
	    				if(splited[3].size() > 0)
	    					cantVotos = Helper::StringToInt(splited[3]);
	    			}

					conteos.push_back(Conteo(splited[0], Helper::StringToInt(splited[1]), idEleccion, kint, cantVotos));

                }
        }

        return conteos;
}

vector<Conteo> ABMConteo::GetConteoByLista(string idLista){

        vector<Conteo> conteos;

        vector<Key> ids = this->indexByLista->GetIds(idLista);
        int size = ids.size();

        ABMEleccion abm = ABMEleccion();

        for(unsigned int i = 0; i < ids.size(); i++){

        	int kint = Helper::StringToInt(ids[i]);

			Element* elemento = this->bplusTree->findExact(Helper::StringToInt(ids[i]));

			string data = elemento->getData();
			vector<string> splited = Helper::split(elemento->getData(), '|');

			int cantVotos = 0;

			if(splited.size() > 3){        //si ya tiene registrado algun voto
				if(splited[3].size() > 0)
					cantVotos = Helper::StringToInt(splited[3]);
			}

			//ABMEleccion abm = ABMEleccion();
			Eleccion* e = abm.GetEleccion(Helper::StringToInt(splited[2]));


			if (Helper::StringToInt(splited[1])!=0)
			conteos.push_back(Conteo(splited[0],Helper::StringToInt(splited[1]),e->GetId(), kint, cantVotos));

        }

        return conteos;
}

void ABMConteo::mostrarConteoPorPantalla(){
        this->bplusTree->exportTree();
}

vector<Conteo> ABMConteo::GetConteoByDistritoYFecha(int idDistrito, Fecha fecha){

        vector<Conteo> conteos;

        //Conteo (((lista)ie, (distrito)ie, (eleccion)ie)i, cantidad): Arbol B+
        vector<Conteo> conteosByDistrito = this->GetConteoByDistrito(idDistrito);

        //Me traigo las elecciones de la fecha
        ABMEleccion abmElecciones = ABMEleccion();
        Fecha* f = new Fecha(fecha.getDia(), fecha.getMes(), fecha.getAnio());
        vector<Eleccion*> eleccionesByFechaYDistrito = abmElecciones.GetByFechaYDistrito(f, idDistrito);

        for(int i = 0; i < eleccionesByFechaYDistrito.size(); i++){

                int idEleccion = eleccionesByFechaYDistrito[i]->GetId();

                //Me quedo con los distritos que pertenecen a las eleccioines que busque antes
                for(int j = 0; j < conteosByDistrito.size(); j++){

					Conteo c = conteosByDistrito[i];
					if(c.GetIdEleccion() == idEleccion){
							conteos.push_back(c);
					}

                }
        }

        return conteos;
}

bool ABMConteo::ExistsKey(KeyInt key){

        if(this->bplusTree->findExact(key) == NULL)
                return false;
        else
                return true;
}

ABMConteo::~ABMConteo() {
        delete this->bplusTree;

        delete this->indexByDistrito;
        delete this->indexByEleccion;
        delete this->indexByLista;
}


