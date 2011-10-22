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

	//Ordeno por cantidad de votos
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
			j++;
		}

	}

	//Ordeno los registro que ya estan agrupados por cantidad de votos
	vector< vector<Conteo> >::iterator it2 = resAgrupados.begin();
	vector<Conteo> cs  = (vector<Conteo>) *it2;
	for (it2 = resAgrupados.begin(); it2 != resAgrupados.end(); it++) {
		cs = *it2;
		cs = Reportes::OrderByCantidadVotos(cs);
	}

	cout << endl << endl << endl;

	for(int i = 0; i < resAgrupados.size(); i++){

		Eleccion* e = abmEleccion->GetEleccion(conteo.GetIdDistrito());
		string cargo = abmCargo->GetCargo(e->GetIdCargo())->GetNombre();
		Fecha fecha = e->GetDate().getStrFecha();

		vector<Conteo> cs = resAgrupados[i];

		cout << "Eleccion: (" << fecha.getStrFecha() << " - " << cargo << ")" << endl;

		for(int j = 0; j < cs.size(); j++){
			Conteo res = cs[j];
			string distrito = abmDistrito->GetDistrito(res.GetIdDistrito())->GetNombre();
			cout << "		Distrito: " << distrito << " tiene " << res.GetCountVotos() << " votos." << endl;
		}
	}

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
			j++;
		}

	}

	//Ordeno los registro que ya estan agrupados por cantidad de votos
	vector< vector<Conteo> >::iterator it2 = resAgrupados.begin();
	vector<Conteo> cs  = (vector<Conteo>) *it2;
	for (it2 = resAgrupados.begin(); it2 != resAgrupados.end(); it++) {
		cs = *it2;
		cs = Reportes::OrderByCantidadVotos(cs);
	}

	cout << endl << endl << endl;

	for(int i = 0; i < resAgrupados.size(); i++){

		Eleccion* e = abmEleccion->GetEleccion(conteo.GetIdDistrito());
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

/* Ordena el vector de Conteos por cantidad de votos.
 * TODO: ESTA ORDENANDO DE MENOR A MAYOR. TIENE QUE SER AL REVES.
 * */
vector<Conteo> Reportes::OrderByCantidadVotos(vector<Conteo> resultados){

	Conteo aux;

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

	Conteo aux;;
	ABMEleccion abmElecciones = ABMEleccion();

	for (int i=0; i <= resultados.size()-1; i++) {

		for (int j = i+1 ;j < resultados.size();j++)	{

			int idE1 = resultados[i].GetIdEleccion();
			int idE2 = resultados[j].GetIdEleccion();

			Fecha f1 = abmElecciones.GetEleccion(idE1)->GetDate();
			Fecha f2 = abmElecciones.GetEleccion(idE2)->GetDate();

			//if (resultados[i].GetEleccion()->GetDate() > resultados[j].GetEleccion()->GetDate()) {
			if(f1 < f2){
				aux = resultados[i];
				resultados[i] = resultados[j];
				resultados[j] = aux;
			}
		}
	}

	return resultados;
}
