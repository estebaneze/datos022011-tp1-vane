/*#include <iostream>

#include "refs.h"
#include "HashExtensible.h"

using namespace std;

int main ( int arg, char *argv[] ){
  
    HashExtensible hash = HashExtensible("hash.bpp");
    
    vector<Field> Vf;
    
    string str="301";
		Field F= Field(str);
		Vf.push_back(F);
  
  
     Key_Node K= Key_Node();

    
    for (int i=0; i<Vf.size();i++){
       Field FAux=Vf.at(i);
        K.AddField(FAux);   
    } 
    
      ref auxRef2;
    auxRef2.posBloq=1;
     auxRef2.posReg=2;
     auxRef2.Key=F;
    
    Refs R=Refs();
    
    R.vRefs.push_back(auxRef2);
    
    K.ref =R;
    
    Key_Node *pK=new Key_Node();
    *pK=K;
    
 //   hash.add(K,R);
   
   
   // 
   vector<Field> Vf2;
    
    string str2="303";
		Field F2= Field(str2);
		Vf2.push_back(F2);
  
  
     Key_Node K2= Key_Node();

    
    for (int i=0; i<Vf2.size();i++){
       Field FAux=Vf2.at(i);
        K2.AddField(FAux);   
    } 
    
      ref auxRef22;
    auxRef22.posBloq=1;
     auxRef22.posReg=2;
     auxRef22.Key=F2;
    
    Refs R2=Refs();
    
    R2.vRefs.push_back(auxRef22);
    
    K.ref =R2;
    

//    hash.add(K2,R2);
   
   
   
   
   
   
   
   
   
    hash.save();

	
 /*   string str2="185";
		Field F2= Field(INTEGER,str2);
		Vf2.push_back(F2);
  
     Key_Node K2= Key_Node();
     K2.ref.posBloq=1;
     K2.ref.posReg=1;
    
    for (int i=0; i<Vf2.size();i++){
       Field FAux=Vf2.at(i);
        K2.AddField(FAux);   
    } 
     cout<<"control"<<endl;
    tree.add_key(K2,true);
    
    system("PAUSE");
    return EXIT_SUCCESS;

  system("PAUSE"); 	
   return 0;
}
*/
