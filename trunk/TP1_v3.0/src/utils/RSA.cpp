/*
 * RSA.cpp
 *
 *  Created on: 29/11/2011
 *      Author: loo
 */

#include "RSA.h"
#include "ConfigurationMananger.h"
#include "exception"

bool RSA::es_primo(int n)
{
  for(int i=2;i<n;i++)
    if(n%i==0)
     return false;

   return true;
}

int RSA::get_pos(string str,char elemento)
{
  for(unsigned int i=0;i<str.size();i++)
    if(str.at(i)==elemento)
      return i;
   return -1;
}

string  RSA::validar_mensaje(string texto_plano)
{
  string texto_plano_valido = texto_plano;

 // completamos con espacio al final para que sea potencia de 2
   int tam = texto_plano_valido.size();
   if(tam%2!=0)
    texto_plano_valido += " ";

   cout << endl << endl;

  return texto_plano_valido;
}


/*
 * ALGORTIMO DE EUCLIDES: Es un metodo que sirve para hallar el mcd de dos numeros enteros
 * positivos.
 */
int RSA::alg_euc(int a,int b)
{
   int max,min,r;

  // identificamos el mayor y menor de los numeros
   if(a>=b)
   {max=a;min=b;}
   else
   {max=b;min=a;}

   while(min!=0)
   {
    r=max%min;
    max=min;
    min=r;
   }
    return max;
}

/*
 * Alfortimo de euclides extendido
 */
long* RSA::alg_euc_ext(int n1,int n2) // n1 es a y n2 es b
{
   long array[3],x=0,y=0,d=0,x2 = 1,x1 = 0,y2 = 0,y1 = 1,q = 0, r = 0;
  if(n2==0)
  {
  array[0]=n1;
  array[1]=1;
  array[2]=0;
  }
  else
  {
   while(n2>0)
      {
     q = (n1/n2);
      r = n1 - q*n2;
      x = x2-q*x1;
      y = y2 - q*y1;
      n1 = n2;
      n2 = r;
      x2 = x1;
      x1 = x;
      y2 = y1;
      y1 = y;
      }
      array[0] = n1;   // mcd (n1,n2)
      array[1] = x2;   // x
      array[2] = y2;   // y
    }
    return array;
}


long RSA::Inverso_Zn(int a,int n)
{
  long* ptr,array[3];
  ptr=alg_euc_ext(n,a);

  array[0]=*ptr;
  array[1]=*(ptr+1);
  array[2]=*(ptr+2);

  if(array[0]!=1)
  return -1;
  else
  {
  if(array[2]<0)
   array[2]+=n;
   return array[2];
  }
}


unsigned long long  RSA::Exponenciacion_Zn(unsigned long long  a,unsigned long long  k,unsigned long long  n)
{
  // convertimos "k" a binario
   unsigned long long numero=k;

  unsigned long long bin[300];
  unsigned long long  ind=0;
  while(numero>=2)
  {
   bin[ind++]=numero%2;
   numero/=2;
  }
  bin[ind]=numero;
  unsigned long long  tam=ind+1;
 // for(int i=0;i<tam;i++)
 // cout<<bin[i]<<endl;
  /////////////////////////////

  unsigned long long  b=1;
  if(k==0)
     return b;

  unsigned long long  A=a;
  for(int i=(tam-1);i>=0;i--)
  {
    b=(b*b)%n;
    if(bin[i]==1)
    b=(A*b)%n;
   // cout<<"b :"<<b<<endl;
  }

return b;
}


void RSA::validarTamClave(){

	int tam = ConfigurationMananger::getInstance()->getTamClaveRSA();
	bool valido = tam == 1 || tam == 2 || tam== 4;	//TODO: VER QUE HACEMOS CON 8 BYTES || tam!= 8

	if(!valido){
		BadRSAKeySizeException* ex = new BadRSAKeySizeException();
		cout << ex->what() << endl;
		throw ex;
	}
}

