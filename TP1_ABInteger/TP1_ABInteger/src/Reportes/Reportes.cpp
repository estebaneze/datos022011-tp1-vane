/*
 * Reportes.cpp
 *
 *  Created on: 18/10/2011
 *      Author: ricardo
 */

#include "Reportes.h"

/*TODO: este metodo tendria que recibir: fecha y cargo y de ahi buscar la eleccion, o el objecto Eleccion
 */

void Reportes::reportePorEleccion(int IdEleccion)
{
	/*std::cout << "**********************************************************" << std::endl;
	std::cout << "TOTAL VOTOS LISTA PARA ELECCION: " << Helper::IntToString(IdEleccion) << std::endl;
	std::cout << "**********************************************************" << std::endl << std::endl << std::endl;

	std::cout << "Lista               %         (Total Votos)" << std::endl;
	std::cout << "-----               -         -------------" << std::endl << std::endl << std::endl;

	ABMConteo *abmConteo = new ABMConteo();

	vector<Conteo> vectorConteo =  abmConteo->GetConteoByEleccion(IdEleccion);
	vector<Conteo>::iterator it = vectorConteo.begin();

	Conteo conteo = (Conteo) *it;
	string idLista = conteo.GetIdLista();
	string idListaAux;

	long totalVotosxEleccion = vectorConteo.size();
	long totalVotosLista = 0;

	for (it = vectorConteo.begin(); it != vectorConteo.end(); it++) {

		conteo = (Conteo) *it;
		idListaAux = conteo.GetIdLista();

		if (idLista.compare(idListaAux) == 0)
		{
			std::cout << idLista << "    " << Helper::FloatToString(totalVotosLista/totalVotosxEleccion) << "    " << "(" << Helper::LongToString(totalVotosLista) << ")" << std::endl << std::endl;
			totalVotosLista = 0;
			idLista = idListaAux;
		}

		totalVotosLista++;
	}
*/
}

void Reportes::reportePorLista(string lista)
{
	ABMConteo *abmConteo = new ABMConteo();

	vector<Conteo> resultados =  abmConteo->GetConteoByLista(lista);
	for(int i = 0; i < resultados.size(); i++){
		cout << "eleccion: " << resultados[i].GetIdDistrito() << ". Votos:  " << resultados[i].GetCountVotos() << endl;
	}
	cout << endl << endl;

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
		cout << "eleccion " << idEleccionAux << endl;;
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
	cout << "Reporte por lista:" << endl << endl;

	for(int i = 0; i < resAgrupados.size(); i++){

		vector<Conteo> cs = resAgrupados[i];
		cout << "Eleccion: " << cs[0].GetIdEleccion() << endl;

		for(int j = 0; j < cs.size(); j++){
			Conteo res = cs[j];
			cout << "		Distrito: " << res.GetIdDistrito() << " tiene " << res.GetCountVotos() << " votos." << endl;
		}
	}

}

void Reportes::reportePorDistrito(int idDistrito)
{
	ABMConteo *abmConteo = new ABMConteo();

	vector<Conteo> resultados =  abmConteo->GetConteoByDistrito(idDistrito);
	for(int i = 0; i < resultados.size(); i++){
		cout << "eleccion: " << resultados[i].GetIdDistrito() << ". Votos:  " << resultados[i].GetCountVotos() << endl;
	}
	cout << endl << endl;

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
		cout << "eleccion " << idEleccionAux << endl;;
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
	cout << "Reporte por lista:" << endl << endl;

	for(int i = 0; i < resAgrupados.size(); i++){

		vector<Conteo> cs = resAgrupados[i];
		cout << "Eleccion: " << cs[0].GetIdEleccion() << endl;

		for(int j = 0; j < cs.size(); j++){
			Conteo res = cs[j];
			cout << "		Distrito: " << res.GetIdDistrito() << " tiene " << res.GetCountVotos() << " votos." << endl;
		}
	}

}

/* Ordena el vector de Conteos por cantidad de votos.
 * TODO: ESTA ORDENANDO DE MENOR A MAYOR. TIENE QUE SER AL REVES.
 * */
vector<Conteo> Reportes::OrderByCantidadVotos(vector<Conteo> resultados){

	Conteo aux;

	for (int i=0; i <= resultados.size()-1; i++) {

		for (int j = i+1 ;j < resultados.size();j++)	{

			if (resultados[i].GetCountVotos() > resultados[j].GetCountVotos()) {
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
			if(f1 > f2){
				aux = resultados[i];
				resultados[i] = resultados[j];
				resultados[j] = aux;
			}
		}
	}

	return resultados;
}
