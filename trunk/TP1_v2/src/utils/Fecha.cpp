/*
 * Fecha.cpp
 *
 *  Created on: 18/10/2011
 *      Author: loo
 */

#include "Fecha.h"

Fecha::Fecha() {
}

Fecha::Fecha(ushort dia, ushort mes, ushort anio) {
	this->dia = dia;
	this->mes = mes;
	this->anio = anio;
}

Fecha::Fecha(std::string fecha) {
	this->dia = Helper::StringToInt(fecha.substr(5,2));
	this->mes = Helper::StringToInt(fecha.substr(3,2));
	this->anio = Helper::StringToInt(fecha.substr(0,4));
}

std::string Fecha::getStrFecha(){
	string sanio = Helper::IntToString(anio);
	string smes= Helper::IntToString(mes);
	string sdia= Helper::IntToString(dia);
	return Helper::concatenar(Helper::concatenar(sanio,smes,""),sdia,"");
}

ushort Fecha::getAnio() const{
    return anio;
}

ushort Fecha::getDia() const{
    return dia;
}

ushort Fecha::getMes() const{
    return mes;
}

void Fecha::setAnio(ushort anio){
    this->anio = anio;
}

void Fecha::setDia(ushort dia){
    this->dia = dia;
}

void Fecha::setMes(ushort mes){
    this->mes = mes;
}

Fecha::~Fecha() {
}
