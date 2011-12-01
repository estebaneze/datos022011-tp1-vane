/*
 * ABMAdministrador.cpp
 *
 *  Created on: 15/10/2011
 *      Author: gabriel
 */

#include "ABMAdministrador.h"

/*
 * creo el directorio y le paso el nombre del archivo a generar y tamaño de los buckets
 */
ABMAdministrador::ABMAdministrador() {
	int maxBucketSize = ConfigurationMananger::getInstance()->getHashBSizeAdministrador();
	this->File= ConfigurationMananger::getInstance()->getAdminFile();
	this->directorio = new DirectoryRSA(ConfigurationMananger::getInstance()->getAdminFile(), maxBucketSize);
}

/**Agrega un nuevo admin, si ya existe no hace nada
 *
 */
void ABMAdministrador::Add(Administrador* admin){

	if (!(this->directorio->existKey(admin->GetUsuario()))){
		this->directorio->insert(admin->GetUsuario(),admin->GetClave());

		HashLog::LogProcess(this->directorio,ConfigurationMananger::getInstance()->getLogProcessAdminFile());
		HashLog::LogInsert(admin->GetUsuario(),admin->GetClave(),ConfigurationMananger::getInstance()->getLogOperAdminFile());
	}
}

/**Elimina una Admin, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMAdministrador::Delete(Administrador* admin){

	if (this->directorio->existKey(admin->GetUsuario())){
		this->directorio->remove(admin->GetUsuario());
		HashLog::LogProcess(this->directorio,"Admin_HashProccess.log");
		HashLog::LogDelete(admin->GetUsuario(),admin->GetClave(),"Admin_HashOperation.log");
		return true;
	}
	else{
		return false;
	}
}

/**Modifica el password de un admin pasada por parametro
* si lo encuentra la modifica sino no hace nada
*/
void ABMAdministrador::ModifyPassword(Administrador* admin){

	if (this->directorio->existKey(admin->GetUsuario())){
		this->directorio->modify(admin->GetUsuario(),admin->GetClave());
		HashLog::LogProcess(this->directorio,"Admin_HashProccess.log");
		HashLog::LogModify(admin->GetUsuario(),admin->GetClave(),"Admin_HashOperation.log");
	}

}
/*
 * Devuelve un vector con nombre de los Administradores y sus password
 * NO DEVUELVE OBJETO ADMINISTRADOR SINO SUS ELEMENTOS
 */
vector<Administrador> ABMAdministrador::GetAdmins(){

	vector<KeyValue> values = this->directorio->getAllValues();
	vector<Administrador> admins;

			for(unsigned int i = 0; i < values.size(); i++){

				admins.push_back(Administrador(values[i].Key,values[i].Value));

			}
	//Descomentar para ver por pantalla
		/*cout << "----------------ABMAdministrador::GetAdmins-----------------------" << endl;
		for(unsigned int i = 0; i < values.size(); i++){


			cout << values[i].Key << ": " << values[i].Value << endl;
		}
		cout << "----------------ABMAdministrador::GetAdmins-----------------------" << endl;*/
		return admins;
}

/*
 * Devuelve administrador si no existe el nombre NULL
 */
Administrador* ABMAdministrador::GetAdmin(std::string nombre){

	if ((this->directorio->existKey(nombre))){

		return new Administrador(nombre,directorio->find(nombre));
	}
	else return NULL;
}

bool ABMAdministrador::existKey(string admin){
	return this->directorio->existKey(admin);
}

void ABMAdministrador::mostrarAdminsPorPantalla(){
	this->directorio->inform();
}

ABMAdministrador::~ABMAdministrador() {
	// TODO Auto-generated destructor stub
	delete(this->directorio);
}
