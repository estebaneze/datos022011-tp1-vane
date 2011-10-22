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

        //configFile->readInto(maxRecordPercent,"maxRecordPercent");
        maxRecordPercent = (1-chargeFactor)/2;

        this->maxRecordSizeTree = this->bufferSizeTree*maxRecordPercent;

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

ConfigurationMananger::~ConfigurationMananger() {
}