/*string RSA::GetAlfabeto(){
	return "abcdefghijklmnopqrstuvwxyz0123456789_";
}*/

void RSA::CheckCache(){

	//Claves::GetClavePublicaN()

}

void RSA::generarClave(){

	//VALIDO QUE NO ESTEN CREADAS CLAVES
	string fileNameClavePrivada = ConfigurationMananger::getInstance()->getClavePrivadaFile();
	string fileNameClavePublica = ConfigurationMananger::getInstance()->getClavePublicaFile();
	if(Archivo::exists(fileNameClavePrivada) && Archivo::exists(fileNameClavePublica)){
		return;
	}

	//Antes de empezar valida que el tamaño parametrizado sea correcto
    RSA::validarTamClave();

	long int p,q,n,fi,e,d,tamanio_n;

	//VANE:
	//aca tenes que cargar el tamanio de n desde el config.txt
	tamanio_n = ConfigurationMananger::getInstance()->getTamClaveRSA();

	/* 1) Generamos aleatoriamente dos enteros p y q (p y q pueden ser cualquier numero
	 pero deben de ser del mismo tamaño) ,
	 ademas deben de ser primos */

	//obtengo numero maximo que puede valer n segun el tamanio de n leido del config.txt
	unsigned int nromax=0;
	if (tamanio_n==1) nromax=256;
	if (tamanio_n==2) nromax=65536;
	if (tamanio_n==4) nromax=4294967296;

	//mientras n tengo un valor menor al permitido repito
	do{

	//obtengo nuemros primos tratando de obtener el p y q maximo posibles
	//la idea es generar p y q hasta pasarme del maximo valor de n
	//luego al primo mas grande lo resto hasta que cumpla que p*q<nromax


	//genero p y q
	do{
		do
		{
			 p=(rand()%(int)(nromax/4) + (int)(nromax/3));  //valor de 2 a raiz(nromax)
		 }while(!es_primo(p));

		 do
		 {
			 q=(int)(rand()%(int)(nromax/2)+(int)nromax/3);
		 }while(!es_primo(q));

		 cout<<" p : "<<p<<" q : "<<q << endl;

	} while (p*q<nromax);

	cout<<"elegidos: p : "<<p<<" q : "<<q << endl;
	//encuentro mayor primo y lo achico hasta que p*q<nromax, pero siempre que siga siendo primo

	do {
		if (p>q) {
			do {
				 p--;
				 cout << "p: " << p << endl;
			} while(!es_primo(p) /*&& (p*q)<nromax*/ );
		}
		else {
			do {
				   q--;
				   cout << "q: " << q << endl;
			} while(!es_primo(q)/* && (p*q)<nromax*/);
		}

		/* 2) Calculamos el valor de n */
			 n = p * q;
	} while (n>nromax);

	}while(n<=nromax/2);

	cout<<"\n n : "<<n;

	/* 3) Calculamos el valor de fi */
	 fi=(p-1)*(q-1);
	 cout<<"\n fi : "<<fi;

	/* 4) Seleccionamos aleatoriamente un entero 'e' tal que mcd(e,fi)=1 y 1 < e < fi */
	do{
	   e = rand() % (fi-2)+2;
	}while(alg_euc(e,fi)!=1);

	//   e = 17;
	cout<<"\n e : "<<e;

	/* 5) Usar el algoritmo de euclides extendido para hallar un entero 'd' tal que
	   ed = 1 (mod fi) donde 1 < d < fi (en otras palabras, hallar el inverso de 'e') */
	d = Inverso_Zn(e,fi);
	cout<<"\n d : "<<d;

	/*  6) La clave publica es (n,e) y la clave privada es d */

	/*******************/
	//VANE ACA TENES QUE GUARDAR LAS CLAVES EN ARCHIVOS.
	/**********************/
	cout<<"\n\n clave publica : ("<< n <<" , "<< e <<")";
	cout<<"\n clave privada : ("<< n <<" , "<< d << endl << endl;

	Claves::GuardarClaves(n,e,d);


}

