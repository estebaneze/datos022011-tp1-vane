
/*
#include <cstdlib>
#include <iostream>
#include "bp_tree.h"

using namespace std;

int main(int argc, char *argv[])
{
    
    Bp_Tree tree = Bp_Tree("arbol.bpp");
    
    
    
    
    vector<Field> Vf;
    
    string str="196";
		Field F= Field(str);
		Vf.push_back(F);
  
  
     Key_Node K= Key_Node();
//     K.ref.posBloq=2;
//     K.ref.posReg=2;
    
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
     tree.print_tree();
    tree.add_key(K,true);
    
  //   tree.add_key(K,false);
    
   tree.print_tree();
    tree.save();
    std::vector<Field> Vf2;
	
 /*  string str2="185";
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
}

*/
