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
  string texto_plano_valido="";

 // completamos con x al final para que sea potencia de 2
   int tam=texto_plano_valido.size();
   if(tam%2!=0)
    texto_plano_valido+=" ";

  return texto_plano_valido;
}



char* RSA::desencriptar(char* m)
{
	return m;

     /*cout<<"\n DESENCRIPTAR :\n\n";
     long int d,n,tam, e;
     //cout<<" Ingrese clave privada (d) :";
     //cin>>d;
     d = 157;
     cout << "Clave privada (d): " << d << endl;
     //cout<<" Ingrese clave n (p*q) :";
     //cin>>n;
     n = 2773;
     cout << "Clave n (p*q) :" << endl;


     cout<<" Ingrese longitud del mensaje cifrado: ";
     cin>>tam;

     long int mensaje_cifrado[tam];
     long int mensaje_int[tam*2];
     string mensaje="";


     cout<<" Mensaje cifrado: \n";
     for(int i=0;i<tam;i++)
     { cout<<"  ["<<i+1<<"] = ";cin>>mensaje_cifrado[i];}
     cout<<endl;

     // elevamos el mensaje a la potencia d (mod n)
      cout<<" mensaje cifrado a la potencia 'd':";
      for(int i=0;i<tam;i++)
          mensaje_cifrado[i]=Exponenciacion_Zn(mensaje_cifrado[i],d,n);

      for(int i=0;i<tam;i++)
          cout<<mensaje_cifrado[i]<<" ";

      cout<<endl;


     // hallamos el mensaje en numeros
     //cout<<" mensaje en numeros: ";
     for(int i=0;i<tam;i++)
       {mensaje_int[i*2]=mensaje_cifrado[i]/100;
        mensaje_int[i*2+1]=mensaje_cifrado[i]%100;
       }
     for(int i=0;i<(tam*2);i++)
         cout<<mensaje_int[i]<<" ";
     cout<<endl;


     // hallamos el mensaje
     cout<<" mensaje : ";
     for(int i = 0 ; i < (tam*2); i++)
       mensaje += GetAlfabeto().at(mensaje_int[i]%26);

     cout<<mensaje;

     return m;
     */
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
void RSA::generarClave(){

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
	    double nromax=0;
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
					 p=(rand()%(int)sqrt(nromax+nromax) + (int)sqrt(nromax/2));  //valor de 2 a raiz(nromax)
				 }while(!es_primo(p));

				 do
				 {
					 q=(int)(rand()%(int)sqrt(nromax*2)+(int)sqrt(nromax/2));
				 }while(!es_primo(q));

				 cout<<" p : "<<p<<"\n q : "<<q;

			} while (p*q>nromax);

			int mayor;
			//encuentro mayor primo y lo achico hasta que p*q<nromax, pero siempre que siga siendo primo
			if (p>q) {
				do {
					 p--;
				} while(!es_primo(p));
			}
			else {
				do {
					   q--;
				} while(!es_primo(q));
			}

			/* 2) Calculamos el valor de n */
				 n = p * q;

	    }while(n>=nromax/2);

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


}

char* RSA::encriptar(char* m){

	//ACA TENGO QUE LEER EL ARCHIVO DE LA CLAVE PUBLICA PARA OBTENER N Y E
    ///////////////////////////////////////////////////

	//ACA TENGO QUE CARGAR EL TAMANIO DE N DE CONFIG.TXT
	int tamanio_n=1;
	int n,e;

    // representamos numericamente el mensaje
	string mensaje;
	mensaje.append((const char*)m);
	//valido el mensaje para que sea potencia de 2
    string mensaje_valido = validar_mensaje(mensaje);
    mensaje.clear();
    mensaje=mensaje_valido;


    string mensaje_int[mensaje.size()]; /*posiciones de los caracteres en el alfabeto del mensaje*/

     //posiciones de los caracteres en el alfabeto del mensaje
     for(unsigned int i = 0; i <mensaje.size(); i++){

    	 int ascii = mensaje.at(i);

    	 string ascii_str = Helper::IntToString(ascii);
    	 if (ascii < 10) ascii_str = "0" + Helper::IntToString(ascii);

    	 mensaje_int[i] = ascii_str;
     }

     cout << " mensaje_int[]: ";
     for(unsigned int i = 0; i < mensaje.size(); i++){
    	 cout << mensaje_int[i] << " ";
     }
     cout << endl;

     //cout<<" mensaje en bloque de tamanio n bytes: ";

     long int mensaje_nros[mensaje.size() / n];
     long int mensaje_cifrado[mensaje.size()/ n];

     //agrupamos de 2 en 2 el mensaje en nros.
     int k = 0;
     int index = 0;
     while(k < mensaje.size()){

		 string msg = "";

		 //si llego al fin del archivo termino
		 if((k+tamanio_n-1) >= mensaje.size())
			 break;

		 int aux=0;
		 string aux_str;
		 aux_str.clear();
		 //concateno la cantidad de caracteres segun el tamanio de n
		 for (unsigned int i=0;i<tamanio_n;i++){

			 aux_str.append(mensaje_int[k+i]);

		 }
		 aux = Helper::StringToInt(aux_str);
		 msg.append(Helper::IntToString(aux));
		 k = k+tamanio_n;


    	 int actualMsg = Helper::StringToInt(msg);
    	 mensaje_nros[index] = actualMsg;
    	 index++;
     }

     cout<<" Mensaje en numeros (formado con posiciones de los caracteres en el alfabeto del mensaje) : " << endl;
     cout << "	";
     for(int i = 0; i < mensaje.size() / n; i++){
    	 cout << mensaje_nros[i] << " ";
     }
     cout << endl;

     //Elevo cada uno a la "d"
     cout << endl << "Mensaje cifrado: ";
     for(int i = 0; i < mensaje.size() / n; i++){

    	 int numExceso=0;
    	 if (tamanio_n==1){

    		 if (mensaje_nros[i]>127) numExceso=128;
    	 }

    	 if (tamanio_n==2){

    	    		 if (mensaje_nros[i]>32767) numExceso=32768;
    	    	 }

    	 if (tamanio_n==4){

    	    		 if (mensaje_nros[i]>2147483647) numExceso=2147483648;
    	    	 }


    	 mensaje_cifrado[i] = Exponenciacion_Zn(mensaje_nros[i]-numExceso, e, n)+numExceso;
    	 cout << mensaje_cifrado[i] << " ";
     }
     cout << endl << endl;

     string cifrado;
     for (unsigned int i=0;i<mensaje.size()/n;i++){
    	cifrado.append(Helper::LongToString(mensaje_cifrado[i]));
     }

     return (char*)cifrado.c_str();
}