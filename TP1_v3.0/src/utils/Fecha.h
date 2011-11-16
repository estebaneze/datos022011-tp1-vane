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
		Fecha(short dia, short mes, short anio);
		Fecha(std::string fecha);
		string getStrFecha();
		short getAnio() const;
		short getDia() const;
		short getMes() const;
		void setAnio(short anio);
		void setDia(short dia);
		void setMes(short mes);
		string getFriendlyStr();
		friend bool operator < (Fecha& fecha1, Fecha& fecha2);
		friend bool operator > (Fecha& fecha1, Fecha& fecha2);
		friend bool operator == (Fecha& fecha1, Fecha& fecha2);
		friend bool operator != (Fecha& fecha1, Fecha& fecha2);

	private:
		short dia;
		short mes;
		short anio;

};

#endif /* FECHA_H_ */
