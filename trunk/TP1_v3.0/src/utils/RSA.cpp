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



char* RSA::desencriptar(char* m)
{
        long int d = Claves::GetClavePrivadaD();
        long int n = Claves::GetClavePrivadaN();
        int tamanio_n = ConfigurationMananger::getInstance()->getTamClaveRSA();
        int cantBloques = 0;

        //imprimo el mensaje a encriptar
        cout << "\n---------tamnio n: " << tamanio_n << " n: " << n << "  d: " << d << endl;
        cout << "---------mensaje: " << m <<  endl;

        //Convierto mi mensaje a string
        string mcifrado;
        mcifrado.append((const char*)m);
        cantBloques = mcifrado.size()/(tamanio_n*2);

        long int* mensaje_nros = new long int[cantBloques];
        long int* mensaje_cifrado = new long int[cantBloques];

        string auxsrt;
        //convierto mi string a un vector de long int con mi mensaje cifrado
        cout << "mcifrado"<<mcifrado<<cantBloques<<endl;

        if (tamanio_n==1){
             unsigned int pos = 0;
             for (unsigned int i = 0; i < cantBloques;i++){
                 string aux;
                 aux.clear();
                 for (unsigned int j=0; j<2; j++){
                     aux = aux + mcifrado.at(pos);
                     pos++;
                 }
                 cout << "aux"<< aux;
                 mensaje_cifrado[i] = Helper::StringToLong(aux);
                 cout << "aux"<<  mensaje_cifrado[i];
             }
        }

         if (tamanio_n==2){
             int pos;
             for (unsigned int i = 0; i < cantBloques;i++){
                 string aux;
                 aux.clear();
                 for (unsigned int j=0; j<6; j++){
                     aux = aux + mcifrado.at(j);
                     pos++;
                 }
                 mensaje_cifrado[i] = Helper::StringToLong(aux);
             }
        }

         if (tamanio_n==4){
             int pos=0;
             for (unsigned int i = 0; i < cantBloques;i++){
                 string aux;
                 aux.clear();
                 for (unsigned int j=0; j<12; j++){
                     aux = aux + mcifrado[pos];
                     pos++;
                 }
                 mensaje_cifrado[i] = Helper::StringToLong(aux);
             }
        }
         cout << "hola";
     for (unsigned int i = 0; i < cantBloques;i++){
             cout << " "<< mensaje_cifrado[i]<<"  "<< endl;
     }

     //CALCULO EXCESO Y DESCIFRO MENSAJE
     for(unsigned int i = 0; i < cantBloques; i++){

         int numExceso=0;
         if (tamanio_n==1){
             if (mensaje_cifrado[i]>127) numExceso=128;
         }
         if (tamanio_n==2){
            if (mensaje_cifrado[i]>65535) numExceso=65536;
         }

         if (tamanio_n==4){
               if (mensaje_cifrado[i]>4294967295) numExceso=4294967296;
         }

         int numSinExceso = mensaje_cifrado[i]-numExceso;
         cout << "numSinExceso: " << numSinExceso << endl;
         mensaje_nros[i] = Exponenciacion_Zn(mensaje_cifrado[i]-numExceso, d, n) + numExceso;
         cout << "mensaje original: " <<  mensaje_nros[i] << endl;
    }

     //convierto mi vector de long int a un string
     string sincifrar = "";
     for (unsigned int i = 0; i < cantBloques;i++){

         if (tamanio_n==1){
             if (mensaje_nros[i]<10){

                 sincifrar.append("00");
                 sincifrar.append(Helper::LongToString(mensaje_nros[i]));
             }
             else if (mensaje_nros[i]>9 && mensaje_nros[i]<100){
                 sincifrar.append("0");
                 sincifrar.append(Helper::LongToString(mensaje_nros[i]));
                 }
                 else{
                     sincifrar.append(Helper::LongToString(mensaje_nros[i]));
                 }
         }
         if (tamanio_n==2){
             string aux;
             aux.append(Helper::LongToString(mensaje_nros[i]));
             int cant_caracteres = aux.size();
             while (cant_caracteres<6){
                 sincifrar.append("0");
                 cant_caracteres++;
             }
             sincifrar.append(aux);
         }
         if (tamanio_n==4){
              string aux;
              aux.append(Helper::LongToString(mensaje_nros[i]));
              int cant_caracteres = aux.size();
              while (cant_caracteres<12){
                  sincifrar.append("0");
                  cant_caracteres++;
              }
              sincifrar.append(aux);
          }
     }
     string mensajeAux;
     string mensaje;
     //posiciones de los caracteres en el alfabeto del mensaje
     for(unsigned int i = 0; i < sincifrar.size(); i++){
         mensajeAux= sincifrar.substr(i,3);//(sincifrar[i]) + (sincifrar[i+1])+ (sincifrar[i+2]);
         cout << "mensaje aux "<< mensajeAux<< endl;
         int ascii = Helper::StringToInt(mensajeAux);
         cout << "ascii: "<< ascii<< endl;


         string num=Helper::copyBytesToString(ascii);

         cout << "Num:"<<num;

         mensaje.append(num);
         i++;
         i++;
         mensajeAux.clear();
     }

     cout << "Sin cifrar en entero: "<<sincifrar<<endl<<"Sin cifrar en caracteres: "<< mensaje<<endl;

     return (char*)mensaje.c_str();
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
	cout << "---------mensaje: " << mensaje <<  endl;

	//valido el mensaje para que sea potencia de 2
    string mensaje_valido = validar_mensaje((string)mensaje);
    mensaje.clear();
    mensaje=mensaje_valido;

    //string mensaje_int;//[mensaje.size()]; /*posiciones de los caracteres en el alfabeto del mensaje*/
	string mensaje_int[mensaje.size()];

     //posiciones de los caracteres en el alfabeto del mensaje
     for(unsigned int i = 0; i < mensaje.size(); i++){

    	 int ascii = mensaje.at(i);
//cout << "ascii:" << ascii << " - ";
    	 string ascii_str = Helper::IntToString(ascii);
    	 if (ascii < 10) ascii_str = "00" + Helper::IntToString(ascii);
    	 if (ascii < 100 && ascii>9) ascii_str = "0" + Helper::IntToString(ascii);

    	 //mensaje_int.push_back(ascii_str);
    	 mensaje_int[i] = ascii_str;
    	 //mensaje_int.append(ascii_str);
     }
cout << endl;
  /*   cout << "mensaje_int[]: ";
     for(unsigned int i = 0; i < mensaje.size(); i++){
    	 cout << mensaje_int[i] << " ";
     }
     cout << endl;
*/
     //cout<<" mensaje en bloque de tamanio n bytes: ";

     //long int mensaje_nros[mensaje.size() / n];
     //long int mensaje_cifrado[mensaje.size()/ n];

	 long int* mensaje_nros = new long int[mensaje.size()/ n];
     //vector<int> mensaje_cifrado;//[mensaje.size()/ n];
     long int* mensaje_cifrado = new long int[mensaje.size()/ n];

     //agrupamos de 2 en 2 el mensaje en nros.
     unsigned int k = 0;
     int index = 0;
     while(k < mensaje.size()){

		 string msg = "";

		 //si llego al fin del archivo termino
		 if(( k + tamanio_n-1) >= mensaje.size())
			 break;

		 int aux=0;
		 string aux_str;
		 aux_str.clear();
		 //concateno la cantidad de caracteres segun el tamanio de n
		 for (int i=0;i<tamanio_n;i++){
			 aux_str.append(mensaje_int[k+i]);
		 }

		 aux = Helper::StringToInt(aux_str);
		 msg.append(Helper::IntToString(aux));
		 k = k+tamanio_n;

    	 int actualMsg = Helper::StringToInt(msg);

    	 mensaje_nros[index] = actualMsg;
    	 index++;
     }

  /*   cout<<"Mensaje en numeros: ";
     for(int i = 0; i < index; i++){
    	 cout << mensaje_nros[i] << " ";
     }
     cout << endl;
*/
     //Elevo cada uno a la "d"
//     cout << endl << "Mensaje cifrado: ";

     for(unsigned int i = 0; i < mensaje.size()/tamanio_n; i++){

    	 int numExceso=0;
    	 if (tamanio_n==1){

    		 if (mensaje_nros[i] > 127) numExceso=128;
    	 }

    	 if (tamanio_n==2){

    	    if (mensaje_nros[i] > 65535) numExceso=65536;

    	 }

    	 if (tamanio_n==4){

    	   	if (mensaje_nros[i] > 4294967295) numExceso=4294967296;
    	 }

    	 //p ej, si es n de 1 byte, al nro le resto 128 y asi anulo el 8vo bit (queda en 0).
    	 //lo mismo si es de 2 o bytes, con 65535 y 4294967295 respectivamente
    	 int numSinExceso = mensaje_nros[i]-numExceso;

    	// cout << "numSinExceso: " << numSinExceso << endl;
    	 mensaje_cifrado[i] = Exponenciacion_Zn(mensaje_nros[i]-numExceso, e, n) + numExceso;
    	 //cout << mensaje_cifrado[i] << " ";

     }

     string cifrado = "";
     for (unsigned int i = 0; i < mensaje.size() / tamanio_n;i++){

    	 if (tamanio_n==1){
			 if (mensaje_cifrado[i]<10){

				 cifrado.append("00");
				 cifrado.append(Helper::LongToString(mensaje_cifrado[i]));
			 }
			 else if (mensaje_cifrado[i]>9 && mensaje_cifrado[i]<100){
					 cifrado.append("0");
					 cifrado.append(Helper::LongToString(mensaje_cifrado[i]));
				 }
				 else{
					 cifrado.append(Helper::LongToString(mensaje_cifrado[i]));
				 }
    	 }
    	 if (tamanio_n==2){
    		 string aux;
    		 aux.append(Helper::LongToString(mensaje_cifrado[i]));
    		 int cant_caracteres = aux.size();
    		 while (cant_caracteres<6){
    			 cifrado.append("0");
    			 cant_caracteres++;
    		 }
    		 cifrado.append(aux);
    	 }

    	 if (tamanio_n==4){

			 string aux;
			 aux.append(Helper::LongToString(mensaje_cifrado[i]));
			 int cant_caracteres = aux.size();

			 while (cant_caracteres < 12){

				 cifrado.append("0");
				 cant_caracteres++;
			 }

			 cifrado.append(aux);
    	 }
     }

     //cout << "cifrado: " << cifrado << endl;

     //delete mensaje_cifrado;
     //delete mensaje_int;
     //delete mensaje_nros;

     return (char*)cifrado.c_str();

     //return (char*)cifrado.c_str();
     //return (char*)mensaje.c_str();

}


