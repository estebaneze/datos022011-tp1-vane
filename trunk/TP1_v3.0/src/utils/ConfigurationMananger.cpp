#include "ConfigurationMananger.h"
#include <math.h>

ConfigurationMananger* ConfigurationMananger::instance = NULL;


ConfigurationMananger* ConfigurationMananger::getInstance(){
        if (ConfigurationMananger::instance == NULL)
                ConfigurationMananger::instance = new ConfigurationMananger();

    return ConfigurationMananger::instance;
}

ConfigurationMananger::ConfigurationMananger() {
        configFile = new ConfigFile("files/config.txt","=","#","EndConfigFile");

        double maxRecordPercent;

        configFile->readInto(bufferSize,"blockSize");
        configFile->readInto(bufferSizeTree,"treeBlockSize");
        configFile->readInto<double>(chargeFactor,"chargePercent");
        configFile->readInto(minRecordSizeTree,"minRecordSizeTree");
        //Tamaño de bloque de los archivos de hash
        configFile->readInto(hashBSizeCandidato,"hashBSizeCandidato");
        configFile->readInto(hashBSizeAdministrador,"hashBSizeAdministrador");
        configFile->readInto(hashBSizeCargo,"hashBSizeCargo");
        configFile->readInto(hashBSizeLista,"hashBSizeLista");
        configFile->readInto(hashBSizeVotante,"hashBSizeVotante");

        configFile->readInto<string>(separador1,"separador1");
        configFile->readInto<string>(separador2,"separador2");

        configFile->readInto<string>(identities,"identities");
        configFile->readInto<string>(cargaMasiva,"cargaMasiva");
        configFile->readInto<string>(votosAutomaticos,"votosAutomaticos");

        configFile->readInto<string>(adminFile,"adminFile");
    	configFile->readInto<string>(distritoFile,"distritoFile");
    	configFile->readInto<string>(candidatoFile,"candidatoFile");
    	configFile->readInto<string>(cargoFile,"cargoFile");
    	configFile->readInto<string>(conteoFile,"conteoFile");
    	configFile->readInto<string>(eleccionFile,"eleccionFile");
    	configFile->readInto<string>(listaFile,"listaFile");
    	configFile->readInto<string>(votanteFile,"votanteFile");


    	configFile->readInto<string>(logProcessEleccion,"logProcessEleccion");
    	configFile->readInto<string>(logOperEleccion,"logOperEleccion");
    	configFile->readInto<string>(logProcessDistrito,"logProcessDistrito");
    	configFile->readInto<string>(logOperDistrito,"logOperDistrito");
    	configFile->readInto<string>(logProcessConteo,"logProcessConteo");
    	configFile->readInto<string>(logOperConteo,"logOperConteo");
    	configFile->readInto<string>(logProcessCargo,"logProcessCargo");
    	configFile->readInto<string>(logOperCargo,"logOperCargo");
    	configFile->readInto<string>(logProcessCargo,"logProcessCargo");
    	configFile->readInto<string>(logOperCargo,"logOperCargo");
    	configFile->readInto<string>(logProcessAdmin,"logProcessAdmin");
    	configFile->readInto<string>(logOperAdmin,"logOperAdmin");
    	configFile->readInto<string>(logProcessLista,"logProcessLista");
    	configFile->readInto<string>(logOperLista,"logOperLista");
    	configFile->readInto<string>(logOperVotante,"logOperVotante");
    	configFile->readInto<string>(logProcessVotante,"logProcessVotante");
    	configFile->readInto<string>(logOperCandidato,"logOperCandidato");
    	configFile->readInto<string>(logProcessCandidato,"logProcessCandidato");
    	configFile->readInto<string>(logDirectory, "logDirectory");
    	configFile->readInto<string>(fileDirectory, "fileDirectory");
    	configFile->readInto<string>(reportFileDirectory, "reportFileDirectory");
    	configFile->readInto<string>(defaultVigenereKey, "defaultVigenereKey");


        //configFile->readInto(maxRecordPercent,"maxRecordPercent");
        //maxRecordPercent = (1-chargeFactor)/2;

        this->maxRecordSizeTree = this->bufferSizeTree*chargeFactor;

        //delete configFile;
}

int ConfigurationMananger::maxNodeLoadForInsert(){
        return floor(getChargeFactor()*getBufferSizeTree());
}

int ConfigurationMananger::getBufferSizeTree(){
        return this->bufferSizeTree;
}

