//Ignacio Fernandez y Fermin Gonzalez
#include<iostream>
#include<queue>
#include<vector>
#include<typeinfo>
#include<fstream>
#include<limits.h>
#include<random>
#include<string>

using namespace std;

//TABLAS CLAVE-VALOR_MODIF

template<typename K,typename V>
struct Nodo_tabla{
       K clave;
       V valor_modif;
       Nodo_tabla<K,V> * izdo = NULL;
       Nodo_tabla<K,V> * dcho = NULL;
};

template<typename K, typename V>
using Tabla = Nodo_tabla<K,V> *;

template <typename K,typename V>
Tabla<K,V> tabla_vacia();

template <typename K,typename V>
bool es_tabla_vacia(Tabla<K,V> t);

template <typename K,typename V>
void insertar_tabla(Tabla<K,V> & t , K e, V f);

template <typename K,typename V>
bool esta_clave(const Tabla<K,V> & t, K e);

template <typename K,typename V>          
V consultar(const Tabla<K,V> & t, K e);

template <typename K,typename V>    
K max(const Tabla<K,V> & t);

template <typename K,typename V>                
void eliminar_tabla(Tabla<K,V> & t , K e);

template <typename K,typename V>
void liberar(Tabla<K,V> & t);

template<typename K,typename V>   
ostream & operator << (ostream & o, Tabla<K,V> t);

//ARBOL_HUFFMAN

struct Nodo_h{
    char c;
    int frecuencia;
    Nodo_h * izd=NULL;
    Nodo_h * dcho=NULL;
};

struct Arbol_h{
    Nodo_h * raiz;
};

Arbol_h hoja(char clave, int f);

bool es_hoja(Arbol_h a);

Arbol_h plantar(Arbol_h a, Arbol_h b);

Arbol_h arbol_vacio();

bool es_arbol_vacio(Arbol_h a);

bool operator <(Arbol_h a1,Arbol_h a2);

ostream & operator << (ostream & o, Arbol_h a);

/*  ARBOL-> CODIGO */

string codifica_arbol(Arbol_h a);

/*  CODIGO-> ARBOL  */

int long_izd(string s);

Arbol_h decodifica_arbol(string s);

/*  TABLA_FRECUENCIAS-> PRIORITY_QUEUE  */

void tabla_a_cola_aux(const Tabla<char,int> & t, priority_queue<Arbol_h> & q);

priority_queue<Arbol_h> tabla_a_cola(const Tabla<char,int> & t);

ostream & operator << (ostream & o, priority_queue<Arbol_h> q);  //cout para las priority_queue

/*  PRIORITY_QUEUE->ARBOL_HUFFMAN  */

Arbol_h cola_a_arbol(priority_queue<Arbol_h> & q);

/*  CODIGOS_HUFFMAN  */

using codigo_h = vector<bool>;

codigo_h codigo_vacio();

ostream & operator << (ostream & o, codigo_h h);

codigo_h operator + (codigo_h b1, codigo_h b2);

/*  ARBOL_HUFFMAN->TABLA_CODIGOS  */

void arbol_a_tabla(Arbol_h a, codigo_h & prefijo, Tabla<char,codigo_h> & t);

Tabla<char,codigo_h> tabla_codigos(Arbol_h a);

/*  TABLA_CODIGOS+MENSAJE.TXT-> CODIGO_H  */

codigo_h tabla_a_codigoh(string file_name, const Tabla<char,codigo_h> & t);

/*  CODIGO_H ->ARCHIVO , ARCHIVO->CODIGO_H  */

void vector_bool_to_file(codigo_h v, string file_name);

codigo_h file_to_vector_bool(string file_name);

/* COD_ARB_HUFF A ARCHIVO , ARCHIVO A COD_ARB_HUFF  */

string file_to_cod_huff(string file_name_huff);

void cod_huff_to_file(string arb_huff, string file_name_huff);

/*  ARBOL_HUFFMAN + CODIGO_H-> MENSAJE  */

void elimina_primer(codigo_h & cod);

char decodifica_aux(const Arbol_h & a, codigo_h & cod);

string decodifica(const Arbol_h & a, codigo_h & cod);


//TABLAS CLAVE-VALOR MODIFICABLE

template <typename K,typename V>
Tabla<K,V> tabla_vacia(){
       return NULL;
}

template <typename K,typename V>
bool es_tabla_vacia(Tabla<K,V> t){
     return t == NULL;
}

template <typename K,typename V>
void insertar_tabla(Tabla<K,V> & t , K e, V f){
     if(es_tabla_vacia(t)){
        t = new Nodo_tabla<K,V>;
        t->clave = e;
        t->valor_modif = f;
     }
     else if(t->clave > e){
          insertar_tabla(t->izdo,e,f);
     }
     else if(t->clave < e){
          insertar_tabla(t->dcho,e,f);
     }
     else if(t->clave==e){
         t->valor_modif = (t->valor_modif)+f; 
     }
}