char* RSA::encriptar(char* m){

	//return m;

	//ACA TENGO QUE LEER EL ARCHIVO DE LA CLAVE PUBLICA PARA OBTENER N Y E
    ///////////////////////////////////////////////////
	long int e = Claves::GetClavePublicaE();
	long int n = Claves::GetClavePublicaN();
	int tamanio_n = ConfigurationMananger::getInstance()->getTamClaveRSA();
    // representamos numericamente el mensaje
	string mensaje;
	mensaje.append((const char*)m);
	cout << "\n---------tamnio n: " << tamanio_n << " n: " << n << "  e: " << e << endl;

	//valido el mensaje para que sea potencia de 2
    string mensaje_valido = validar_mensaje((string)mensaje);
    mensaje.clear();
    mensaje=mensaje_valido;

    //string mensaje_int;//[mensaje.size()]; /*posiciones de los caracteres en el alfabeto del mensaje*/
	string mensaje_int[mensaje.size()];
	int cantBloques;
    if(tamanio_n == 1)
        cantBloques = (mensaje.size() / 1);
    else if(tamanio_n == 2)
    	cantBloques = (mensaje.size() / 2);
    else if(tamanio_n == 4)
    	cantBloques = (mensaje.size() / 4);


	 long int mensaje_nros[cantBloques];
     long int mensaje_cifrado[cantBloques];
     long int mensaje_cifrado_salida[mensaje.size()];

     //posiciones de los caracteres en el alfabeto del mensaje
     for(unsigned int i = 0; i < mensaje.size(); i++){


    	 if (tamanio_n==1) mensaje_nros[i]= mensaje.at(i);

    	 if (tamanio_n==2){
    		// cout <<(int) mensaje.at(i)<<" ";
    		 //cout <<(int) mensaje.at(i+1)<<" ";
    		 mensaje_nros[i/2]= mensaje.at(i)*256+mensaje.at(i+1);
    		 i++;
    	 }

    	 if (tamanio_n==4){
    		 mensaje_nros[i/4]= mensaje.at(i) *  pow(16,6) + mensaje.at(i+1) * pow(16,4) + mensaje.at(i+2) * pow(16,2) + mensaje.at(i+3);
    		 i = i+3;
    	 }

     }
     for(int i = 0; i < cantBloques; i++){
    	 //cout << mensaje_nros[i] << " ";
     }
     cout << endl;

     for(unsigned int i = 0; i < mensaje.size()/tamanio_n; i++){

    	 int numExceso=0;
    	 if (tamanio_n==1){
    		 if (mensaje_nros[i] > 127) numExceso=128;
    	 }

    	 if (tamanio_n==2){
    	    if (mensaje_nros[i] > 59999) numExceso=60000;
    	 }

    	 if (tamanio_n==4){
    	   	if (mensaje_nros[i] > 2147483647) numExceso = 2147483648;
    	 }

    	 //p ej, si es n de 1 byte, al nro le resto 128 y asi anulo el 8vo bit (queda en 0).
    	 //lo mismo si es de 2 o bytes, con 65535 y 4294967295 respectivamente
    	 int numSinExceso = mensaje_nros[i]-numExceso;


    	 mensaje_cifrado[i] = Exponenciacion_Zn(mensaje_nros[i]-numExceso, e, n) + numExceso;
//    	 cout << "numSinExceso: " << numSinExceso <<" cifrado: " <<mensaje_cifrado[i] << " "<<endl;

     }

     for (unsigned int i = 0; i < cantBloques;i++){

    	 if (tamanio_n==1){
			 mensaje_cifrado_salida[i]=mensaje_cifrado[i];
    	 }

    	 if (tamanio_n==2){
    		 int primerValor=0;
    		 int segundoValor=0;
    		 primerValor = mensaje_cifrado[i]/256;
    		 segundoValor = mensaje_cifrado[i] - primerValor * 256;
    		 mensaje_cifrado_salida[2*i]=primerValor;
    		 mensaje_cifrado_salida[2*i+1]=segundoValor;
    	}

    	 //HACER TAMAÑO 4
    	 //if (tamanio_n==4)

     }

    //Convierto mi vector de salida a string
     string cifrado = "";
     for (unsigned int i = 0; i < mensaje.size();i++){
     	 cifrado.append((char*)Helper::copyBytesToString(mensaje_cifrado_salida[i]).c_str());
     }
  //   cout << "Mensaje cifrado: " << cifrado << " Longitud del mensaje cifrado: "<< cifrado.size()<<endl;

     return (char*)cifrado.c_str();
}


