#ifndef BUCKET_H_
#define BUCKET_H_



#include "key_node.h"
#include "refs.h"


/**Clase Bucket
 */
class Bucket
{
private:

	int N;//id del Bucket
	std::vector<std::pair<Key_Node,Refs> > bucket;	//<clave de hash , elems del array del bucket>
	int refs; //cantidad de referencia al buckets
    
public:
				
	Bucket();
	Bucket(int,int);
	Bucket(const Bucket &toCopy);

	/**Inserta la clave en el bucket
	 * @param key clave a insertar
	 * @param value numero de registro donde encontrar la clave en el archivo de datos
	 */
	void	insertKey( Key_Node &key, Refs value);

	/**Elimina la clave en el bucket
	 * @param key clave a eliminar
	 */
	void	deleteKey ( Key_Node &key);

	/**Obtiene el numero de bucket
	 * @return numero de bucket
	 */
	int		getNBucket() const;

	/**Obtiene el numero de registro donde encontrar la clave en el archivo de datos
	 */					
	Refs * 	getValue ( Key_Node &key);
	
	/**Verifica si el bucket esta vacio
	 */
	bool	empty();
	
	/**Devuelve la cantidad de pares clave-reg del bucket
	 */
	int	size();
		
        			
	/**Vacia el bucket
	 */
	void	clear();
	
	/**Devuelve el tamanio en bytes del bucket
	 */
	int		sizeKb() const;
	
	/**Devuelve el par clave-reg de la posicion indicada
	 */
	std::pair<Key_Node,Refs> at(int i);
	
	/**Obtiene el bucket
	 */
	std::vector<std::pair<Key_Node,Refs> >	getBucket();
	
	/**Verifica la existencia de una clave en el bucket
	 */
	bool exists( Key_Node &key);
	
	/**Agrega una referencia al bucket
	 */
	void 	addRef();	
	
	/**Actualiza las referencias al bucket
	 */
	void 	updateRef(int ref);				
	void 	duplicateRef();
	void divRef();
	int getRef();
	virtual ~Bucket(); 
};


#endif /*BUCKET_H_*/