template <typename K,typename V>
bool esta_clave(const Tabla<K,V> & t, K e){
    if (es_tabla_vacia(t)){
        return false;
    }
    else{
        if (t->clave==e){
            return true;
        }
        else if(t->clave > e){
            return esta_clave(t->izdo,e);
        }
        else{
            return esta_clave(t->dcho,e);
        }
    }
}


template <typename K,typename V>          
V consultar(const Tabla<K,V> & t, K e){
    V result;
    if(!(esta_clave(t,e))){
        throw runtime_error("La tabla no contiene el valor");
    }
    else if (t->clave == e){
        result = t->valor_modif;
    }
    else if (t->clave > e){
        result = consultar(t->izdo, e);
    }
    else if (t->clave < e){
        result= consultar(t->dcho, e);
    }
    return result;
}

template <typename K,typename V>    
K max(const Tabla<K,V> & t){
    K result;
    if(es_tabla_vacia(t)){
        throw runtime_error("No hay ningun elemento en la tabla");
    }
    if(t->dcho==NULL){
        result=t->clave;
    }
    else{
        result= max(t->dcho);
    }
    return result;
}

template <typename K,typename V>                
void eliminar_tabla(Tabla<K,V> & t , K e){
    if(es_tabla_vacia(t)){
        throw runtime_error("El elemento no esta en la tabla");
    }
     else if(t->clave > e){
        eliminar_tabla(t->izdo,e);
     }
     else if(t->clave < e){
        eliminar_tabla(t->dcho,e);
     }
     else if(t->clave==e && t->dcho==NULL){
         t=t->izdo;
     }
     else{
         K m=max(t->izdo);
         t->clave=m;
         t->valor_modif=consultar(t->izdo,m);
         eliminar_tabla(t->izdo, m);
     }
}

template <typename K,typename V>
void liberar(Tabla<K,V> & t){
       if(t!=NULL){
           liberar(t->izdo);
           liberar(t->dcho);
           delete t;
       }
}

template<typename K,typename V>   
ostream & operator << (ostream & o, Tabla<K,V> t){ //Donde habia \n ponemos _ en su lugar para que no haga un salto de linea al representar
    if(es_tabla_vacia(t)){
         o << "" ;
       }
    else if(t->izdo==NULL && t->dcho==NULL){
        if(t->clave=='\n'){
            o<< "_:" << t->valor_modif ;
        }
        else{
            o<< t->clave << ":" << t->valor_modif ;
        }
    }
    else if(t->izdo==NULL){
        if(t->clave=='\n'){
            o<< "_:" << t->valor_modif << "," << t->dcho;
        }
        else{
            o << t->clave <<":" << t->valor_modif << "," << t->dcho;
        }
    }
    else if(t->dcho==NULL){
        if(t->clave=='\n'){
            o<<"_:" << t->valor_modif << "," << t->izdo;
        }
        else{
            o<< t->clave << ":" << t->valor_modif << "," << t->izdo;
        }
    }
    else{
        if(t->clave=='\n'){
            o<<"_:" << t->valor_modif << "," << t->izdo << "," <<t->dcho;
        }
        else{
            o<< t->clave << ":" << t->valor_modif << "," << t->izdo << "," <<t->dcho;
        }
    }
    return o;
}


//ARBOLES HUFFAMAN


Arbol_h hoja(char clave, int f){
    Nodo_h * aux=new Nodo_h;
    aux->c=clave;
    aux->frecuencia= f;
    Arbol_h a;
    a.raiz=aux;
    return a;
}

bool es_hoja(Arbol_h a){
    return (a.raiz)->izd==NULL && (a.raiz)->dcho==NULL;
}

Arbol_h plantar(Arbol_h a, Arbol_h b){
    Nodo_h * aux=new Nodo_h;
    aux-> frecuencia = (a.raiz->frecuencia) + (b.raiz->frecuencia);
    aux->izd = a.raiz;
    aux-> dcho=b.raiz;
    Arbol_h c;
    c.raiz=aux;
    return c;
}

Arbol_h arbol_vacio(){
    Arbol_h a;
    a.raiz=NULL;
    return a;
}

bool es_arbol_vacio(Arbol_h a){
    return a.raiz==NULL;
}


bool operator <(Arbol_h a1,Arbol_h a2){
    return (a1.raiz->frecuencia) > (a2.raiz->frecuencia);
}


