/*
 * Reportes.cpp
 *
 *  Created on: 18/10/2011
 *      Author: ricardo
 */

#include "Reportes.h"

/*TODO: mostrar la cantidad de votos en porcentaje
 */

void Reportes::reportePorEleccion(int idEleccion, bool guardaEncriptado)
{
	ABMConteo *abmConteo = new ABMConteo();
	std::stringstream out;

	vector<Conteo> resultados =  abmConteo->GetConteoByEleccion(idEleccion);

	if(resultados.size() == 0) {
		out << "No se encontraron resultados." << endl;
		return;
	}

	//Ordeno por cantidad de votos
	resultados = Reportes::GroupByLista(resultados);
	resultados = Reportes::OrderByCantidadVotos(resultados);

	for(int i = 0; i < resultados.size(); i++){
		out << "Lista: " << resultados[i].GetIdLista() << ". Votos:  " << resultados[i].GetCountVotos() << endl;
	}

	if (guardaEncriptado)
	{
		string reporteEncriptado = Vigenere::encriptar("TODO", out.str());
		ofstream file;
		file.open("TODO", ios::app);
		file.write(reporteEncriptado.c_str(), reporteEncriptado.size());
		file.close();
	}
	else{
		cout << out.str();
	}

	delete abmConteo;
}

void Reportes::reportePorLista(string lista, bool guardaEncriptado)
{
	ABMConteo *abmConteo = new ABMConteo();
	ABMEleccion* abmEleccion = new ABMEleccion();
	ABMCargo* abmCargo = new ABMCargo();
	ABMDistrito* abmDistrito = new ABMDistrito();
	std::stringstream out;

	vector<Conteo> resultados =  abmConteo->GetConteoByLista(lista);

	if(resultados.size() == 0){
		out << "No se encontraron resultados." << endl;
		return;
	}

	//Primero ordeno por fecha de eleccion
	resultados = Reportes::OrderByFecha(resultados);


	//Agrupo por fecha de eleccion
	vector< vector<Conteo> > resAgrupados;
	vector<Conteo> cs;
	cs.push_back(resultados[0]);
	resAgrupados.push_back(cs);
	int idEleccionActual = resultados[0].GetIdEleccion();

	//Tengo que agrupar por eleccion
	for(int i = 1; i < resultados.size(); i++){

		  Conteo conteo = resultados[i];

		  if(conteo.GetIdEleccion() == idEleccionActual){

			resAgrupados[resAgrupados.size() - 1].push_back(conteo);
		  }
		  else{	//Nuevo grupo de eleccion

			  vector<Conteo> cs;
			  cs.push_back(conteo);
			  resAgrupados.push_back(cs);
			  idEleccionActual = conteo.GetIdEleccion();

		  }

	}

	for(int i = 0; i < resAgrupados.size(); i++){

		vector<Conteo> aux = Reportes::OrderByCantidadVotos(resAgrupados[i]);
		resAgrupados[i] = aux;
	}

	out << endl << endl << endl;

	for(int i = 0; i < resAgrupados.size(); i++){

		vector<Conteo> cs = resAgrupados[i];

		if(resAgrupados.size() > 0){

			Conteo conteo = cs[0];
			Eleccion* e = abmEleccion->GetEleccion(conteo.GetIdEleccion());
			string cargo = abmCargo->GetCargo(e->GetIdCargo())->GetNombre();
			Fecha fecha = e->GetDate().getStrFecha();

			out << "Eleccion: (" << fecha.getFriendlyStr() << " - " << cargo << ")" << endl;

			for(int j = 0; j < cs.size(); j++){
				Conteo res = cs[j];
				out << "		Distrito: " << res.GetIdDistrito() << " tiene " << res.GetCountVotos() << " votos." << endl;
			}
		}
	}

	if (guardaEncriptado){
		string reporteEncriptado = Vigenere::encriptar("TODO", out.str());
		ofstream file;
		file.open("TODO", ios::app);
		file.write(reporteEncriptado.c_str(), reporteEncriptado.size());
		file.close();
	}
	else{
		cout << out.str();
	}

	delete abmConteo;
	delete abmEleccion;
	delete abmCargo;
	delete abmDistrito;

}

void Reportes::reportePorDistrito(int idDistrito, bool guardaEncriptado)
{
	ABMConteo *abmConteo = new ABMConteo();
	ABMEleccion* abmEleccion = new ABMEleccion();
	ABMCargo* abmCargo = new ABMCargo();
	ABMDistrito* abmDistrito = new ABMDistrito();
	std::stringstream out;

	vector<Conteo> resultados =  abmConteo->GetConteoByDistrito(idDistrito);

	if(resultados.size() == 0){
		out << "No se encontraron resultados." << endl;
		return;
	}

	//Primero ordeno por fecha de eleccion
	resultados = Reportes::OrderByFecha(resultados);

	//Agrupo por fecha de eleccion
	vector< vector<Conteo> > resAgrupados;
	vector<Conteo> cs;
	cs.push_back(resultados[0]);
	resAgrupados.push_back(cs);
	int idEleccionActual = resultados[0].GetIdEleccion();

	//Tengo que agrupar por eleccion
	for(int i = 1; i < resultados.size(); i++){

	      Conteo conteo = resultados[i];

	      if(conteo.GetIdEleccion() == idEleccionActual){

	    	resAgrupados[resAgrupados.size() - 1].push_back(conteo);
	      }
	      else{	//Nuevo grupo de eleccion

		      vector<Conteo> cs;
		      cs.push_back(conteo);
		      resAgrupados.push_back(cs);
		      idEleccionActual = conteo.GetIdEleccion();

	      }

	}

	for(int i = 0; i < resAgrupados.size(); i++){

		vector<Conteo> aux = Reportes::OrderByCantidadVotos(resAgrupados[i]);
		resAgrupados[i] = aux;
	}

	out << endl << endl << endl;

	for(int i = 0; i < resAgrupados.size(); i++){

		vector<Conteo> cs = resAgrupados[i];

		if(resAgrupados.size() > 0){

			Conteo conteo = cs[0];
			Eleccion* e = abmEleccion->GetEleccion(conteo.GetIdEleccion());
			string cargo = abmCargo->GetCargo(e->GetIdCargo())->GetNombre();
			Fecha fecha = e->GetDate().getStrFecha();

			out << "Eleccion: (" << fecha.getFriendlyStr() << " - " << cargo << ")" << endl;

			for(int j = 0; j < cs.size(); j++){
				Conteo res = cs[j];
				out << "		Lista: " << res.GetIdLista() << " tiene " << res.GetCountVotos() << " votos." << endl;
			}
		}
	}

	if (guardaEncriptado)
	{
		string reporteEncriptado = Vigenere::encriptar("TODO", out.str());
		ofstream file;
		file.open("TODO", ios::app);
		file.write(reporteEncriptado.c_str(), reporteEncriptado.size());
		file.close();
	}
	else{
		cout << out.str();
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
