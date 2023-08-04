//Ignacio Fernandez y Fermin Gonzalez
#include "trabajo4.cpp"

int main(){
     string file_name;
     cin >> file_name;
     ifstream f;
     f.open(file_name);
     Tabla<char,int> t = tabla_vacia<char,int>();
     string result;
     string linea;
     while(getline(f,linea)){
         result=result+linea+'\n';
     }
     f.close();
     cout<<result<<endl;     // Los saltos de lineas los vamos a representar como _ en la representacion
     for(int i = 0;i<result.length();++i){
         insertar_tabla(t,result[i],1);
     }
     cout<<t<<endl;
     
     priority_queue<Arbol_h> q=tabla_a_cola(t);
     cout<<q<<endl;
     
     Arbol_h arb_huff= cola_a_arbol(q);
     cout<<arb_huff<<endl;
     string arbh=codifica_arbol(arb_huff);
     cout<<arbh<<endl; 
     
     string file_name_huff;
     cin >> file_name_huff;
     cod_huff_to_file(arbh,file_name_huff); 
     
     Tabla<char,codigo_h> s = tabla_codigos(arb_huff);
     cout<<s<<endl;
     
     codigo_h codificado= tabla_a_codigoh(file_name,s); 
     cout<<codificado<<endl;
     
     string file_name_cod;
     cin >> file_name_cod;
     vector_bool_to_file(codificado, file_name_cod);
}