#include "ana_lexico.h"
#include <stdio.h>
#include <stdlib.h>

/*
* ANALIZADOR SINTACTICO (sigleton)
*/

//libera la memoria de un componente lexico
void consumir(comp_lexico* componente){
    free(componente->lexema);
    componente->lexema = NULL;
    free(componente);
    componente = NULL;
}

//funcion para poner en marcha el analizador sintactico (ver .h)
void comenzar_analisis_sintactico(){
    comp_lexico *componente = siguiente_comp_lexico();
   
   //consume componentes lexicos mientras no haya uno NULO o EOF
    while (componente != NULL && componente->id >0) {
        printf("<%d, %s>\n", componente->id, componente->lexema); 
        consumir(componente);
        componente = siguiente_comp_lexico();
    }
    
    /*
    * si el ultimo componente recibido no era nulo 
    * es EOF y hay que consumirlo aunque no se imprima
    */
    if(componente!=NULL) consumir(componente);
}

/**
* Inicializa (singleton)
*/
void inicializar_ana_sintactico(){
    //inicializacion del modulo si hiciese falta en futuras versiones
}

/**
* Cierra (singleton)
*/
void cerrar_ana_sintactico(){
    //cierre del modulo si hiciese falta en futuras versiones
}