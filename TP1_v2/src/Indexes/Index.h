/*
 * ConteoIndex.h
 *
 *  Created on: 16/10/2011
 *      Author: minnie
 */

#ifndef INDEX_H_
#define INDEX_H_

#include "../Hash/KeyValue.h"
#include "../Hash/Directory.h"
#include "../Common/Entidades.h"
#include "../Common/Common.h"


class Index {

	public:
		Index(string filename);
		virtual ~Index();

		/* Devuelve los valores indexados correspondientes al idKey */
		vector<int> GetIds(int idKey);

		/* Pisa los valores en el indice  del registro correspondientes al Id Key, con la lista de idsValues */
		void RefreshIndex(int idKey, vector<int> idsValues);

		/* Agrega al registro del indice correspondiente al IdKey, el idValue. Si no existe el registro con el
		 * Id Key, lo crea */
		void AppendToIndex(int idKey, int idValue);


	private:
		string hashFile;
		Directory* directorio;
};

#endif /* INDEX_H_ */

