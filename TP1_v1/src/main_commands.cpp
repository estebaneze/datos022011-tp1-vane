/**************************************************************************
             MAIN
 ***************************************************************************/
/*
#include <iostream>

//#include "HashExtensible.h"
#include "ComuDatos.h"
#include "Index.h"
#include "base64.h"
#include <fstream>
#include <sstream>

using namespace std;

int main ( int argc, char *argv[] ){
	ComuDatos comMetadata(argv);
	ComuDatos comFisica;
	
	cout<<argv[6]<<endl;
         
        


	stringstream ss;
	base64 b64;
	cout<<"inicializando capa indice"<<endl;
//	ComuDatos misComu(argv);
	int cont;	
	while((comMetadata.parametro(cont) != FIN_PARAMETROS) and (cont < 100))
		{
			cout << "parámetros proceso2 "  << comMetadata.parametro(cont) << " - "<< cont << endl;
			cont++;
		}

cout<< "Cant Param" <<cont<<endl;//cout de los param//
//	if (arg<2)
//	   return 1;
	

	 if (strcmp(comMetadata.parametro(1).c_str(),"CTLF")==0)
	{
		string nombre=comMetadata.parametro(2).c_str();
		string slong=comMetadata.parametro(3).c_str();
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./cfisica");//CAMBIAR
		comFisica.agregarParametro("creartablaRF",1);
		comFisica.agregarParametro(comMetadata.parametro(2).c_str(),2);
		comFisica.agregarParametro(comMetadata.parametro(3).c_str(),3);
		comFisica.lanzar();
	        comFisica.escribir("");	
		comFisica.liberarRecursos();

	}

	 if (strcmp(comMetadata.parametro(1).c_str(),"CTLV")==0)
	{
		
		string nombre=comMetadata.parametro(2).c_str();
		string slong=comMetadata.parametro(3).c_str();
		//int longitud=atoi(slong.c_str());
		
                comMetadata.liberarRecursos();

		comFisica.ejecutable("./cfisica");//CAMBIAR
		comFisica.agregarParametro("creartablaRVB",1);
		comFisica.agregarParametro(nombre.c_str(),2);
		comFisica.agregarParametro(slong.c_str(),3);
                
		comFisica.lanzar();
		cout<<"entro a clv"<<endl;
	       // comFisica.escribir("");	
	//	comFisica.liberarRecursos();

	}
	
 	if (strcmp(comMetadata.parametro(1).c_str(),"IRLF")==0)
	{
		string nombre=comMetadata.parametro(2).c_str();
		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("nada",0);
		comFisica.agregarParametro("agregarRegistroRF",1);
		comFisica.agregarParametro(comMetadata.parametro(2).c_str(),2);
		
		//int tamanio=atoi(comMetadata.parametro(3).c_str());
		comFisica.lanzar();
		 std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(comMetadata.parametro(3).c_str()),12);
		comFisica.escribir(encoded);
		
			
		ss<< comFisica.leer(100).c_str();
		long pos;
		ss>>pos;

		comFisica.liberarRecursos();
		
		
		 std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(comMetadata.parametro(5).c_str(),"INTEGER")==0) Type=INTEGER;	
		if(strcmp(comMetadata.parametro(5).c_str(),"REAL")==0) Type=REAL;
		if(strcmp(comMetadata.parametro(5).c_str(),"DATE")==0) Type=DATE;
		if(strcmp(comMetadata.parametro(5).c_str(),"STRING")==0) Type=STRING;
		if(strcmp(comMetadata.parametro(5).c_str(),"CHAR")==0) Type=CHAR;
		if(strcmp(comMetadata.parametro(5).c_str(),"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(comMetadata.parametro(5).c_str(),"SHORT")==0) Type=SHORT;
		if(strcmp(comMetadata.parametro(5).c_str(),"LONG")==0) Type=LONG;
	
		
		string str=string(comMetadata.parametro(6).c_str());	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(comMetadata.parametro(2).c_str(), comMetadata.parametro(4).c_str());
		
		ref ref;
		ref.posReg=pos;
		I.PutRef(Vf,ref);

		

	}

	if (strcmp(comMetadata.parametro(1).c_str(),"IRLV")==0)
	{
		string nombre=comMetadata.parametro(2).c_str();
		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("",0);
		comFisica.agregarParametro("agregarRegistroRVB",1);
		comFisica.agregarParametro(comMetadata.parametro(2).c_str(),2);
		comFisica.agregarParametro(12,3);
		
		//int tamanio=atoi(comMetadata.parametro(3).c_str());
		comFisica.lanzar();
		 std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(comMetadata.parametro(3).c_str()),12);
		comFisica.escribir(encoded);
		
		ref ref;	
		string salida=b64.base64_decode(comFisica.leer(100));
		ss<< salida;
		
		ss>>ref.posBloq;
		ss>>ref.posReg;
		comFisica.liberarRecursos();
	

		
		
		 std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(comMetadata.parametro(5).c_str(),"INTEGER")==0) Type=INTEGER;	
		if(strcmp(comMetadata.parametro(5).c_str(),"REAL")==0) Type=REAL;
		if(strcmp(comMetadata.parametro(5).c_str(),"DATE")==0) Type=DATE;
		if(strcmp(comMetadata.parametro(5).c_str(),"STRING")==0) Type=STRING;
		if(strcmp(comMetadata.parametro(5).c_str(),"CHAR")==0) Type=CHAR;
		if(strcmp(comMetadata.parametro(5).c_str(),"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(comMetadata.parametro(5).c_str(),"SHORT")==0) Type=SHORT;
		if(strcmp(comMetadata.parametro(5).c_str(),"LONG")==0) Type=LONG;
	
		
		string str=string(comMetadata.parametro(6).c_str());	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(comMetadata.parametro(2).c_str(), comMetadata.parametro(4).c_str());
				
		I.PutRef(Vf,ref);

		

	}

	if (strcmp(comMetadata.parametro(1).c_str(),"GRLF")==0)
	{
		string nombre=comMetadata.parametro(2).c_str();

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(comMetadata.parametro(4).c_str(),"INTEGER")==0) Type=INTEGER;	
		if(strcmp(comMetadata.parametro(4).c_str(),"REAL")==0) Type=REAL;
		if(strcmp(comMetadata.parametro(4).c_str(),"DATE")==0) Type=DATE;
		if(strcmp(comMetadata.parametro(4).c_str(),"STRING")==0) Type=STRING;
		if(strcmp(comMetadata.parametro(4).c_str(),"CHAR")==0) Type=CHAR;
		if(strcmp(comMetadata.parametro(4).c_str(),"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(comMetadata.parametro(4).c_str(),"SHORT")==0) Type=SHORT;
		if(strcmp(comMetadata.parametro(4).c_str(),"LONG")==0) Type=LONG;
	
		
		string str=string(comMetadata.parametro(5).c_str());	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(comMetadata.parametro(2).c_str(), comMetadata.parametro(3).c_str());
		
		Refs * ref = I.GetRef(Vf);

		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("nada",0);
		comFisica.agregarParametro("devolverRegistroRF",1);
		comFisica.agregarParametro(comMetadata.parametro(2).c_str(),2);
		comFisica.agregarParametro((*ref).vRefs.at(0).posReg,3);
		
		
		comFisica.lanzar();
				
	//	base64 b64;
		//std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(buffer),12);
		
		string salida=b64.base64_decode(comFisica.leer(100));
		cout <<salida<<endl;

		//comFisica.escribir("");
		//cout<<"pos "<<comFisica.leer(100);	
		comFisica.liberarRecursos();

	}

	if (strcmp(comMetadata.parametro(1).c_str(),"GRLV")==0)
	{
		string nombre=comMetadata.parametro(2).c_str();

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(comMetadata.parametro(4).c_str(),"INTEGER")==0) Type=INTEGER;	
		if(strcmp(comMetadata.parametro(4).c_str(),"REAL")==0) Type=REAL;
		if(strcmp(comMetadata.parametro(4).c_str(),"DATE")==0) Type=DATE;
		if(strcmp(comMetadata.parametro(4).c_str(),"STRING")==0) Type=STRING;
		if(strcmp(comMetadata.parametro(4).c_str(),"CHAR")==0) Type=CHAR;
		if(strcmp(comMetadata.parametro(4).c_str(),"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(comMetadata.parametro(4).c_str(),"SHORT")==0) Type=SHORT;
		if(strcmp(comMetadata.parametro(4).c_str(),"LONG")==0) Type=LONG;
	
		
		string str=string(comMetadata.parametro(5).c_str());	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(comMetadata.parametro(2).c_str(), comMetadata.parametro(3).c_str());
		
		Refs * ref = I.GetRef(Vf);

		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("nada",0);
		comFisica.agregarParametro("devolverRegistroRVB",1);
		comFisica.agregarParametro(comMetadata.parametro(2).c_str(),2);
		comFisica.agregarParametro((*ref).vRefs.at(0).posBloq,3);
		comFisica.agregarParametro((*ref).vRefs.at(0).posReg,4);
		
		
		comFisica.lanzar();
				
	//	base64 b64;
		//std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(buffer),12);
		
		string salida=b64.base64_decode(comFisica.leer(100));
		 cout<<endl;
		cout <<salida<<endl;

		//comFisica.escribir("");
		//cout<<"pos "<<comFisica.leer(100);	
		comFisica.liberarRecursos();

	}

	if (strcmp(comMetadata.parametro(1).c_str(),"MRLF")==0)
	{
		string nombre=comMetadata.parametro(2).c_str();

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(comMetadata.parametro(5).c_str(),"INTEGER")==0) Type=INTEGER;	
		if(strcmp(comMetadata.parametro(5).c_str(),"REAL")==0) Type=REAL;
		if(strcmp(comMetadata.parametro(5).c_str(),"DATE")==0) Type=DATE;
		if(strcmp(comMetadata.parametro(5).c_str(),"STRING")==0) Type=STRING;
		if(strcmp(comMetadata.parametro(5).c_str(),"CHAR")==0) Type=CHAR;
		if(strcmp(comMetadata.parametro(5).c_str(),"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(comMetadata.parametro(5).c_str(),"SHORT")==0) Type=SHORT;
		if(strcmp(comMetadata.parametro(5).c_str(),"LONG")==0) Type=LONG;
	
		
		string str=string(comMetadata.parametro(6).c_str());	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(comMetadata.parametro(2).c_str(), comMetadata.parametro(4).c_str());
		
		Refs * ref = I.GetRef(Vf);

		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("",0);
		comFisica.agregarParametro("modificarRegistroRF",1);
		comFisica.agregarParametro(comMetadata.parametro(2).c_str(),2);
		comFisica.agregarParametro((*ref).vRefs.at(0).posReg,3);

		
		comFisica.lanzar();
				
	//	base64 b64;
		//std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(buffer),12);
		
		 std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(comMetadata.parametro(3).c_str()),12);
		comFisica.escribir(encoded);
		
		//cout<<"pos "<<comFisica.leer(100);	
		comFisica.liberarRecursos();

	}

	if (strcmp(comMetadata.parametro(1).c_str(),"MRLV")==0)
	{
		string nombre=comMetadata.parametro(2).c_str();

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(comMetadata.parametro(5).c_str(),"INTEGER")==0) Type=INTEGER;	
		if(strcmp(comMetadata.parametro(5).c_str(),"REAL")==0) Type=REAL;
		if(strcmp(comMetadata.parametro(5).c_str(),"DATE")==0) Type=DATE;
		if(strcmp(comMetadata.parametro(5).c_str(),"STRING")==0) Type=STRING;
		if(strcmp(comMetadata.parametro(5).c_str(),"CHAR")==0) Type=CHAR;
		if(strcmp(comMetadata.parametro(5).c_str(),"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(comMetadata.parametro(5).c_str(),"SHORT")==0) Type=SHORT;
		if(strcmp(comMetadata.parametro(5).c_str(),"LONG")==0) Type=LONG;
	
		
		string str=string(comMetadata.parametro(6).c_str());	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(comMetadata.parametro(2).c_str(), comMetadata.parametro(4).c_str());
		
		Refs * ref = I.GetRef(Vf);

		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("",0);
		comFisica.agregarParametro("modificarRegistroRVB",1);
		comFisica.agregarParametro(comMetadata.parametro(2).c_str(),2);
		comFisica.agregarParametro(30,3);
		comFisica.agregarParametro((*ref).vRefs.at(0).posBloq,4);
		comFisica.agregarParametro((*ref).vRefs.at(0).posReg,5);
		
		
		
		comFisica.lanzar();
				
	//	base64 b64;
		//std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(buffer),12);
		
		 std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(comMetadata.parametro(3).c_str()),12);
		comFisica.escribir(encoded);
		
		//cout<<"pos "<<comFisica.leer(100);	
		comFisica.liberarRecursos();

	}

	if (strcmp(comMetadata.parametro(1).c_str(),"ERLF")==0)
	{
		string nombre=comMetadata.parametro(2).c_str();

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(comMetadata.parametro(4).c_str(),"INTEGER")==0) Type=INTEGER;	
		if(strcmp(comMetadata.parametro(4).c_str(),"REAL")==0) Type=REAL;
		if(strcmp(comMetadata.parametro(4).c_str(),"DATE")==0) Type=DATE;
		if(strcmp(comMetadata.parametro(4).c_str(),"STRING")==0) Type=STRING;
		if(strcmp(comMetadata.parametro(4).c_str(),"CHAR")==0) Type=CHAR;
		if(strcmp(comMetadata.parametro(4).c_str(),"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(comMetadata.parametro(4).c_str(),"SHORT")==0) Type=SHORT;
		if(strcmp(comMetadata.parametro(4).c_str(),"LONG")==0) Type=LONG;
	
		
		string str=string(comMetadata.parametro(5).c_str());	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(comMetadata.parametro(2).c_str(), comMetadata.parametro(3).c_str());
		
		Refs * ref = I.GetRef(Vf);

		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("",0);
		comFisica.agregarParametro("eliminarRegistroRF",1);
		comFisica.agregarParametro(comMetadata.parametro(2).c_str(),2);
		comFisica.agregarParametro((*ref).vRefs.at(0).posReg,3);

		
		comFisica.lanzar();
			
		I.DelRef(Vf);	

		comFisica.liberarRecursos();

	}
	
	if (strcmp(comMetadata.parametro(1).c_str(),"ERLV")==0)
	{
		string nombre=comMetadata.parametro(2).c_str();

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(comMetadata.parametro(4).c_str(),"INTEGER")==0) Type=INTEGER;	
		if(strcmp(comMetadata.parametro(4).c_str(),"REAL")==0) Type=REAL;
		if(strcmp(comMetadata.parametro(4).c_str(),"DATE")==0) Type=DATE;
		if(strcmp(comMetadata.parametro(4).c_str(),"STRING")==0) Type=STRING;
		if(strcmp(comMetadata.parametro(4).c_str(),"CHAR")==0) Type=CHAR;
		if(strcmp(comMetadata.parametro(4).c_str(),"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(comMetadata.parametro(4).c_str(),"SHORT")==0) Type=SHORT;
		if(strcmp(comMetadata.parametro(4).c_str(),"LONG")==0) Type=LONG;
	
		
		string str=string(comMetadata.parametro(5).c_str());	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(comMetadata.parametro(2).c_str(), comMetadata.parametro(3).c_str());
		
		Refs * ref = I.GetRef(Vf);

		
		//int longitud=atoi(slong.c_str());
		
	
		I.DelRef(Vf);		

		

	}

	if (strcmp(comMetadata.parametro(1).c_str(),"CI")==0)
	{
		string nombre=comMetadata.parametro(2).c_str();
		
		index_t indextype;
		tindex_t tindextype;
		
	
		if(strcmp(comMetadata.parametro(4).c_str(),"HASH")==0) indextype=HASH;	
		if(strcmp(comMetadata.parametro(4).c_str(),"BPTREE")==0) indextype=BPTREE;
		
		if(strcmp(comMetadata.parametro(5).c_str(),"ROMANO")==0) tindextype=ROMANO;
		if(strcmp(comMetadata.parametro(5).c_str(),"GRIEGO")==0) tindextype=GRIEGO;
		

		Index I= Index(comMetadata.parametro(2).c_str(), comMetadata.parametro(3).c_str(),indextype,tindextype);
		
	


	}
	//comMetadata.leer(100);
    return 0;
}

*/