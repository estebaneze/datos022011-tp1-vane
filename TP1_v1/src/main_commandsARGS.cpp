/**************************************************************************
             MAIN
 ***************************************************************************/
#include <iostream>

//#include "HashExtensible.h"
#include "ComuDatos.h"

#include "TableIndex.h"
#include "base64.h"
#include <fstream>
#include <sstream>

using namespace std;


std::vector<std::string> Split(std::string str, char c)
{
	std::vector<std::string> vOut;
	
	std::string auxStr;
	
	for ( int i=0; i<str.size(); i++)
	{
		if(str.at(i)==c)
		{
			vOut.push_back(auxStr);
			auxStr.clear();	
		}
		else
		{
			auxStr = auxStr + str.at(i);
		}	

	}
	vOut.push_back(auxStr);
	return vOut;
}

int main2 ( int argc, char *argv[] ){
	ComuDatos comFisica(argv);
	
	stringstream ss;
	base64 b64;
	

	if (argc>1)
	{
	 if (strcmp(argv[1],"CTLF")==0)
	{
		string nombre=argv[2];
		string slong(argv[3]);
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./cfisica");//CAMBIAR
		comFisica.agregarParametro("creartablaRF",1);
		comFisica.agregarParametro(argv[2],2);
		comFisica.agregarParametro(argv[3],3);
		comFisica.lanzar();
	        comFisica.escribir("");	
		comFisica.liberarRecursos();
	
                TableIndex tableIndex=TableIndex(nombre);

	}

	 if (strcmp(argv[1],"CTLV")==0)
	{
		cout<<"entro a clv"<<endl;
		string nombre=argv[2];
		string slong(argv[3]);
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./cfisica");//CAMBIAR
		comFisica.agregarParametro("creartablaRVB",1);
		comFisica.agregarParametro(argv[2],2);
		comFisica.agregarParametro(argv[3],3);
		comFisica.lanzar();
	    //    comFisica.escribir("");	
		comFisica.liberarRecursos();
		 TableIndex tableIndex=TableIndex(nombre);

	}
	
 	if (strcmp(argv[1],"IRLF")==0)
	{
		string nombre=argv[2];
		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("nada",0);
		comFisica.agregarParametro("agregarRegistroRF",1);
		comFisica.agregarParametro(nombre,2);
		
		//int tamanio=atoi(argv[3]);
		comFisica.lanzar();
		 std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(argv[3]),12);
		comFisica.escribir(encoded);
		
			
		ss<< comFisica.leer(100).c_str();
		long pos;
		ss>>pos;

		comFisica.liberarRecursos();
		
		
		 std::vector<Field> Vf;
		std::vector<Field> VfPrimary;
		
		TableIndex tableIndex= TableIndex(argv[2]);

		for (int j=4; j<argc;j++)
		{
			type_t Type;				
			
			vector<string> vValoresCampos= Split(argv[j],',');
			
			Index I = tableIndex.getIndices().at(j-4);
			
			std::vector<std::pair<std::string,type_t> >  auxFields = I.getFields();
			
			if (auxFields.size()!=vValoresCampos.size())
			{
				cout<<"Error de comandos"<<endl;
				return 1;
			}	
			
	
	
			for ( int i=0;i<vValoresCampos.size();i++)
			{
				type_t t;
				
				stringstream ss(vValoresCampos.at(i));
				
				Field F= Field();
				
				switch(auxFields.at(i).second)
				{
					case INTEGER:
							int auxInt;
							ss>>auxInt;
							F= Field(auxInt);
							break;
					case REAL:
							float auxFloat;
							ss>>auxFloat;
							F= Field(auxFloat);
							break;
					case DATE:
							F= Field(DATE,vValoresCampos.at(i));
							break;
					case STRING:
							F= Field(STRING,vValoresCampos.at(i));
							break;
					case BOOLEAN:
							bool auxBool;
							ss>>auxBool;
							F= Field(auxBool);
							break;
					case SHORT:
							short auxShort;
							ss>>auxShort;
							F= Field(auxShort);
							break;	
					case LONG:
							long auxLong;
							ss>>auxLong;
							F= Field(auxLong);
							break;	
				
				}
				Vf.push_back(F);
		
			}
			
			
			if(j==4)
			{
				ref aref;
				aref.posReg=pos;
				I.PutRef(Vf,aref);
				VfPrimary=Vf;
			}
			else
			{
				ref aref;
				aref.Key=VfPrimary.at(0);
				I.PutRef(Vf,aref);
			}
		}

	}

	if (strcmp(argv[1],"IRLV")==0)
	{
		string nombre=argv[2];
		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("",0);
		comFisica.agregarParametro("agregarRegistroRVB",1);
		comFisica.agregarParametro(argv[2],2);
		comFisica.agregarParametro(12,3);
		
		//int tamanio=atoi(argv[3]);
		comFisica.lanzar();
		 std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(argv[3]),12);
		comFisica.escribir(encoded);
		
		int posB;
		int posR;
		string salida=b64.base64_decode(comFisica.leer(100));
		ss<< salida;
		
		ss>>posB;
		ss>>posR;
		comFisica.liberarRecursos();
	

		
		
		  std::vector<Field> Vf;
		std::vector<Field> VfPrimary;
		
		TableIndex tableIndex= TableIndex(argv[2]);

		for (int j=4; j<argc;j++)
		{
			type_t Type;				
			
			vector<string> vValoresCampos= Split(argv[j],',');
			
			Index I = tableIndex.getIndices().at(j-4);
			
			std::vector<std::pair<std::string,type_t> >  auxFields = I.getFields();
			
			if (auxFields.size()!=vValoresCampos.size())
			{
				cout<<"Error de comandos"<<endl;
				return 1;
			}	
			
	
	
			for ( int i=0;i<vValoresCampos.size();i++)
			{
				type_t t;
				
				stringstream ss(vValoresCampos.at(i));
				
				Field F= Field();
				
				switch(auxFields.at(i).second)
				{
					case INTEGER:
							int auxInt;
							ss>>auxInt;
							F= Field(auxInt);
							break;
					case REAL:
							float auxFloat;
							ss>>auxFloat;
							F= Field(auxFloat);
							break;
					case DATE:
							F= Field(DATE,vValoresCampos.at(i));
							break;
					case STRING:
							F= Field(STRING,vValoresCampos.at(i));
							break;
					case BOOLEAN:
							bool auxBool;
							ss>>auxBool;
							F= Field(auxBool);
							break;
					case SHORT:
							short auxShort;
							ss>>auxShort;
							F= Field(auxShort);
							break;	
					case LONG:
							long auxLong;
							ss>>auxLong;
							F= Field(auxLong);
							break;	
				
				}
				Vf.push_back(F);
		
			}
			
			
			if(j==4)
			{
				ref aref;
				aref.posReg=posR;
				aref.posBloq=posB;
				I.PutRef(Vf,aref);
				VfPrimary=Vf;
			}
			else
			{
				ref aref;
				aref.Key=VfPrimary.at(0);
				I.PutRef(Vf,aref);
			}
		}

	}

	if (strcmp(argv[1],"GRLF")==0)
	{
		string nombre=argv[2];

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(argv[4],"INTEGER")==0) Type=INTEGER;	
		if(strcmp(argv[4],"REAL")==0) Type=REAL;
		if(strcmp(argv[4],"DATE")==0) Type=DATE;
		if(strcmp(argv[4],"STRING")==0) Type=STRING;
		if(strcmp(argv[4],"CHAR")==0) Type=CHAR;
		if(strcmp(argv[4],"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(argv[4],"SHORT")==0) Type=SHORT;
		if(strcmp(argv[4],"LONG")==0) Type=LONG;
	
		
		string str=string(argv[5]);	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(argv[2], argv[3]);
		
		Refs  ref = Refs();
        
        int ret = I.GetRef(Vf,ref);

		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("nada",0);
		comFisica.agregarParametro("devolverRegistroRF",1);
		comFisica.agregarParametro(argv[2],2);
		comFisica.agregarParametro((ref).vRefs.at(0).posReg,3);
		
		
		comFisica.lanzar();
				
	//	base64 b64;
		//std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(buffer),12);
		
		string salida=b64.base64_decode(comFisica.leer(100));
		cout <<salida<<endl;

		//comFisica.escribir("");
		//cout<<"pos "<<comFisica.leer(100);	
		comFisica.liberarRecursos();

	}

	if (strcmp(argv[1],"GRLV")==0)
	{
		string nombre=argv[2];

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(argv[4],"INTEGER")==0) Type=INTEGER;	
		if(strcmp(argv[4],"REAL")==0) Type=REAL;
		if(strcmp(argv[4],"DATE")==0) Type=DATE;
		if(strcmp(argv[4],"STRING")==0) Type=STRING;
		if(strcmp(argv[4],"CHAR")==0) Type=CHAR;
		if(strcmp(argv[4],"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(argv[4],"SHORT")==0) Type=SHORT;
		if(strcmp(argv[4],"LONG")==0) Type=LONG;
	
		
		string str=string(argv[5]);	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(argv[2], argv[3]);
		
		Refs  ref = Refs();
        
        int ret = I.GetRef(Vf,ref);

		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("nada",0);
		comFisica.agregarParametro("devolverRegistroRVB",1);
		comFisica.agregarParametro(argv[2],2);
		comFisica.agregarParametro((ref).vRefs.at(0).posBloq,3);
		comFisica.agregarParametro((ref).vRefs.at(0).posReg,4);
		
		
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

	if (strcmp(argv[1],"MRLF")==0)
	{
		string nombre=argv[2];

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(argv[5],"INTEGER")==0) Type=INTEGER;	
		if(strcmp(argv[5],"REAL")==0) Type=REAL;
		if(strcmp(argv[5],"DATE")==0) Type=DATE;
		if(strcmp(argv[5],"STRING")==0) Type=STRING;
		if(strcmp(argv[5],"CHAR")==0) Type=CHAR;
		if(strcmp(argv[5],"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(argv[5],"SHORT")==0) Type=SHORT;
		if(strcmp(argv[5],"LONG")==0) Type=LONG;
	
		
		string str=string(argv[6]);	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(argv[2], argv[4]);
		
			Refs  ref = Refs();
        
        int ret = I.GetRef(Vf,ref);

		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("",0);
		comFisica.agregarParametro("modificarRegistroRF",1);
		comFisica.agregarParametro(argv[2],2);
		comFisica.agregarParametro((ref).vRefs.at(0).posReg,3);

		
		comFisica.lanzar();
				
	//	base64 b64;
		//std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(buffer),12);
		
		 std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(argv[3]),12);
		comFisica.escribir(encoded);
		
		//cout<<"pos "<<comFisica.leer(100);	
		comFisica.liberarRecursos();

	}

	if (strcmp(argv[1],"MRLV")==0)
	{
		string nombre=argv[2];

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(argv[5],"INTEGER")==0) Type=INTEGER;	
		if(strcmp(argv[5],"REAL")==0) Type=REAL;
		if(strcmp(argv[5],"DATE")==0) Type=DATE;
		if(strcmp(argv[5],"STRING")==0) Type=STRING;
		if(strcmp(argv[5],"CHAR")==0) Type=CHAR;
		if(strcmp(argv[5],"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(argv[5],"SHORT")==0) Type=SHORT;
		if(strcmp(argv[5],"LONG")==0) Type=LONG;
	
		
		string str=string(argv[6]);	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(argv[2], argv[4]);
		
		Refs  ref = Refs();
        
        int ret = I.GetRef(Vf,ref);

		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("",0);
		comFisica.agregarParametro("modificarRegistroRVB",1);
		comFisica.agregarParametro(argv[2],2);
		comFisica.agregarParametro(30,3);
		comFisica.agregarParametro((ref).vRefs.at(0).posBloq,4);
		comFisica.agregarParametro((ref).vRefs.at(0).posReg,5);
		
		
		
		comFisica.lanzar();
				
	//	base64 b64;
		//std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(buffer),12);
		
		 std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(argv[3]),12);
		comFisica.escribir(encoded);
		
		//cout<<"pos "<<comFisica.leer(100);	
		comFisica.liberarRecursos();

	}

	if (strcmp(argv[1],"ERLF")==0)
	{
		string nombre=argv[2];

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(argv[4],"INTEGER")==0) Type=INTEGER;	
		if(strcmp(argv[4],"REAL")==0) Type=REAL;
		if(strcmp(argv[4],"DATE")==0) Type=DATE;
		if(strcmp(argv[4],"STRING")==0) Type=STRING;
		if(strcmp(argv[4],"CHAR")==0) Type=CHAR;
		if(strcmp(argv[4],"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(argv[4],"SHORT")==0) Type=SHORT;
		if(strcmp(argv[4],"LONG")==0) Type=LONG;
	
		
		string str=string(argv[5]);	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(argv[2], argv[3]);
		
		Refs  ref = Refs();
        
       		 int ret = I.GetRef(Vf,ref);

		
		//int longitud=atoi(slong.c_str());
		comFisica.ejecutable("./tpdatos");//CAMBIAR
		comFisica.agregarParametro("",0);
		comFisica.agregarParametro("eliminarRegistroRF",1);
		comFisica.agregarParametro(argv[2],2);
		comFisica.agregarParametro((ref).vRefs.at(0).posReg,3);

		
		comFisica.lanzar();
			
		I.DelRef(Vf);	

		comFisica.liberarRecursos();

	}
	
	if (strcmp(argv[1],"ERLV")==0)
	{
		string nombre=argv[2];

		std::vector<Field> Vf;

   	      	 type_t Type;
	
		if(strcmp(argv[4],"INTEGER")==0) Type=INTEGER;	
		if(strcmp(argv[4],"REAL")==0) Type=REAL;
		if(strcmp(argv[4],"DATE")==0) Type=DATE;
		if(strcmp(argv[4],"STRING")==0) Type=STRING;
		if(strcmp(argv[4],"CHAR")==0) Type=CHAR;
		if(strcmp(argv[4],"BOOLEAN")==0) Type=BOOLEAN;
		if(strcmp(argv[4],"SHORT")==0) Type=SHORT;
		if(strcmp(argv[4],"LONG")==0) Type=LONG;
	
		
		string str=string(argv[5]);	
		
	
		Field F= Field(Type,str);
		Vf.push_back(F);
	
		Index I= Index(argv[2], argv[3]);
		
			Refs  ref = Refs();
        
       		int ret = I.GetRef(Vf,ref);

		
		//int longitud=atoi(slong.c_str());
		
	
		I.DelRef(Vf);		

		

	}

	if (strcmp(argv[1],"CI")==0)
	{
		string nombre=argv[2];
		
		index_t indextype;
		tindex_t tindextype;
		
	
		if(strcmp(argv[5],"HASH")==0) indextype=HASH;	
		if(strcmp(argv[5],"BPTREE")==0) indextype=BPTREE;
		
		if(strcmp(argv[6],"ROMANO")==0) tindextype=ROMANO;
		if(strcmp(argv[6],"GRIEGO")==0) tindextype=GRIEGO;
		
		

		Index I= Index(argv[2], argv[3],indextype,tindextype);
		
		I.Create(atoi(argv[7]));

		vector<string> vCampos= Split(argv[3],',');
		vector<string> vTipoCampos= Split(argv[4],',');
		
		if (vCampos.size()!=vTipoCampos.size())
		{
			cout<<"Error de comandos"<<endl;
			return 1;
		}	
		

		for ( int i=0;i<vCampos.size();i++)
		{
			type_t t;
			
			if(vTipoCampos.at(i)=="INTEGER") t=INTEGER;	
			if(vTipoCampos.at(i)=="REAL") t=REAL;
			if(vTipoCampos.at(i)=="DATE") t=DATE;
			if(vTipoCampos.at(i)=="STRING") t=STRING;
			if(vTipoCampos.at(i)=="CHAR") t=CHAR;
			if(vTipoCampos.at(i)=="BOOLEAN") t=BOOLEAN;
			if(vTipoCampos.at(i)=="SHORT") t=SHORT;
			if(vTipoCampos.at(i)=="LONG") t=LONG;
			
			I.addField(vCampos.at(i),t);
			
		}



		TableIndex tableIndex=TableIndex(nombre);

		tableIndex.insertIndex(I);
		tableIndex.save();

	}
	}
    return 0;
}


