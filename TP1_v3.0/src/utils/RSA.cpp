/*
 * RSA.cpp
 *
 *  Created on: 29/11/2011
 *      Author: loo
 */

#include "RSA.h"

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

// eliminamos los espacios del texto plano
  for(unsigned int i=0;i<texto_plano.size();i++)
     if(texto_plano.at(i)!=' ')
       texto_plano_valido+=texto_plano.at(i);

 // completamos con x al final para que sea potencia de 2
   int tam=texto_plano_valido.size();
   if(tam%2!=0)
    texto_plano_valido+="x";

  return texto_plano_valido;
}


char* RSA::encriptar(char* m)
{
	return m;

     long int p,q,n,fi,e,d;
     string mensaje,mensaje_valido;
     char mensaje_aux[300];
     cout<<" ENCRIPTAR :\n\n";

     cout << "supongo n de 1 byte (char)" << endl;

     char value = 2;
     cout << value << endl;

     // Debemos seguir una serie de pasos para generar las claves publica y privada :

    /* 1) Generamos aleatoriamente dos enteros p y q (p y q pueden ser cualquier numero
         pero deben de ser del mismo tamaño , en este caso yo quiero que sean de 2 cifras) ,
          ademas deben de ser primos */
         do
         {
        	 p=rand()%50+50;
         }while(!es_primo(p));

         do
         {
        	 q=rand()%50+50;
         }while(!es_primo(q));
         //p=2357;
         //q=2551;

     	 p = 47;
     	 q = 59;

         cout<<" p : "<<p<<"\n q : "<<q;

    /* 2) Calculamos el valor de n */
         n = p * q;
         cout<<"\n n : "<<n;


    /* 3) Calculamos el valor de fi */
         fi=(p-1)*(q-1);
         cout<<"\n fi : "<<fi;

    /* 4) Seleccionamos aleatoriamente un entero 'e' tal que mcd(e,fi)=1 y 1 < e < fi */
       /*do{
    	   e = rand() % (fi-2)+2;
       }while(alg_euc(e,fi)!=1);
       */
         e = 17;
       cout<<"\n e : "<<e;

    /* 5) Usar el algoritmo de euclides extendido para hallar un entero 'd' tal que
           ed = 1 (mod fi) donde 1 < d < fi (en otras palabras, hallar el inverso de 'e') */
        d = Inverso_Zn(e,fi);
        cout<<"\n d : "<<d;

     /*  6) La clave publica es (n,e) y la clave privada es d */
        cout<<"\n\n clave publica : ("<<n<<" , "<<e<<")";
        cout<<"\n clave privada : "<< d << endl << endl;

    ///////////////////////////////////////////////////

     cout<<" Ingrese mensaje a encriptar : ";
     //fflush(stdin);
     //gets(mensaje_aux);
     //mensaje=mensaje_aux;
     //mensaje="criptografia";
     cin >> mensaje;
     //cout<<" mensaje ingrsa: "<< mensaje <<endl;

     mensaje_valido = validar_mensaje(mensaje);
     cout<<" Mensaje valido : "<< mensaje_valido <<endl;

     // representamos numericamente el mensaje

     string mensaje_int[mensaje_valido.size()]; /*posiciones de los caracteres en el alfabeto del mensaje*/

     //posiciones de los caracteres en el alfabeto del mensaje
     for(unsigned int i = 0; i <mensaje_valido.size(); i++){

    	 int pos = get_pos(GetAlfabeto(),mensaje_valido.at(i));
    	 string posstr = Helper::IntToString(pos);
    	 if(pos < 10)
    		 posstr = "0" + Helper::IntToString(pos);

    	 mensaje_int[i] = posstr;
    	 //mensaje_int[i] = get_pos(alfabeto,mensaje_valido.at(i));

     }

     cout << " mensaje_int[]: ";
     for(unsigned int i = 0; i <mensaje_valido.size(); i++){
    	 cout << mensaje_int[i] << " ";
     }
     cout << endl;
     //cout<<" mensaje en numeros (formado con posiciones de los caracteres en el alfabeto del mensaje) : ";
//     for(unsigned int i = 0; i < mensaje_valido.size(); i++)
  //     cout<<mensaje_int[i]<<" ";

     cout<<endl;
     //cout<<" mensaje en numeros 2: ";

     long int mensaje_nros[mensaje_valido.size() / 2];
     long int mensaje_cifrado[mensaje_valido.size()/2];

     //agrupamos de 2 en 2 el mensaje en nros.
     int k = 0;
     int index = 0;
     while(k < mensaje_valido.size()){

		 string msg = "";

		 if(k+1 >= mensaje_valido.size())
			 break;

		 int aux = Helper::StringToLong(mensaje_int[k] + mensaje_int[k+1]);
		 msg.append(Helper::IntToString(aux));
		 k = k+2;

    	 int actualMsg = Helper::StringToInt(msg);
    	 mensaje_nros[index] = actualMsg;
    	 index++;
     }

     cout<<" Mensaje en numeros (formado con posiciones de los caracteres en el alfabeto del mensaje) : " << endl;
     cout << "	";
     for(int i = 0; i < mensaje_valido.size() / 2; i++){
    	 cout << mensaje_nros[i] << " ";
     }
     cout << endl;

     //Elevo cada uno a la "d"
     cout << endl << "Mensaje cifrado: ";
     for(int i = 0; i < mensaje_valido.size() / 2; i++){
    	 mensaje_cifrado[i] = Exponenciacion_Zn(mensaje_nros[i], e, n);
    	 cout << mensaje_cifrado[i] << " ";
     }
     cout << endl;

     // agrupamos de 2 en 2 el mensaje numerico
  /*   for(int i=0; i < (mensaje_valido.size()/2); i++)
    	 mensaje_cifrado[i] = mensaje_int[i*2] * 100 + mensaje_int[i*2+1];

     cout<<" mensaje cifrado : ";
      for(int i=0;i<(mensaje_valido.size()/2);i++)
        cout<<mensaje_cifrado[i]<<" ";
      cout<<endl;

      cout<<" mensaje cifrado : ";
      // elevamos al cuadrado el mensaje_cifrado
      for(int i = 0; i < (mensaje_valido.size()/2); i++)
        mensaje_cifrado[i] = Exponenciacion_Zn(mensaje_cifrado[i],e,n);

      for(int i=0;i<(mensaje_valido.size()/2);i++)
        cout << mensaje_cifrado[i] << " ";
*/
      cout<<endl;
}

char* RSA::desencriptar(char* m)
{
	return m;

     cout<<"\n DESENCRIPTAR :\n\n";
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


string RSA::GetAlfabeto(){
	return "abcdefghijklmnopqrstuvwxyz0123456789_";
}