char* RSA::desencriptar(string m)
{
        long int d = Claves::GetClavePrivadaD();
        long int n = Claves::GetClavePrivadaN();
        int tamanio_n = ConfigurationMananger::getInstance()->getTamClaveRSA();
        int cantBloques = 0;

        //imprimo el mensaje a encriptar
        cout << "\n---------tamnio n: " << tamanio_n << " n: " << n << "  d: " << d << endl;

        if(tamanio_n == 1)
            cantBloques = (m.size() / 1);
        else if(tamanio_n == 2)
        	cantBloques = (m.size() / 2);
        else if(tamanio_n == 4)
        	cantBloques = (m.size() / 4);

        long int mensaje_nros[cantBloques];
        long int mensaje_cifrado[cantBloques];
        long int mensaje_cifrado_salida[m.size()];

       //convierto mi string a un vector de long int con mi mensaje cifrado
        if (tamanio_n==1){
            for (unsigned int i = 0; i < cantBloques;i++){
//            	cout << mensaje_cifrado[i] << " ";
                 mensaje_cifrado[i] =  Helper::copyBytesToLong((char*)m.substr(i,1).c_str());
              }
        }

        if (tamanio_n==2){
        	int primerValor = 0;
        	int segundoValor = 0;

        	 for (unsigned int i = 0; i < cantBloques;i++){
         		primerValor = Helper::copyBytesToLong((char*)m.substr(2*i,1).c_str());
        		segundoValor =  Helper::copyBytesToLong((char*)m.substr(2*i+1,1).c_str());
				mensaje_cifrado[i] = primerValor * 256 + segundoValor;
             }
        }

         if (tamanio_n==4){
        	 cout << "FALTA IMPLEMENTAR CON N = 4"<<endl;
        }

     //CALCULO EXCESO Y DESCIFRO MENSAJE
     for(unsigned int i = 0; i < cantBloques; i++){

    	 int numExceso=0;
    	 if (tamanio_n==1){
    		 if (mensaje_cifrado[i] > 127) numExceso=128;
    	 }

    	 if (tamanio_n==2){
    	    if (mensaje_cifrado[i] > 59999) numExceso=60000;
    	 }

    	 if (tamanio_n==4){
    	   	if (mensaje_cifrado[i] > 2147483647) numExceso = 2147483648;
    	 }

    	 int numSinExceso = mensaje_cifrado[i] - numExceso;
         mensaje_nros[i] = Exponenciacion_Zn(numSinExceso, d, n) + numExceso;
    }

     //convierto mi vector de long int a un string
     string sincifrar = "";

     int j = 0;
     string mensajeSinCifrar;

     for (unsigned int i = 0; i < cantBloques;i++){
    	 //cout << mensaje_nros[i]<<" ";
         if (tamanio_n==1) {
        	string num=Helper::copyBytesToString(mensaje_nros[i]);
			mensajeSinCifrar.append(num);
         }

         if (tamanio_n==2){
        	 int division = mensaje_nros[i]/256;
        	 string num=Helper::copyBytesToString(division);
        	 mensajeSinCifrar.append((char*)num.c_str());

        	 num =  Helper::copyBytesToString(mensaje_nros[i] - ( division * 256));
        	 mensajeSinCifrar.append(num.c_str());


         }
     }
     //cout <<"Mensaje desencriptado: "<< mensajeSinCifrar<<endl;

     return (char*)mensajeSinCifrar.c_str();
}