ostream & operator << (ostream & o, Arbol_h a){      //Donde hay salto de linea ponemos _
    if(es_hoja(a)){
        if(((a.raiz)->c)=='\n'){
            o <<"_:"<< ((a.raiz)->frecuencia)<<",";
        }
        else{
            o << ((a.raiz)->c) <<":"<< ((a.raiz)->frecuencia)<<",";
        }
    }
    else{
        Arbol_h izd1;
        izd1.raiz=(a.raiz->izd);
        Arbol_h dch1;
        dch1.raiz=(a.raiz->dcho);
        o<<izd1<<" "<<dch1;
    }
    return o;
}

string codifica_arbol(Arbol_h a){
    string result="";
    if(es_hoja(a)){
        if ((a.raiz->c)=='\n'){
            result=result+'_';     //asi la expresion la tenemos en la misma linea e identificamos el salto de linea con barrabaja
        }
        else{
            result=result+(a.raiz->c);
        }
    }
    else{
        Arbol_h izd1;
        izd1.raiz=(a.raiz->izd);
        Arbol_h dch1;
        dch1.raiz=(a.raiz->dcho);
        string iz=codifica_arbol(izd1);
        string dr=codifica_arbol(dch1);
        result=result+'+'+iz+dr;
    }
    return result;
}


int long_izd(string s){ //devuelve la longitud de la cadena correspondiente a la codificacion del arbol izq
    int j=0;
    int cont=0;
    if (s[0]=='+'){
        j++;
        cont++;
    }
    while (j!=0 && cont<s.length()){
        if (s[cont]=='+'){
            j++;
            cont++;
        }
        else{
            j--;
            cont++;
        }
    }
    return cont;
}

Arbol_h decodifica_arbol(string s){
    Arbol_h a1;
    if(s[0]=='+'){
        int cont=long_izd(s);
        Arbol_h a2=decodifica_arbol(s.substr(1,cont-1)); //desde la posicion 1 y longitud cont-1
        Arbol_h a3= decodifica_arbol(s.substr(cont)); //desde la posicion cont hasta el final
        a1=plantar(a2,a3);
    }
    else{
        if (s[0]=='_'){
            a1=hoja('\n',0); 
        }
        else{
            a1=hoja(s[0],0);  ;
        }
    }
    return a1;
    
}

//Lo construimos con todas las frecuencias 0, ya que solo necesitabamos las frecuencias para su construccion, ya da igual, si las queremos poner como estaban necesitariamos la tabla


//PASAR DE TABLA_FRECUENCIAS A PRIORITY QUEUE


void tabla_a_cola_aux(const Tabla<char,int> & t, priority_queue<Arbol_h> & q){
    if(!(t==NULL)){
        Arbol_h arb_unitario = hoja(t->clave ,t->valor_modif);
        q.push(arb_unitario);
        tabla_a_cola_aux(t->izdo,q);
        tabla_a_cola_aux(t->dcho,q);
    }
}

priority_queue<Arbol_h> tabla_a_cola(const Tabla<char,int> & t){
    priority_queue<Arbol_h> q;
    tabla_a_cola_aux(t,q);
    return q;
}

//DEFINIMOS EL COUT PARA LAS PRIORITY QUEUE

ostream & operator << (ostream & o, priority_queue<Arbol_h> q){
    priority_queue<Arbol_h> aux=q;
    while(!aux.empty()){
         o << aux.top();
         aux.pop();
    }
    o<<endl;
    return o;
}

//PASAR DE PRIORITY_QUEUE A ARBOL_HUFFMAN

Arbol_h cola_a_arbol(priority_queue<Arbol_h> & q){
    Arbol_h result;
    if(q.empty()){
        throw runtime_error ("La cola esta vacia");
    }
    else if (q.size()==1){
        result=q.top();
    }
    else{
        Arbol_h a1=q.top();
        q.pop();
        Arbol_h a2=q.top();
        q.pop();
        Arbol_h a3= plantar(a1,a2);
        q.push(a3);
        result= cola_a_arbol(q);   
    }
    return result;
}


//PASAR DE ARBOL_HUFFMAN A TABLA_CODIGOS

using codigo_h = vector<bool>;

codigo_h codigo_vacio(){
    codigo_h a;
    return a;
}

void arbol_a_tabla(Arbol_h a, codigo_h & prefijo, Tabla<char,codigo_h> & t){   
    if (es_hoja(a)){                             
        insertar_tabla(t,(a.raiz->c),prefijo);
    }
    else{
        if(a.raiz->izd!=NULL){
            codigo_h aux1= prefijo;
            aux1.push_back(false);  //añade un 0 al final
            Arbol_h izd1;
            izd1.raiz=(a.raiz->izd);
            arbol_a_tabla(izd1,aux1,t); 
        }
        if(a.raiz->dcho!=NULL){
            codigo_h aux2=prefijo;
            aux2.push_back(true);   //añade un 1 al final
            Arbol_h dch1;
            dch1.raiz=(a.raiz->dcho);
            arbol_a_tabla(dch1,aux2,t);
        }
    }
}

