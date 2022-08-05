#include "ana_lexico.h"
#include "sis_entrada.h"
#include "stdlib.h"
#include "automata.h"
#include "tabla_simbolos.h"
#include "errores.h"
#include <stdio.h>
#include <unistd.h>

/*
* ANALIZADOR LEXICO (singleton)
*/


//almacena el valor del ultimo lexema leido
int ultimo_lex = -1;

int _sin_significado(int nombre);
int _calcular_significado_retorno();

//devuelve un componente lexico (ver .h)
comp_lexico* siguiente_comp_lexico(){
    struct estado estado;
    /* 
    * repite hasta que encuentra un componente con significado 
    * (i.e. que no sea un espacio, comentario...)
    */
    while(1){
        //inicializacion del automata
        estado.siguiente=inicial;
        estado.nombre = 0;
        estado.caracter = 0;
        
        //ponemos en marcha corre mientras haya un estado siguiente 
        while (estado.siguiente){
            estado.caracter = siguiente_caracter(); //del sistema de entrada
            estado.siguiente(&estado);
        }

        if(estado.es_ultimo_extra){
            /* si el ultimo caracter usado para el reconocimiento no es parte del
            lexema reducimos su longitud y devolvemos un caracter*/
            devolver_caracter(); //del sistema de entrada
        }else if (estado.nombre == '\n'){
            //si se reconoce un retorno de carro se calcula si es en realidad ';'
             estado.nombre = _calcular_significado_retorno();
        }

        
        if(_sin_significado(estado.nombre)){
            ignorar(); //del sistema de entrada
        }else{
            break;
        }
    }

    //reserva de memoria para comp lexico
    comp_lexico* comp = (comp_lexico*)malloc(sizeof(comp_lexico));
    if (comp == NULL) return NULL;

    //pedir al sistema de entrada un str* del comp lexico
    comp->lexema = pedir_ultimo_lexema(); //del sistema de entrada
    comp->id = estado.nombre;

    /* 
    * En este momento IDENTIFIER puede hacer referencia tanto a un
    * identicador como a una palabra reservada. Consulta a la tabla de simbolos
    */
    if(estado.nombre == IDENTIFIER){
        comp->id = buscar_comp_lexico(comp->lexema); //de la tabla de simbolos
    }else if (comp->id == ';'){
        /*
        * Un ';' puede estar escrito en el codigo a analizar como un '\n'
        * por si esto es asi metemos a mano el ';'
        */
        comp->lexema[0]=';';
    }else if(estado.nombre < -1){
        /*
        * -1 es EOF, los demas numeros negaticos se corresponden
        * con menos el valor de un componente lexico mal formado
        */
        comp->id *=-1;
        avisar_error(MAL_FORMADO,comp);
    }

    ultimo_lex = comp->id;
    return comp;
}

//comprueba si un componente lexico tiene significado
int _sin_significado(int nombre){
    return (nombre == '\n' || nombre == ' ' || nombre == COMENTARIO || nombre == '\t' || nombre == '\r');
}

//calcula el valor real de un retorno de carro en funcion del ultimo lexema leido (ver doc de go)
int _calcular_significado_retorno(){
    switch (ultimo_lex){
        case IDENTIFIER:
        case INTEGER_LIT:
        case FLOAT_LIT:
        case IMAGIN_LIT:
        case STR_LIT:
        case BREAK:
        case CONTINUE: 
        case FALLTHROUGH:
        case RETURN:
        case MAS_MAS:
        case MENOS_MENOS:
        case ')':
        case ']':
        case '}':
            return ';';
        default:
            return '\n';
    }
}

//inicializar
void inicializar_ana_lex(){
    ultimo_lex = 0;
}

//inicializar
void cerrar_ana_lex(){
    ultimo_lex = -1;
}