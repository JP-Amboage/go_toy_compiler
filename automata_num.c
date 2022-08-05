#include <ctype.h>
#include <stdlib.h>
#include "automata_num.h"

/*
* SUB-AUTOMATA PARA RECONOCER NUMEROS (ej: entero decimal/hexadecimal; float; imaginarios)
*/

void _cifras_exp();
void _cifras_exp_cifras();
void _cifras_exp_signo();
void _ini_hex();
void _hex();


//estado al que deriva el automata principal despues de procesar un numero del 1 al 9
void num_ini_1_9(struct estado *estado){
    if(isdigit(estado->caracter)){
        //devora numeros
        estado->siguiente = num_ini_1_9;
    }else if (estado->caracter == '.'){
        //encontrar un . => cambio de estado
        estado->siguiente = num_ini_punto_cifra;
    }else if (estado->caracter == 'e' || estado->caracter == 'E'){
        //econtrar un exponente => cambio de estado
        estado->siguiente = _cifras_exp;
    } else if (estado->caracter == 'i'){
        //econtrar una i reconoce un imaginario
        estado->siguiente = NULL;
        estado->nombre = IMAGIN_LIT;
        //la i es parte del lexema
        estado->es_ultimo_extra = 0;
    }else{
        //econtrar cualquier otra cosa implica que se reconoce un entero
        estado->siguiente = NULL;
        estado->nombre = INTEGER_LIT;
        //el caracter que permitio reconocer el entero no es parte del mismo
        estado->es_ultimo_extra = 1;
    }
}

//estado al que deriva el automata principal despues de procesar un 0
void num_ini_0(struct estado *estado){
    if(estado->caracter == 'x' || estado->caracter == 'X'){
        //0x o 0X inidican que viene un hexadecimal => cambio de estado
        estado->siguiente = _ini_hex;
    }
    /*
    * FALTAN IF ELSE para otros numeros especiales
    * como binarios 0B/0b u octales 0O/0o
    */ 
    else{
        /* en caso de no recibir una letra "especial" despues del 0
        * el procesamiento del 0 es el mismo que en las cifras 1-9 
        * para no duplicar codigo llamamos a la funcion de inicio para 1_9
        */
        num_ini_1_9(estado);
    }
}

/* 
* estado al que derivan:
* el principal despues de procesar "." "0"..."9"
* estados internos despues de procesar un "."
*/
void num_ini_punto_cifra(struct estado *estado){
    if(isdigit(estado->caracter)){
        //devora numeros
        estado->siguiente = num_ini_punto_cifra;
    }else if (estado->caracter == 'e' || estado->caracter == 'E'){
        //exponente => cambio de estado
        estado->siguiente = _cifras_exp;
    }else if (estado->caracter == 'i'){
        //i => reconoce un imaginario
        estado->siguiente = NULL;
        estado->nombre = IMAGIN_LIT;
        //la propia i es parte del imaginario
        estado->es_ultimo_extra = 0;
    }else{
        //si no hay digitos ni ',' ni exponente ni 'i' reconoce un float
        estado->siguiente = NULL;
        estado->nombre = FLOAT_LIT;
        //el ultimo caracter no es parte del float
        estado->es_ultimo_extra = 1;
    }
}

//estado privado al que se llega despues de encontrar un exponente (e|E)
void _cifras_exp(struct estado *estado){
    if(isdigit(estado->caracter)){
        estado->siguiente = _cifras_exp_cifras;
    }else if (estado->caracter == '+' || estado->caracter == '-'){
        estado->siguiente = _cifras_exp_signo;
    }else{
        /*si despues del exponente no hay un numero o un signo
        * reconoce un float mal formado
        */
        estado->siguiente = NULL;
        estado->nombre = -1*FLOAT_LIT;
        estado->es_ultimo_extra = 1;
    }
}

// estado privado al  que se llega despues de haber encontrado cifras despues de un exponente
void _cifras_exp_cifras(struct estado *estado){
    if(isdigit(estado->caracter)){
        //devora numeros
        estado->siguiente = _cifras_exp_cifras;
    }else if (estado->caracter == 'i'){
        //si hay una i reconoce un imaginario
        estado->siguiente = NULL;
        estado->nombre = IMAGIN_LIT;
        //la i es parte del imaginario
        estado->es_ultimo_extra = 0;
    }else{
        //si llega cualquier otra cosa reconoce un float
        estado->siguiente = NULL;
        estado->nombre = FLOAT_LIT;
        estado->es_ultimo_extra = 1;
    }
}

// estado privado al  que se llega despues de haber encontrado un +/- despues de un exp
void _cifras_exp_signo(struct estado *estado){
    if(isdigit(estado->caracter)){
        //si hay una cifra => cambio de estado
        estado->siguiente = _cifras_exp_cifras;
    }else{
        /* 
        * un numero no puede acanar en (e|E)(+|-)
        * se reconoce un float mal formado
        */ 
        estado->siguiente = NULL;
        estado->nombre = -1*FLOAT_LIT;
        estado->es_ultimo_extra = 1;
    }
}

//estado privado a la que se llega despues de un "0"("x"|"X")
void _ini_hex(struct estado *estado){
    char c = estado->caracter;
    if (isdigit(c) || ('A'<= c && c<='F') || ('a'<= c && c<='f')){
        //recibir cifra hexadecimal => cambio de estado
        estado->siguiente = _hex;
    }else{
        //si recibe cualquier otra cosa reconoce un Integer mal formado (0X no es lexema valido)
        estado->siguiente = NULL;
        estado->nombre =  -1*INTEGER_LIT;
        estado->es_ultimo_extra = 1;
    }
}

//estado privado para reconocer numeros en exadecimal: se llega despues de "0"("x"|"X")(cifra_hex)
void _hex(struct estado *estado){
    char c = estado->caracter;
    if (isdigit(c) || ('A'<= c && c<='F') || ('a'<= c && c<='f')){
        //devora cifras hexadecimales
        estado->siguiente = _hex;
    }else{
        //cuando hay algo distinto reconoce un integer literal
        estado->siguiente = NULL;
        estado->nombre = INTEGER_LIT;
        estado->es_ultimo_extra = 1;
    }
}



