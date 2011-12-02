#ifndef CONFIGURATIONMANANGER_H_
#define CONFIGURATIONMANANGER_H_

#include "types.h"
#include <string>
#include "ConfigFile.h"

class ConfigurationMananger {
private:
        /** instancia del Singletone. */
        static ConfigurationMananger* instance;

        //Constructor privado
        ConfigurationMananger();

        /** Almacena el porcentaje util de un nodo */
        ChargeFactor chargeFactor;

        /** Define el los bloques cabecera. */
        int bufferSize;

        /**
         * Tamaño del buffer del arbol
         */
        int bufferSizeTree;

        /**
         * Tamaño minimo del registro que puede tener.
         */
        int minRecordSizeTree;

        /**
         * Tamaño maximo del registro que puede tener.
         */
        int maxRecordSizeTree;

        /**
         * Tamaño del bloque del los archivos de hash
         */
        int hashBSizeCandidato;
        int hashBSizeAdministrador;
        int hashBSizeCargo;
        int hashBSizeLista;
        int hashBSizeVotante;

        /* Tamaño de la clave RSA en bytes */
        int tamClaveRSA;

        /*
         * Separadores
         */
        string separador1;
        string separador2;

        /*
         * identities
         */
        string identities;

        /*
         * log de carga masiva
         */
        string cargaMasiva;
        string votosAutomaticos;
    	/*
    	 * Nombres de los archivos
    	 */
        string adminFile;
    	string candidatoFile;
    	string cargoFile;
    	string conteoFile;
    	string eleccionFile;
    	string listaFile;
    	string votanteFile;
    	string distritoFile;
    	string clavesFile;
        /*
         * Nombre de los archivos logs
         */
    	string logOperVotante;
    	string logProcessVotante;
    	string logOperCandidato;
    	string logProcessCandidato;
    	string logOperLista;
    	string logProcessLista;
    	string logOperAdmin;
    	string logProcessAdmin;
    	string logOperCargo;
    	string logProcessCargo;
       	string logOperConteo;
    	string logProcessConteo;
    	string logOperDistrito;
    	string logProcessDistrito;
    	string logOperEleccion;
    	string logProcessEleccion;
    	string logDirectory;
    	string fileDirectory;
    	string reportFileDirectory;
    	string defaultVigenereKey;

    	/**
         * Archivo de configuracion
         */
        ConfigFile *configFile;

public:

        virtual ~ConfigurationMananger();

     /**
         * Devuelve la unica instancia del singleton.
         */
        static ConfigurationMananger* getInstance();

        ChargeFactor getChargeFactor();
        int maxNodeLoadForInsert();

        /**
         * Tamano que tiene el buffer, Nodo, o bloque
         */
        int getBufferSize();

        int getBufferSizeTree();

        /**
         * Devuelve el tama�o minimo de underflow permitido
         *  50% tama�o del bloque -  el tama�o maximo del registro
         */
        int getMinUnderflowSizeTree();

        int getMinRecordSizeTree();

        int getMaxRecordSizeTree();

        /**
         * Devuelven el tamaño del bloque de los archivos de hash
         */
        int getHashBSizeCandidato();
        int getHashBSizeAdministrador();
        int getHashBSizeCargo();
        int getHashBSizeLista();
        int getHashBSizeVotante();

        /* Devuelve el tamaño en bytes de la clave RSA */
        int getTamClaveRSA();

        /**
         * Devuelve el tamaño de los separadores
         */
        string getSeparador1();
        string getSeparador2();
        /*
         * devuelve el nombre del archivo identities
         */
        string getIdentities();

        /*
         * devuerlve el nombre del archivo de logueo de votos automaticos
         */
        string getVotosAutomaticos();

        /*
         * devuerlve el nombre del archivo cargaMasiva
         */
        string getCargaMasiva();

    	/**
    	 * Devuelve el nombre de los archivos
    	 */
        string getAdminFile();
    	string getCandidatoFile();
    	string getCargoFile();
    	string getConteoFile();
    	string getEleccionFile();
    	string getListaFile();
    	string getVotanteFile();
    	string getDistritoFile();
    	string getClavesFile();
    	/*
    	 * Devuelve el nombre de los archivos de logs
    	 */

    	string getLogOperVotanteFile();
    	string getLogProcessVotanteFile();
    	string getLogOperCandidatoFile();
    	string getLogProcessCandidatoFile();
    	string getLogOperListaFile();
    	string getLogProcessListaFile();
    	string getLogOperAdminFile();
    	string getLogProcessAdminFile();
    	string getLogOperCargoFile();
    	string getLogProcessCargoFile();
    	string getLogOperConteoFile();
    	string getLogProcessConteoFile();
    	string getLogOperDistritoFile();
    	string getLogProcessDistritoFile();
    	string getLogOperEleccionFile();
    	string getLogProcessEleccionFile();
    	string getLogDirectory();
    	string getFileDirectory();
    	string getReportFileDirectory();
    	string getDefaultVIgenereKey();

};

#endif /* CONFIGURATIONMANANGER_H_ */
