#include "Buckets.h"
#include "Directory.h"
#include <fstream>
 #include <sstream>
#ifndef CTEHASH
#define CTEHASH 0.6180338997
#endif
class HashExtensible 
{
				
    private:
    	int bucketCapacity;		 
        int 	actualbits;	
        Buckets		buckets;
    	Directory 	directory;
    	string filename;
        				
     int	getPrevDir (int);
    public:
    				 	 				
        //! Construye un indice de Hash a partir de un archivo de directorio y un archivo de buckets
        /*!
         * @param filePath Nombre del archivo de directorio
         * @param blockSize Tamanio del bloque
         * @param keyTypes vector de tipos de claves que se indexaran
         * @return Direccion que se asociara a un numero de bucket donde se encontrara la clave.
         */
        
     	 HashExtensible();
     	 HashExtensible(std::string filename);
        HashExtensible(std::string filename, int BucketCap);
        
        //! Funci�n de Hash.
        /*!
         * @param key Clave a insertar
         * @return Direccion que se asociara a un numero de bucket donde se encontrara la clave.
         */
        int 	fHash(Key_Node &key);
        					
        //! Guarda la clave junto con el numero de registro al que apunta.
        /*!
         * \param key Clave a insertar
         * \param reg Numero de Registro al que apunta.
         */	
        
        void 	add (Key_Node &key, Refs value);
        
        //! Elimina una clave del indice
        /*!
         * @param key Clave a eliminar
         */
         
         
         void save();
         void load();
         
        void 	del ( Key_Node &key) ; 
        
        //! Obtiene el numero de registro donde se encuentra la clave en el archivo
        /*!
         * @param key Clave a obtener
         * @return Numero de registro
         */
        Refs * 	get ( Key_Node &key);
        //! Verifica la existencia de una clave en el indice
        /*!
         * @param key Clave a buscar
         * @return devuelve si la clave existe o no
         */
        bool	contains ( Key_Node &key);
        
        std::vector< Refs > getUpTo( Key_Node &key, bool includeKeyValue = true);
        std::vector< Refs > getFrom( Key_Node &key, bool includeKeyValue = true);
        std::vector< Refs > getRange( Key_Node &leftBound,  Key_Node &rightBound, bool includeLeftValue = true, bool includeRightValue = true);
        			
        bool	isEmpty();
        void 	view();
        //void 	destroy();

        					
        ~HashExtensible();
};

