/*
 * Reportes.cpp
 *
 *  Created on: 18/10/2011
 *      Author: ricardo
 */

#include "Reportes.h"

/*TODO: mostrar la cantidad de votos en porcentaje
 */

void Reportes::reportePorEleccion(int idEleccion)
{
	ABMConteo *abmConteo = new ABMConteo();

	vector<Conteo> resultados =  abmConteo->GetConteoByEleccion(idEleccion);

	if(resultados.size() == 0) {
		cout << "No se encontraron resultados." << endl;
		return;
	}

	//Ordeno por cantidad de votos
	resultados = Reportes::GroupByLista(resultados);
	resultados = Reportes::OrderByCantidadVotos(resultados);

	for(int i = 0; i < resultados.size(); i++){
		cout << "Lista: " << resultados[i].GetIdLista() << ". Votos:  " << resultados[i].GetCountVotos() << endl;
	}

	delete abmConteo;
}

void Reportes::reportePorLista(string lista)
{
	ABMConteo *abmConteo = new ABMConteo();
	ABMEleccion* abmEleccion = new ABMEleccion();
	ABMCargo* abmCargo = new ABMCargo();
	ABMDistrito* abmDistrito = new ABMDistrito();


	vector<Conteo> resultados =  abmConteo->GetConteoByLista(lista);

	if(resultados.size() == 0){
		cout << "No se encontraron resultados." << endl;
		return;
	}

	//Primero ordeno por fecha de eleccion
	vector<Conteo> aux = resultados;

	resultados = Reportes::OrderByFecha(aux);
	vector<Conteo>::iterator it = resultados.begin();

	Conteo conteo = (Conteo) *it;

	//Agrupo por fecha de eleccion
	vector< vector<Conteo> > resAgrupados;
	vector<Conteo> c1;
	resAgrupados.push_back(c1);
	int j = 0;
	int idEleccionActual = conteo.GetIdEleccion();



	//Tengo que agrupar por eleccion
	for (it = resultados.begin(); it != resultados.end(); it++) {

		conteo = (Conteo) *it;

		int idEleccionAux = conteo.GetIdEleccion();

		if(idEleccionAux == idEleccionActual){
			resAgrupados[j].push_back(conteo);
		}
		else{	//Nuevo grupo de eleccion
			vector<Conteo> cs;
			cs.push_back(conteo);
			resAgrupados.push_back(cs);
			idEleccionActual = idEleccionAux;
			j++;
		}

	}


	//Ordeno los registro que ya estan agrupados por cantidad de votos
	/*vector< vector<Conteo> >::iterator it2 = resAgrupados.begin();
	vector<Conteo> cs  = (vector<Conteo>) *it2;
	for (it2 = resAgrupados.begin(); it2 != resAgrupados.end(); it++) {
		vector<Conteo> aux = *it2;

		cs = Reportes::OrderByCantidadVotos(aux);
	}*/


	for(int i = 0; i < resAgrupados.size(); i++){

		vector<Conteo> aux = Reportes::OrderByCantidadVotos(resAgrupados[i]);
		resAgrupados[i] = aux;
	}


	cout << endl << endl << endl;

	for(int i = 0; i < resAgrupados.size(); i++){

		Eleccion* e = abmEleccion->GetEleccion(conteo.GetIdEleccion());


		//string cargo = abmCargo->GetCargo(e->GetIdCargo())->GetNombre();

		vector <Cargo> v = abmCargo->GetCargos();
		string cargo;


		for (int i=0; i<v.size();i++ ){
			if (v.at(i).GetId()==e->GetIdCargo()){
				cargo= v.at(i).GetNombre();
			}
		}

		Fecha fecha = e->GetDate().getStrFecha();

		vector<Conteo> cs = resAgrupados[i];


		cout << "Eleccion: (" << fecha.getStrFecha() << " - " << cargo << ")" << endl;


		for(int j = 0; j < cs.size(); j++){

			Conteo res = cs[j];
			Distrito* d = abmDistrito->GetDistrito(res.GetIdDistrito());

			if(d != NULL){
				string distrito = d->GetNombre();
				cout << "		Distrito: " << distrito << " tiene " << res.GetCountVotos() << " votos." << endl;
			}
		}

		//cout << "aca2" << endl;
		//cout  << endl << "--i: " << i << " eleccion " << e->GetId() << " -  id cargo " << e->GetIdCargo() << endl;
	}

//	cout << "aca3" << endl;
	delete abmConteo;
	delete abmEleccion;
	delete abmCargo;
	delete abmDistrito;
}

