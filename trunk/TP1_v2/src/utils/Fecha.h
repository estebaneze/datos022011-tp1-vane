/*
 * Fecha.h
 *
 *  Created on: 18/10/2011
 *      Author: loo
 */

#ifndef FECHA_H_
#define FECHA_H_
#include "../Common/Common.h"

class Fecha {
public:

	virtual ~Fecha();
	Fecha();
	Fecha(ushort dia, ushort mes, ushort anio);
	Fecha(std::string fecha);
	string getStrFecha();
	ushort getAnio() const;
	ushort getDia() const;
	ushort getMes() const;
	void setAnio(ushort anio);
	void setDia(ushort dia);
	void setMes(ushort mes);

private:
	ushort dia;
	ushort mes;
	ushort anio;
};

#endif /* FECHA_H_ */