Tabla<char,codigo_h> tabla_codigos(Arbol_h a){
    codigo_h prefijo=codigo_vacio();
    Tabla<char,codigo_h> t=tabla_vacia<char,codigo_h>();
    arbol_a_tabla(a,prefijo,t);
    return t;
}


ostream & operator << (ostream & o, codigo_h h){
    for(int i = 0; i< h.size(); i++){
        o << h[i] ;
    }
    return o;
}

//TABLA_CODIGOS+MENSAJE A CODIGO_H

codigo_h operator + (codigo_h b1, codigo_h b2){
     codigo_h result=b1;
     for(int i=0; i<b2.size(); i++){
         result.push_back(b2[i]);
     }
     return result;
}

codigo_h tabla_a_codigoh(string file_name, const Tabla<char,codigo_h> & t){
    ifstream f = ifstream(file_name);
    codigo_h result=codigo_vacio(); 
    string s;
    string linea;
    while(getline(f,linea)){
        s=s+linea+'\n';
    }
    f.close();
    for(int i = 0; i<s.length();i++){
        codigo_h aux = consultar(t,s[i]);
        result=result+aux; 
    }
    return result;
}

// PARA GUARDAR UN VECTOR BOOL EN UN ARCHIVO

void vector_bool_to_file(codigo_h v, string file_name){
    ofstream f = ofstream(file_name);
    long num_bits = v.size();
    unsigned char c;
    long inic;
    f << num_bits<<endl;
    for(int i = 0;i< num_bits/CHAR_BIT; i++){
        c = 0;
        inic = i*CHAR_BIT;
        for(int j = CHAR_BIT-1;j>=0;j--){ 
           c = c*2+v[inic+j];
        }
        f<<c;
    }
    c = 0;
    inic = (num_bits/CHAR_BIT)*CHAR_BIT;
    for(int j = num_bits%CHAR_BIT-1;j>=0;j--){
        c = c *2 + v[inic + j];
    }
    f << c;
    f.close();
}

codigo_h file_to_vector_bool(string file_name){
    long num_bits;
    vector<bool> result;
    ifstream f = ifstream(file_name);
    f >> num_bits;
    unsigned char c;
    string s;
    getline(f,s); 
    long pos = 0;
    for(long i =0; i<num_bits/CHAR_BIT; i++){
         c = f.get();
         for(long j = 0 ; j<CHAR_BIT;j++){
              result.push_back(c % 2);
              c = c/2;
              pos++;
         }
    }
    c = f.get();
    for(long j = num_bits%CHAR_BIT-1;j>=0;j--){
        result.push_back(c % 2);
        c = c/2;
    }
    f.close();
    return result; 
}

/* COD_ARB_HUFF A ARCHIVO , ARCHIVO A COD_ARB_HUFF  */

string file_to_cod_huff(string file_name_huff){
    ifstream f = ifstream(file_name_huff);
    string result;
    string linea;
    while(getline(f,linea)){
        result=result+linea;
    }
    f.close();
    return result;
}  

void cod_huff_to_file(string arb_huff, string file_name_huff){
    ofstream f = ofstream(file_name_huff);
    f << arb_huff;
    f.close();
}


// ARBOL_HUFFMAN + CODIGO_FINAL A MENSAJE

void elimina_primer(codigo_h & cod){ //Elimina primer digito de un codigo
    codigo_h result=codigo_vacio(); 
    for (int i=0;i<cod.size()-1;i++){
        result.push_back(cod[i+1]);
    }
    cod=result;
}

char decodifica_aux(const Arbol_h & a, codigo_h & cod){ // Dado un arbol y el codigo del mensaje encriptado, te devuelve el primer caracter del codigo y avanza el codigo
    char result;
    if(cod.empty()){
        result=a.raiz->c;
    }
    else{
        if(es_hoja(a)){
            result=((a.raiz)->c);
        }
        else if(cod[0]==false){
            Arbol_h aux1;
            aux1.raiz=(a.raiz)->izd;
            elimina_primer(cod);
            result=decodifica_aux(aux1,cod);
        }
        else if(cod[0]==true){
            Arbol_h aux2;
            aux2.raiz=(a.raiz)->dcho;
            elimina_primer(cod);
            result=decodifica_aux(aux2,cod);
        }
    }
    return result;
}

string decodifica(const Arbol_h & a, codigo_h & cod){
    string result="";
    while (!cod.empty()){
        result=result+decodifica_aux(a,cod);
    }
    return result;
}