void Reportes::reportePorDistrito(int idDistrito)
{
	ABMConteo *abmConteo = new ABMConteo();
	ABMEleccion* abmEleccion = new ABMEleccion();
	ABMCargo* abmCargo = new ABMCargo();
	ABMDistrito* abmDistrito = new ABMDistrito();

	vector<Conteo> resultados =  abmConteo->GetConteoByDistrito(idDistrito);

	if(resultados.size() == 0){
		cout << "No se encontraron resultados." << endl;
		return;
	}

	//Primero ordeno por fecha de eleccion
	resultados = Reportes::OrderByFecha(resultados);

	vector<Conteo>::iterator it = resultados.begin();

	Conteo conteo = (Conteo) *it;

	//Agrupo por fecha de eleccion
	vector< vector<Conteo> > resAgrupados;
	vector<Conteo> c1;
	resAgrupados.push_back(c1);
	int j = 0;
	int idEleccionActual = conteo.GetIdEleccion();

	//Tengo que agrupar por eleccion

	for (it = resultados.begin(); it != resultados.end(); it++) {

		conteo = (Conteo) *it;

		int idEleccionAux = conteo.GetIdEleccion();

		if(idEleccionAux == idEleccionActual){
			resAgrupados[j].push_back(conteo);
		}
		else{	//Nuevo grupo de eleccion
			vector<Conteo> cs;
			cs.push_back(conteo);
			resAgrupados.push_back(cs);
			idEleccionActual = idEleccionAux;
			j++;
		}

	}

	//Ordeno los registro que ya estan agrupados por cantidad de votos

	/*vector< vector<Conteo> >::iterator it2 = resAgrupados.begin();
	vector<Conteo> cs  = (vector<Conteo>) *it2;
	cout << "resAgrupados.size() " << resAgrupados.size() << endl;

	for (it2 = resAgrupados.begin(); it2 != resAgrupados.end(); it++) {
		cs = *it2;
		cs = Reportes::OrderByCantidadVotos(cs);
	}
	*/

	for(int i = 0; i < resAgrupados.size(); i++){

		vector<Conteo> aux = Reportes::OrderByCantidadVotos(resAgrupados[i]);
		resAgrupados[i] = aux;
	}

	cout << endl << endl << endl;

	for(int i = 0; i < resAgrupados.size(); i++){

		Eleccion* e = abmEleccion->GetEleccion(conteo.GetIdEleccion());
		string cargo = abmCargo->GetCargo(e->GetIdCargo())->GetNombre();
		Fecha fecha = e->GetDate().getStrFecha();

		vector<Conteo> cs = resAgrupados[i];

		cout << "Eleccion: (" << fecha.getStrFecha() << " - " << cargo << ")" << endl;

		for(int j = 0; j < cs.size(); j++){
			Conteo res = cs[j];
			cout << "		Lista: " << res.GetIdLista() << " tiene " << res.GetCountVotos() << " votos." << endl;
		}
	}

	delete abmConteo;
	delete abmEleccion;
	delete abmCargo;
	delete abmDistrito;

}

vector<Conteo> Reportes::GroupByLista(vector<Conteo> resultados){

	Conteo aux;
	vector<Conteo> vectorReturn;

	if (resultados.size() <= 1)
		return resultados;

	//1ro ordeno x Lista
	for (int i=0; i <= resultados.size()-1; i++) {

		for (int j = i+1 ;j < resultados.size();j++)	{

			if (resultados[i].GetIdLista().compare(resultados[j].GetIdLista()) > 0) {
				aux = resultados[i];
				resultados[i] = resultados[j];
				resultados[j] = aux;
			}
		}
	}

	//2do sumo cntidad votos x lista y creo conteo dummy (iddependencia 0 y idconteo 0)
	int cantVotos = 0;
	string idListaActual = resultados[0].GetIdLista();
	int idEleccion = resultados[0].GetIdEleccion();
	for (int i=0; i < resultados.size(); i++) {

		if (resultados[i].GetIdLista().compare(idListaActual) == 0)
		{
			cantVotos += resultados[i].GetCountVotos();
		}
		else
		{
			vectorReturn.push_back(Conteo(idListaActual, 0, idEleccion, 0, cantVotos));
			cantVotos =  resultados[i].GetCountVotos();
			idListaActual = resultados[i].GetIdLista();
		}
	}
	vectorReturn.push_back(Conteo(idListaActual, 0, idEleccion, 0, cantVotos));

	for (int i=0; i < vectorReturn.size(); i++) {
		cout << vectorReturn[i].GetCountVotos() << endl;
	}


	return vectorReturn;
}

/* Ordena el vector de Conteos por cantidad de votos.
 * TODO: ESTA ORDENANDO DE MENOR A MAYOR. TIENE QUE SER AL REVES.
 * */
vector<Conteo> Reportes::OrderByCantidadVotos(vector<Conteo> resultados){

	Conteo aux;

	if (resultados.size() <= 1)
		return resultados;


	for (int i=0; i <= resultados.size()-1; i++) {

		for (int j = i+1 ;j < resultados.size();j++)	{

			if (resultados[i].GetCountVotos() < resultados[j].GetCountVotos()) {
				aux = resultados[i];
				resultados[i] = resultados[j];
				resultados[j] = aux;
			}
		}
	}

	return resultados;
}

/* Los ordena por fecha de eleccion */
vector<Conteo> Reportes::OrderByFecha(vector<Conteo> resultados){

	if (resultados.size() <= 1)
		return resultados;

	Conteo aux;;
	ABMEleccion abmElecciones = ABMEleccion();

	for (int i=0; i < resultados.size(); i++) {

		for (int j = i+1 ;j < resultados.size();j++)	{


			int idE1 = resultados[i].GetIdEleccion();
			int idE2 = resultados[j].GetIdEleccion();

			Eleccion* e1 = abmElecciones.GetEleccion(idE1);
			Eleccion* e2 = abmElecciones.GetEleccion(idE2);

			if(e1 != NULL && e2 != NULL){

				Fecha f1 = e1->GetDate();
				Fecha f2 = e2->GetDate();

				//if (resultados[i].GetEleccion()->GetDate() > resultados[j].GetEleccion()->GetDate()) {
				if(f1 < f2){
					aux = resultados[i];
					resultados[i] = resultados[j];
					resultados[j] = aux;
				}
			}
		}
	}

	return resultados;
}