void RSA::encriptar2(char* m){

	//ACA TENGO QUE LEER EL ARCHIVO DE LA CLAVE PUBLICA PARA OBTENER N Y E
    ///////////////////////////////////////////////////

	//ACA TENGO QUE CARGAR EL TAMANIO DE N DE CONFIG.TXT
	RSA::validarTamClave();
	int tamanio_n = ConfigurationMananger::getInstance()->getTamClaveRSA();

	int n,e, p,q, fi, d;

	/*do
	{
		p = rand()%25;
	}while(!es_primo(p) || p <= 1);

	do
	{
		q = rand()%25;
	}while(!es_primo(q) || q == p || q <= 1);
*/

	p = 3;
	q = 7;

	cout << "es_primo(p): " << es_primo(p) << endl;
	cout << "es_primo(q): " << es_primo(q) << endl;

	n = p * q;
	cout << "p: " << p << " - q: " << q << " - n: " << n << endl;

    /* 3) Calculamos el valor de fi */
     fi = (p-1) * (q-1);
     cout << "\n fi : " << fi;

    /* 4) Seleccionamos aleatoriamente un entero 'e' tal que mcd(e,fi)=1 y 1 < e < fi */
		do{
			e = rand() % (fi-2)+2;
		}while(alg_euc(e,fi)!=1);

     //e = 17;
     cout << "\n e : " << e;

     /* 5) Usar el algoritmo de euclides extendido para hallar un entero 'd' tal que
            ed = 1 (mod fi) donde 1 < d < fi (en otras palabras, hallar el inverso de 'e') */
	 d = Inverso_Zn(e,fi);
	 cout << "\n d : " << d;

      /*  6) La clave publica es (n,e) y la clave privada es d */
	 cout << "\n\n clave publica : (" << n <<" , " << e <<")";
	 cout << "\n clave privada : "<< d << endl << endl;

    // representamos numericamente el mensaje
	string mensaje;
	mensaje.append((const char*)m);

	cout << "\n mensaje: " << mensaje <<  endl;

	//valido el mensaje para que sea potencia de 2
    string mensaje_valido = validar_mensaje((string)mensaje);
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

     long int mensaje_nros[mensaje.size() / tamanio_n];
     long int mensaje_cifrado[mensaje.size()/ tamanio_n];

     //agrupamos de 2 en 2 el mensaje en nros.
     int k = 0;
     int index = 0;
     while(k < mensaje.size()){

		 string msg = "";

		 //si llego al fin del archivo termino
		 if(( k + tamanio_n-1) >= mensaje.size())
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

     cout<<" Mensaje en numeros: ";
     for(int i = 0; i < index; i++){
    	 cout << mensaje_nros[i] << " ";
     }
     cout << endl;

     //Elevo cada uno a la "d"
     cout << "mensaje " << mensaje << endl;
     cout << "mensaje.size() " << mensaje.size() <<  endl;
     cout << "mensaje.size() / n " << mensaje.size() / n <<endl;
     cout << endl << "Mensaje cifrado: ";
     for(int i = 0; i < mensaje.size() / tamanio_n; i++){


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

    	 mensaje_cifrado[i] = Exponenciacion_Zn(mensaje_nros[i]-numExceso, e, n) + numExceso;
    	 cout << mensaje_cifrado[i] << " ";

     }

     string cifrado;
     for (unsigned int i = 0; i < mensaje.size() / n;i++){
    	cifrado.append(Helper::LongToString(mensaje_cifrado[i]));
     }

     //cout << "\ncifrado " << cifrado.size() << endl;

     //return (char*)cifrado.c_str();
     //return (char*)mensaje.c_str();
//     return m;
}

