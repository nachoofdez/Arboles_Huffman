//Ignacio Fernandez y Fermin Gonzalez
#include "trabajo4.cpp"


int main(){
    
     string file_name_huff; //Meter los dos nombres de la parte 1
     cin >> file_name_huff;
     
     string file_name_cod;
     cin >> file_name_cod;
     
     codigo_h codificado=file_to_vector_bool(file_name_cod);
     
     cout<<codificado<<endl;
          
     string z=file_to_cod_huff(file_name_huff); 
     Arbol_h arb_huff= decodifica_arbol(z);
     cout<<arb_huff<<endl;;
     
     Tabla<char,codigo_h> s = tabla_codigos(arb_huff);
     cout<<s<<endl;
     
     string nuevo_mensaje=decodifica(arb_huff,codificado);
     cout<<nuevo_mensaje;
}