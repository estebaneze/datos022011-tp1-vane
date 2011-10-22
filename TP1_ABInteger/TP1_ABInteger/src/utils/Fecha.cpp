/*
 * Fecha.cpp
 *
 *  Created on: 18/10/2011
 *      Author: loo
 */

#include "Fecha.h"

Fecha::Fecha() {
}

Fecha::Fecha(short dia, short mes, short anio) {
	this->dia = dia;
	this->mes = mes;
	this->anio = anio;
}

Fecha::Fecha(std::string fecha) {

	if(fecha.length() != 8){
		cout << "Error al construir la fecha" << endl;
		return;
	}

	this->dia = Helper::StringToInt(fecha.substr(4,2));
	this->mes = Helper::StringToInt(fecha.substr(6,2));
	this->anio = Helper::StringToInt(fecha.substr(0,4));
}

std::string Fecha::getStrFecha(){

	string sanio = Helper::IntToString(anio);
	string smes= Helper::IntToString(mes);
	if(mes < 10){
		smes = "0";
		smes.append(Helper::IntToString(mes));
	}

	string sdia= Helper::IntToString(dia);
	if(dia < 10){
		sdia = "0";
		sdia.append(Helper::IntToString(dia));
	}

	return Helper::concatenar(Helper::concatenar(sanio,smes,""),sdia,"");
}

short Fecha::getAnio() const{
    return anio;
}

short Fecha::getDia() const{
    return dia;
}

short Fecha::getMes() const{
    return mes;
}

void Fecha::setAnio(short anio){
    this->anio = anio;
}

void Fecha::setDia(short dia){
    this->dia = dia;
}

void Fecha::setMes(short mes){
    this->mes = mes;
}

bool operator < (Fecha& fecha1, Fecha& fecha2){

	if(fecha1.getAnio() < fecha2.getAnio())
		return true;

	if(fecha1.getAnio() == fecha2.getAnio()){

		if(fecha1.getMes() < fecha2.getMes())
			return true;

		if(fecha1.getMes() == fecha2.getMes()){
			if(fecha1.getDia() < fecha2.getDia())
					return true;
		}
	}

	return false;
}

bool operator > (Fecha& fecha1, Fecha& fecha2){

	return !(fecha1 < fecha2);
}

bool operator == (Fecha& fecha1, Fecha& fecha2){

	return(fecha1.anio == fecha2.anio &&
			fecha1.mes == fecha2.mes &&
			fecha1.dia == fecha1.dia);
}


bool operator != (Fecha& fecha1, Fecha& fecha2){

	return !(fecha1 == fecha2);
}

Fecha::~Fecha() {
}

