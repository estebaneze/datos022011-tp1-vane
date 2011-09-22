#include "ComuDatos.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include  <cstring>
#include <cstdio>

#define CORRIMIENTOARGUMENTO 3

	 
int contarArgv(char **argv)
{
	int contador;
	for(contador = 0; argv[contador] != NULL; contador++);
	return contador;
}


ComuDatos::ComuDatos()
{
	this->id_procesoHijo = 0;
	this->fd_pipeP     = 0; 
	this->fd_pipeH     = 0; 
	this->cantParametros = 0;	
}

ComuDatos::ComuDatos(string nombreEjecutable)
{
	this->id_procesoHijo = 0;
	this->fd_pipeP     = 0; 
	this->fd_pipeH     = 0; 
	this->cantParametros = 0;	
	this->nombreProceso = nombreEjecutable;
}

ComuDatos::ComuDatos(char** argv)
{
	int contador = contarArgv(argv);
	
	if (contador >= CORRIMIENTOARGUMENTO){
		this->fd_pipeP = open(argv[2], O_WRONLY);
		if (this->fd_pipeP<0) return;
		
		this->fd_pipeH = open(argv[1], O_RDONLY);
		if (this->fd_pipeH<0){
			close(this->fd_pipeH);
			perror("argv[]");
			return;	
		}	
		this->parametrosProceso.resize(contador-CORRIMIENTOARGUMENTO);
		for (int i = 0; i<(contador-CORRIMIENTOARGUMENTO); i++)
			this->parametrosProceso.at(i) = argv[i+CORRIMIENTOARGUMENTO];
	}
	
}

//! parametros tiene que ser NULL o tener un puntero a NULL en el último lugar del vector.
void ComuDatos::lanzar()
{
	char *argumentos[this->parametrosProceso.size()+CORRIMIENTOARGUMENTO+1];

	if (this->nombreProceso.length() == 0)
	{
		cout << "Error en lanzar" << endl;
		return; 
	}
	
	string pipeLee = this->nombreProceso + "_ComuDatosH";
	string pipeEscribe = this->nombreProceso + "_ComuDatosP";
	mkfifo(pipeLee.c_str(), 0666);
	mkfifo(pipeEscribe.c_str(), 0666);
	
	// Parametro 1 lectura y 2 escritura hijo.
	argumentos[1] = (char*) malloc (sizeof(char)*pipeEscribe.length()+1);
	strcpy(argumentos[1], pipeEscribe.c_str());
	argumentos[2] = (char*) malloc (sizeof(char)*pipeLee.length()+1);
	strcpy(argumentos[2], pipeLee.c_str());
	
	argumentos[0] = (char*) malloc (sizeof(char)*(this->nombreProceso.length()+1));
	strcpy(argumentos[0], this->nombreProceso.c_str());
	for(unsigned int i=3; i<(this->parametrosProceso.size()+CORRIMIENTOARGUMENTO); i++)
	{
		argumentos[i] = (char*) malloc (sizeof(char)*(this->parametrosProceso.at(i-CORRIMIENTOARGUMENTO).length()+1));
		strcpy(argumentos[i], this->parametrosProceso.at(i-CORRIMIENTOARGUMENTO).c_str());
	}
	argumentos[this->parametrosProceso.size()+CORRIMIENTOARGUMENTO] = NULL;
	
	this->id_procesoHijo = fork();

	if (this->id_procesoHijo > 0)
	{
		execv(argumentos[0], argumentos);
	}

	this->fd_pipeH = open(pipeLee.c_str(), O_RDONLY);
	this->fd_pipeP = open(pipeEscribe.c_str(), O_WRONLY);
}

void ComuDatos::ejecutable(string nombreEjecutable)
{
		this->nombreProceso = nombreEjecutable;
}

void ComuDatos::agregarParametro(int valorParametro, unsigned int posParametro)
{
	char num[20];
	sprintf(num,"%d",valorParametro);
	if (posParametro >= this->parametrosProceso.size())
	{
		this->parametrosProceso.resize(posParametro+1);
	}
	this->parametrosProceso.at(posParametro) = num;
}

void ComuDatos::agregarParametro(string valorParametro, unsigned int posParametro)
{
	if (posParametro+1 >= this->parametrosProceso.size())
	{
		this->parametrosProceso.resize(posParametro+1);	
	}
	this->parametrosProceso[posParametro] = valorParametro;
}

string ComuDatos::parametro(unsigned int posParametro)
{	
	if (posParametro < this->parametrosProceso.size())
		return this->parametrosProceso[posParametro];
	else
		return FIN_PARAMETROS;
	
}

int ComuDatos::fd_leer()
{
	return this->fd_pipeH;
}

int ComuDatos::fd_escribir()
{
	return this->fd_pipeP;
}
 
void ComuDatos::escribir(string enviarDato)
{
	if (enviarDato.length()<(TOPE_ENVIAR_STRING-1))
	{
		write(this->fd_pipeP, enviarDato.c_str(), (enviarDato.length()+1)*sizeof(char));
	}
}

string ComuDatos::leer(int cantidad)
{
	if (cantidad <= TOPE_ENVIAR_STRING)
	{		
		char leo[TOPE_ENVIAR_STRING];
		read(this->fd_pipeH, leo, cantidad);
		leo[cantidad] = 0;
		string retorno = leo;
		return retorno;
	}else return "";
}

void ComuDatos::liberarRecursos()
{
	if (this->nombreProceso.length() > 0)
	{
		string nombre = this->nombreProceso + "_ComuDatosH";
		
		unlink(nombre.c_str());
		nombre = this->nombreProceso + "_ComuDatosP";
		unlink(nombre.c_str());
	}
}

ComuDatos::~ComuDatos()
{
	liberarRecursos();
}
