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
	//configFile->readInto(maxRecordPercent,"maxRecordPercent");

	/* El factor maximo de registro tiene que ser tal que si dos nodos NO estan en underflow,
	 * juntos tienen que dar overflow
	 * 2*minUnderFlowSizeTree = porcentajeCarga * tama�oBloque
	 * minUnderFlowSizeTree = tama�oBloque/2 - maxRecordPercent * tama�oBloque
	 *
	 * (tama�oBloque/2 - maxRecordPercent * tama�oBloque) * 2 = porcentajeCarga * tama�oBloque
	 * 1 - 2*maxRecordPercent = factorCarga
	 * maxRecordPercent = (1 - factorCarga)/2
	 */

	//chargeFactor = (int)(chargeFactor * 1000);
	//chargeFactor = (double)chargeFactor/1000;

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
ConfigurationMananger::~ConfigurationMananger() {
}

ChargeFactor ConfigurationMananger::getChargeFactor(){
	return this->chargeFactor;
}

int  ConfigurationMananger::getBufferSize(){
	return this->bufferSize;
}
