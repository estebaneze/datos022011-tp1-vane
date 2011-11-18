/*
 * ConteoIndex.h
 *
 *  Created on: 16/10/2011
 *      Author: minnie
 */

#ifndef INDEX_H_
#define INDEX_H_

#include "../Hash/Directory.h"
#include "../Common/Common.h"
#include "../Logging/HashLog.h"
#include "../Common/ProcessData.h"

using namespace std;

class Index {

	public:
		Index(string filename);
		virtual ~Index();

		/* Devuelve los valores indexados correspondientes al idKey */
		vector<Key> GetIds(Key idKey);

		/* Pisa los valores en el indice  del registro correspondientes al Id Key, con la lista de idsValues */
		void RefreshIndex(Key key, vector<Key> values);

		/* Agrega al registro del indice correspondiente al IdKey, el idValue. Si no existe el registro con el
		 * Id Key, lo crea */
		void AppendToIndex(Key key, Key value);
		void AppendToIndex(KeyInt key, Key value);

		void AppendToIndex(Key key,Key oldKey, Key value);
		void AppendToIndex(KeyInt key,KeyInt oldKey, Key value);

		void DeleteFromIndex(Key key, Key value);
		void DeleteFromIndex(KeyInt key, Key value);
	private:
		string processLogIx;
		string operationLogIx;
		string hashFile;
		Directory* directorio;
};

#endif /* INDEX_H_ */