int ConfigurationMananger::getMinUnderflowSizeTree() {
        // 50% del tamanioo maximo del bloque - el tamanio maximo del registro
        return ((this->bufferSizeTree/2) - this->getMaxRecordSizeTree());
}

int ConfigurationMananger::getMinRecordSizeTree(){
        return this->minRecordSizeTree;
}
int ConfigurationMananger::getMaxRecordSizeTree(){
        return this->maxRecordSizeTree;
}

ChargeFactor ConfigurationMananger::getChargeFactor(){
        return this->chargeFactor;
}

int  ConfigurationMananger::getBufferSize(){
        return this->bufferSize;
}

int ConfigurationMananger::getHashBSizeCandidato(){
        return this->hashBSizeCandidato;
}

int ConfigurationMananger::getHashBSizeAdministrador(){
        return this->hashBSizeAdministrador;
}

int ConfigurationMananger::getHashBSizeCargo(){
        return this->hashBSizeCargo;
}

int ConfigurationMananger::getHashBSizeLista(){
        return this->hashBSizeLista;
}

int ConfigurationMananger::getHashBSizeVotante(){
        return this->hashBSizeVotante;
}

string ConfigurationMananger::getSeparador1(){
        return this->separador1;
}

string ConfigurationMananger::getSeparador2(){
        return this->separador2;
}

string ConfigurationMananger::getIdentities(){
	return this->identities;
}

string ConfigurationMananger::getCargaMasiva(){
	return this->cargaMasiva;
}

string ConfigurationMananger::getVotosAutomaticos(){
	return this->votosAutomaticos;
}

string ConfigurationMananger::getAdminFile(){
	return this->adminFile;
}

string ConfigurationMananger::getDistritoFile(){
	return this->distritoFile;
}

string ConfigurationMananger::getCandidatoFile(){
	return this->candidatoFile;
}

string ConfigurationMananger::getCargoFile(){
	return this->cargoFile;
}

string ConfigurationMananger::getConteoFile(){
	return this->conteoFile;
}

string ConfigurationMananger::getEleccionFile(){
	return this->eleccionFile;
}

string ConfigurationMananger::getListaFile(){
	return this->listaFile;
}

string ConfigurationMananger::getVotanteFile(){
	return this->votanteFile;
}


ConfigurationMananger::~ConfigurationMananger() {
}

string ConfigurationMananger::getLogProcessVotanteFile()
{
	return this->logProcessVotante;
}

string ConfigurationMananger::getLogOperConteoFile()
{
	return this->logOperConteo;
}

string ConfigurationMananger::getLogOperAdminFile()
{
	return this->logOperAdmin;
}

string ConfigurationMananger::getLogOperVotanteFile()
{
	return this->logOperVotante;
}

string ConfigurationMananger::getLogOperEleccionFile()
{
	return this->logOperEleccion;
}

string ConfigurationMananger::getLogProcessListaFile()
{
	return this->logProcessLista;
}

string ConfigurationMananger::getLogProcessAdminFile()
{
	return this->logProcessAdmin;
}

string ConfigurationMananger::getLogOperCandidatoFile()
{
	return this->logOperCandidato;
}

string ConfigurationMananger::getLogOperCargoFile()
{
	return this->logOperCargo;
}

string ConfigurationMananger::getLogProcessEleccionFile()
{
	return this->logProcessEleccion;
}

string ConfigurationMananger::getLogProcessCandidatoFile()
{
	return this->logProcessCandidato;
}

string ConfigurationMananger::getLogProcessDistritoFile()
{
	return this->logProcessDistrito;
}

string ConfigurationMananger::getLogProcessCargoFile()
{
	return this->logProcessCargo;
}


string ConfigurationMananger::getLogProcessConteoFile()
{
	return this->logProcessConteo;
}

string ConfigurationMananger::getLogOperListaFile()
{
	return this->logOperLista;
}

string ConfigurationMananger::getLogOperDistritoFile()
{
	return this->logOperDistrito;
}

string ConfigurationMananger::getLogDirectory()
{
	return this->logDirectory;
}

string ConfigurationMananger::getFileDirectory()
{

	return this->fileDirectory;
}

string ConfigurationMananger::getReportFileDirectory()
{
	return this->reportFileDirectory;
}

string ConfigurationMananger::getDefaultVIgenereKey()
{
	return this->defaultVigenereKey;
}
