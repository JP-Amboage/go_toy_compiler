#include "tabla_simbolos.h"
#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
* TABLA DE SIMBOLOS (singleton)
*/

//palabras reservadas que se pre-insertan en la tabla de simbolos
const int id_reservadas[] = { PACKAGE, IMPORT, FUNC, CHAN, VAR, RANGE, GO};
char* lex_reservadas[] = { "package", "import", "func", "chan", "var", "range","go"}; 

//arbol e que se apoya la tabla (singleton)
abb arbol;


//buscar componente lexico
int buscar_comp_lexico(char *lexema){
    //funcion añadida a la librería abb.h 
    return buscar_insertar(&arbol, lexema);
}

//inicialización de la tabla (singleton)
void inicializar_tabla(){
    //creacion del arbol
    crear_arbol(&arbol);   
    int num_reservadas = sizeof(id_reservadas)/sizeof(id_reservadas[0]);
    //insercion de las palabras reservadas
    for(int i = 0; i < num_reservadas; i++){
        tipoelem reservada = {.id = id_reservadas[i], .lexema = lex_reservadas[i]};
        insertar(&arbol, reservada);
    }
}

//borrado de la tabla
void borrar_tabla(){
    destruir_arbol(&arbol);
}

//imprime la tabla en orden
void print_tabla(){
    printf("========= TABLA SIMBOLOS =========\n");
    inorden(arbol);
    printf("======== FIN TABLA SIMBOLOS =======\n");
}