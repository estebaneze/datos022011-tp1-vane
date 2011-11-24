/*
 * VotanteLog.cpp
 *
 *  Created on: 22/10/2011
 *      Author: gabriel
 */

#include "VotanteLog.h"

void VotanteLog::LogSuccess(string info)
{
	string message="Votante con DNI: ";
	message.append(info);
	message.append(" logueado correctamente.");
	Log::WriteLog(message, "files/logs/Log_AutheticationSuccess_votante");
	//cout << message << endl;

}

void VotanteLog::LogChangeVoto(string dni,int idLista,int idListaAnterior)
{
	string lista = Helper::IntToString(idLista);
	string listaAnterior = Helper::IntToString(idListaAnterior);

	string message="Votante DNI: ";
	message.append(dni);
	message.append("cambio eleccion de Lista: ");
	message.append(listaAnterior);
	message.append(" por la Lista: ");
	message.append(lista);
	Log::WriteLog(message, "Log_ChangeVoto_votante");
}

void VotanteLog::LogUserInvalid(string info)
{
	string message="Se ingreso un votante con DNI: ";
	message.append(info);
	message.append(" inexistente.");

	Log::WriteLog(message, "files/logs/Log_AutheticationInvalid_votante");

}

void VotanteLog::LogPasswordInvalid(string info)
{
	string message="El votante con DNI: ";
	message.append(info);
	message.append(" ingreso password incorrecto.");

	Log::WriteLog(message, "files/logs/Log_AutheticationInvalid_votante");

}

void VotanteLog::LogVoto(string dni, int idLista)
{
	string lista = Helper::IntToString(idLista);

	string message="Votante DNI: ";
	message.append(dni);
	message.append(" voto Lista: ");
	message.append(lista);
	Log::WriteLog(message, "files/logs/Log_Voto_votante");
}



VotanteLog::VotanteLog() {
	// TODO Auto-generated constructor stub

}

VotanteLog::~VotanteLog() {
	// TODO Auto-generated destructor stub
}
