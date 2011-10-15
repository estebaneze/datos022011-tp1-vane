/**
 * Clase singleton que permite hacer logging de mensajes
 * sobre uno o varios archivos de log
 * autor nromani, ssoria.
 */

#include "Logger.h"

//#define DEBUG_MODE false

Logger* Logger::logger = NULL;
int Logger::limit = 100000;

Logger::Logger() {
	//Logger::limit = cantRegistros;
	Logger::nextFile = Logger::setNextFile();
	Logger::count = 0;
	std::string c;


	ioFile.open("logger.log", std::ios_base::in);
	if (ioFile.is_open())
		while(!ioFile.eof()){
			getline(ioFile,c);
			if(c.compare(""))
				Logger::count++;
		}


	ioFile.close();
	ioFile.open("logger.log", std::ios_base::out | std::ios_base::app);
}

Logger* Logger::getInstance(){
	if ( Logger::logger  == NULL )
		Logger::logger = new Logger();
	return Logger::logger;
}

void Logger::setLimit(int cantRegistros) {
	Logger::limit = cantRegistros;
}

Logger::~Logger(){
	ioFile.close();
}

void Logger::renameFile(){
	ioFile.close();

	std::stringstream file;
	file << "logger" << Logger::nextFile << ".log";

	rename("logger.log", file.str().c_str());

	Logger::nextFile ++;
	Logger::count = 0;

	ioFile.open("logger.log", std::ios_base::out | std::ios_base::app);
}

std::string Logger::getTime(){
	time_t rawtime;
	time(&rawtime);
	struct tm* timestamp = localtime(&rawtime);

	std::stringstream out;
	if (timestamp->tm_mday < 10)
		out << "0" << timestamp->tm_mday << "/" ;
	else out << timestamp->tm_mday << "/" ;
	if (timestamp->tm_mon < 10)
		out << "0" << timestamp->tm_mon + 1 << "/" ;
	else out << timestamp->tm_mon + 1 << "/" ;
	out << timestamp->tm_year + 1900;
	out << " ";
	if (timestamp->tm_hour < 10 )
		out << "0" << timestamp->tm_hour << ":"  ;
	else out << timestamp->tm_hour << ":";
	if (timestamp->tm_min < 10 )
		out << "0" << timestamp->tm_min << ":" ;
	else out << timestamp->tm_min << ":";
	if (timestamp->tm_sec < 10 )
		out << "0" << timestamp->tm_sec ;
	else out << timestamp->tm_sec;
	out << " ";
	return out.str();
}

int Logger::setNextFile(){
	bool right = false;
	int i = 1;
	while (!right){
		std::stringstream file;
		file << "logger" << i << ".log";

		if ( access(file.str().c_str(),0) != 0)
			right = true;
		else i++;
	}
	return i;
}
void Logger::warn(std::string  message){
	std::string key = "WARN :";
	Logger::insert(key,message);
}

void Logger::info(std::string message){
	std::string key = "INFO :";
	Logger::insert(key,message);
}

void Logger::debug(std::string  message){
	std::string key = "DEBUG :";
	Logger::insert(key,message);
}

void Logger::error(std::string  message){
	std::string key = "ERROR :";
	Logger::insert(key,message);
}

void Logger::insert(std::string& key, std::string& value){
	if (ioFile.is_open()) {

		#ifdef DEBUG_MODE
			std::cout << Logger::getTime() << key << " " << value << std::endl;
		#endif

		ioFile << Logger::getTime() << key << " " << value << std::endl;
		ioFile.flush();
		Logger::count++;

		if (Logger::count >= Logger::limit) Logger::renameFile();
	} else throw new FileNotOpenException();
}

int Logger::buscar(std::string cadena) {
	std::string c, numArchivo = "" ;
	std::string nombreArchivo = "logger.log";
	Logger* logger = Logger::getInstance();
	int ultimoArchivo = logger->nextFile;
	int cantTotalOcurrencias = 0, cantOcurrencias, cantArchivos = 0, cantOcurrenciasArchivo = 0;
	std::cout << "------------------------ INICIO DE BUSQUEDA -------------------------" << std::endl;
	for (cantArchivos= 0; cantArchivos < ultimoArchivo; ++cantArchivos) {
		std::cout << "---------------------------------------------------------------------" << std::endl;
		std::cout << "Ocurrencias en el archivo: " << nombreArchivo << std::endl;
		ioFile.close();
		ioFile.open(nombreArchivo.c_str(), std::ios::in);
		if (ioFile.is_open())
			cantOcurrenciasArchivo = 0;
			while (!ioFile.eof()) {
				cantOcurrencias = 0;
				getline(ioFile, c);
				cantOcurrencias = Logger::encontrarOcurrencias(c, cadena);
				if (cantOcurrencias > 0) {
					cantTotalOcurrencias = cantTotalOcurrencias + cantOcurrencias;
					cantOcurrenciasArchivo = cantOcurrenciasArchivo + cantOcurrencias;
					std::cout << c << std::endl;
				}
			}
		std::cout << ""<< std::endl;
		std::cout <<  cantOcurrenciasArchivo <<" ocurrencia/s " << std::endl;
		std::cout << "---------------------------------------------------------------------" << std::endl;
		ioFile.close();

		ioFile.open(nombreArchivo.c_str(), std::ios::out | std::ios::app);
		std::ostringstream stream;
		stream << cantArchivos + 1;
		std::string numArchivo = stream.str();
		nombreArchivo = "logger" + numArchivo + ".log";
	}
	std::cout << "---------------------------FIN BÚSQUEDA------------------------------" << std::endl;
	std::cout << "TOTAL OCURRENCIAS EN ARCHIVOS:" << cantTotalOcurrencias << std::endl;

	return cantTotalOcurrencias;
}

int Logger::encontrarOcurrencias(std::string cadena, std::string subCadena)
{
	const char *tmp = cadena.c_str();
	const char *pdest;
	int ocur = 0, pos;
	int len = strlen(subCadena.c_str());
	while (1) {
		pdest = strstr(tmp, subCadena.c_str());
		if (!pdest)
			break;
		pos = pdest - tmp;
		tmp += pos + len;
		ocur++;
	}
	return ocur;
}

void Logger::listar() {
	std::string c, numArchivo = "" ;
	std::string nombreArchivo = "logger.log";
	Logger* logger = Logger::getInstance();
	int ultimoArchivo = logger->nextFile;
	int cantArchivos = 0;
	for (cantArchivos= 0; cantArchivos < ultimoArchivo; ++cantArchivos) {
		std::cout << "--------------------------------------------------------------------" << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
		std::cout << "LISTADO DEL ARCHIVO " << nombreArchivo << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
		ioFile.close();
		ioFile.open(nombreArchivo.c_str(), std::ios::in);
		if (ioFile.is_open())
			while (!ioFile.eof()) {
				getline(ioFile, c);
				if(c.compare(""))
					std::cout <<  "Línea: " << c << std::endl;
			}
		ioFile.close();

		ioFile.open(nombreArchivo.c_str(), std::ios::out | std::ios::app);
		std::ostringstream stream;
		stream << cantArchivos + 1;
		std::string numArchivo = stream.str();
		nombreArchivo = "logger" + numArchivo + ".log";
	}
}
