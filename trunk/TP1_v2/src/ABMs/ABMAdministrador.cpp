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
ABMAdministrador::ABMAdministrador(string file) {

	this->File= File;
	this->directorio = new Directory(file,2048);

	//Descomentar esto si quiere verse el contenido del archivo por pantalla
	//this->directorio->inform();

	// OJO! el tamaño lo tioene que leer desde un archivo de configuracion


}

/**Agrega un nuevo admin, si ya existe no hace nada
 *
 */
void ABMAdministrador::Add(Administrador admin){

	if (!(this->directorio->existKey(admin.GetUsuario()))){
		this->directorio->insert(admin.GetUsuario(),admin.GetClave());
	}
}

/**Elimina una Admin, si no exite arroja un excepcion, informa true si elimino sino false*/
bool ABMAdministrador::Delete(Administrador admin){

	if (this->directorio->existKey(admin.GetUsuario())){
		return (this->directorio->remove(admin.GetUsuario()));
	}
	else{
		return false;
	}
}

/**Modifica el password de un admin pasada por parametro
* si lo encuentra la modifica sino no hace nada
*/
void ABMAdministrador::ModifyPassword(Administrador admin){

	if (this->directorio->existKey(admin.GetUsuario())){
		this->directorio->modify(admin.GetUsuario(),admin.GetClave());
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

	if (!(this->directorio->existKey(nombre))){

		return new Administrador(nombre,directorio->find(nombre));
	}
	else return NULL;
}

bool ABMAdministrador::existKey(Administrador admin){
	return this->directorio->existKey(admin.GetUsuario());
}

void ABMAdministrador::mostrarAdminsPorPantalla(){
	this->directorio->inform();
}

ABMAdministrador::~ABMAdministrador() {
	// TODO Auto-generated destructor stub
}
