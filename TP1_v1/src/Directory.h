#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include <vector>
#include <string>


class Directory
{
	
private:

	std::vector<std::pair<int,int> > directory;
	int	actualBits;
	
public:
	Directory();
	Directory(const Directory &toCopy);
	std::vector<std::pair<int, int> > getDirectory ();
	/**Duplica la cantidad de direcciones del directorio replicando las
	 * referencias a los buckets.
	 */
	void duplicateDirectory ();

	/**Reduce el directorio cuando todos los buckets tienen mas de 2 referencias
	 * y se ha eliminado un bit en la funcion de hashing.					  
	 */
	void reduceDirectory ();
	
	/**Inserta una direccion en el directorio con un numero de referencia al bucket
	 * al que apunta.
	 */
	void insertDir (int Dir, int nBlockBucket);		
	
	/**Actualiza el numero de referencia del bucket al que apunta la direccion
	 */
	void updateDir (int Dir, int nBlockBucket);
	
	/**Devuelve la cantidad de direcciones del directorio
	 */
	int getNDir ();
	
	/**Devuelve el numero de Bucket al que apunta una direccion.
	 */
	int getNBlockBucket(int Dir) const;
					
	void redirect(int nB, int newBlockBucket, int nRef);	
	
	/**Crea el archivo de directorio mediante los servicios de la capa física
	 * @see opf::organization::PhysicalLayer
	 */
	void createDirectory(std::string fileName);
	
	/**Carga el directorio desde el archivo mediante los servicios de la capa física
	 * @see PhysicsalLayer
	 */					
	void loadDirectory(std::string fileName);
	
	std::vector<std::pair<int,int> >::iterator 	it (int Dir);
	
	bool exists(int Dir);
	
	int getActualBits();
	
	void updateBits(int actualBits);
	
	std::pair<int,int> at(unsigned int);
	
    unsigned int size();
	
	void	destroy();
	~Directory();
};


#endif /*DIRECTORY_H_*/
