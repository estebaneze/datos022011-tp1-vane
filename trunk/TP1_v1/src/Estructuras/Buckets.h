#ifndef BUCKETS_H_
#define BUCKETS_H_


#define BUCKET_CAP 4

#include "Bucket.h"	
#include "key_node.h"						
/**Provee toda la funcionalidad para manejar un archivo de buckets, con acceso a 
 * un buffer de memoria.
 */
class Buckets
{
private:

	int	 bucketCapacity;

	std::vector<Bucket> buckets;																	
	
public:
    Buckets();
    Buckets(int inbucketCapacity);
	/**Constructor de buckets. 
	 * Si el archivo de buckets existe, obtiene la relacion 
	 * numero de bucket - numero de bloque.
	 * Sino, crea el archivo con el formato especificado por parametro.
	 * @param keyTypes tipos de claves que se guardaran en los buckets.
	 */
	Buckets(const Buckets &toCopy);
    	
	/**Obtiene un bucket buscandolo en el buffer 
	 * @see BucketsBuffer
	 * Si no lo encuentra, lo levanta del archivo de buckets mediante los servicios 
	 * de la capa fisica 
	 * @see PhysicalLayer
	 * Guarda el bucket en el buffer o actualiza su posicion LRU segun corresponda.
	 */
	Bucket 	getBucket (int nBucket);
	
	/**Actualiza un bucket en el buffer y en el archivo de buckets.
	 */
	void	updateBucket(int nBucket, Bucket& tempBucket);
	
	/**Verifica si un bucket esta lleno.
	 * @param size tamanio de clave que se quiere agregar al bucket
	 */
	bool	isFull (int nBucket); 
	
	/**Obtiene el bucket, inserta la clave y lo actualiza.
	 */

	
	void 	insertKey(int nBlockBucket, Key_Node &key, Refs value);
	
	/**Obtiene el bucket, elimina la clave y lo actualiza.
	 */					
	void 	deleteKey(int nBucket,  Key_Node &key);
	
	/**Crea un bucket en el archivo de buckets segun el formato de bucket especificado
	 */
	int  	createBucket();
	
	/**Elimina el bucket actualizando el archivo y el buffer.
	 */
	void	deleteBucket(int nBucket);
	
	/**Vacia el bucket especificado y lo actualiza.
	 */
	void 	clearBucket(int nBucket);
	
	/**Devuelve la capacidad en bits del bucket
	 */
	unsigned int  	getBucketCapacity();
	
	/**Devuelve la cantidad de buckets actuales, leyendo el primer byte del archivo
	 * de buckets.
	 */
	int  	getNBuckets();
	
	/**Actualiza la cantidad de buckets actual.
	 */
	void 	addRef (int nBucket);
	void 	updateRef(int nBlockBucket, int ref);
	void	duplicateRef (std::vector<std::pair<int, int> > nBlocks);
	void	divRef (std::vector<std::pair<int, int> > nBlocks);
	int 	minRef(std::vector<std::pair<int, int> > nBlocks);
	int 	getNBucket(int nBlockBucket);
	virtual ~Buckets(); 
};

#endif /*BUCKETS_H_*/

