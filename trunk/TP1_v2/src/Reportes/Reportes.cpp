/*
 * Reportes.cpp
 *
 *  Created on: 18/10/2011
 *      Author: ricardo
 */

#include "Reportes.h"

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
	resultados = Reportes::OrderByFecha(resultados);
	vector<Conteo>::iterator it = resultados.begin();

	Conteo conteo = (Conteo) *it;

	vector< vector<Conteo> > resAgrupados;
	vector<Conteo> c1;
	resAgrupados.push_back(c1);
	int j = 0;
	string idEleccionActual = conteo.GetEleccion()->GetId();

	//Tengo que agrupar por eleccion
	for (it = resultados.begin(); it != resultados.end(); it++) {

		conteo = (Conteo) *it;

		string idEleccionAux = conteo.GetEleccion()->GetId();
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

	cout << endl << endl << endl;
	cout << "Reporte por lista:" << endl << endl;

	for(int i = 0; i < resAgrupados.size(); i++){

		vector<Conteo> cs = resAgrupados[i];
		cout << "Eleccion: " << cs[0].GetEleccion()->GetId() << endl;

		for(int j = 0; j < cs.size(); j++){
			Conteo res = cs[j];
			cout << "		Distrito: " << res.GetIdDistrito() << " tiene " << res.GetCountVotos() << " votos." << endl;
		}
	}

}

void Reportes::reportePorDistrito(int idDistrito)
{
	return;
}













/* Ordena el vector de Conteos por cantidad de votos. */
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

	Conteo aux;

	for (int i=0; i <= resultados.size()-1; i++) {

		for (int j = i+1 ;j < resultados.size();j++)	{

			Fecha f1 = resultados[i].GetEleccion()->GetDate();
			Fecha f2 = resultados[j].GetEleccion()->GetDate();
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
