/*
 * Reportes.cpp
 *
 *  Created on: 18/10/2011
 *      Author: ricardo
 */

#include "Reportes.h"

void Reportes::reportePorEleccion(int IdEleccion)
{
	std::cout << "**********************************************************" << std::endl;
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

}

void Reportes::reportePorLista(int idLista)
{
	return;
}

void Reportes::reportePorDistrito(int idDistrito)
{
	return;
}
