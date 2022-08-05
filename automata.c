#include "automata_alfanum.h"
#include "automata_num.h"
#include "automata_op.h"
#include "automata_com.h"
#include "automata_str.h"
#include <ctype.h>
#include <stdlib.h>

/*
* AUTOMATA PRINCIPAL
* elige a que sub-automata derivar en 
* en funcion de los minimos caracteres leidos posibles casi siempre
* puede derivar a un sub-automata despues del primer caracter.  Pero hay casos como
* al recibir un . en que no (podria ser el inicio de un numero o un operador )
*/

void _punto(struct estado *estado);
void _diagonal(struct estado *estado);

/*
* Estado inicial que procesa el primer caracter de TODOS los lexemas
*/
void inicial(struct estado *estado){
    char c = estado->caracter;
    
    if('1'<=c && c<='9'){ // no puede ir en switch case (solo valen ctes)
        
        //deriva al subautomata de numeros
        estado->siguiente = num_ini_1_9;

    }else if(isalpha(c) || c == '_'){// no puede ir en switch case (solo valen ctes)
        
        //deriva al subautomata de cadenas alfanum
        estado->siguiente = alfanum_ini;

    }else{

        switch (c){
        case '0':
            //deriva al subautomata de numeros
            estado->siguiente = num_ini_0;
            break;
        case '\"':
            //deriva al subautomata de strings
            estado->siguiente = str_ini;
            break;
        case '.':
            //aun no puede discrminar
            //deriva a un estado privado
            estado->siguiente = _punto;
            break;
        case ':':
            //deriva al sub-automata de operadores
            estado->siguiente = op_ini_dospuntos;
            break;
        case '=':
            //necesitaria otro tratamiento porque existe ==
            //debería derivar a un estado propio en ell sub-automata de operadores
            estado->siguiente = NULL;
            estado->nombre = c;
            estado->es_ultimo_extra = 0;
            break;
        case '!':
            //necesitaria otro tratamiento porque existe !=
            //debería derivar a un estado propio en ell sub-automata de operadores
            estado->siguiente = NULL;
            estado->nombre = c;
            estado->es_ultimo_extra = 0;
            break;
        case '+':
            //deriva al sub-automata de operadores
            estado->siguiente = op_ini_mas;
            break;
        case '-':
            //deriva al subautomata de operadores
            estado->siguiente = op_ini_guion;
            break;
        case '*':
            //necesitaria otro tratamiento porque existe *=
            //debería derivar a un estado propio en ell sub-automata de operadores
            estado->siguiente = NULL;
            estado->es_ultimo_extra = 0;
            estado->nombre = c;
            break;
        case '/':
            //con una barra / no puede discriminar todavía 
            //pasa a un estado interno
            estado->siguiente = _diagonal;
            break;
        case '%':
            //necesitaria otro tratamiento porque existe %=
            //debería derivar a un estado propio en ell sub-automata de operadores
            estado->siguiente = NULL;
            estado->nombre = c;
            estado->es_ultimo_extra = 0;
            break;
        case '|':
            //necesitaria otro tratamiento porque existen |= y ||
            //debería derivar a un estado propio en ell sub-automata de operadores
            estado->siguiente = NULL;
            estado->nombre = c;
            estado->es_ultimo_extra = 0;
            break;
        case '&':
            //necesitaria otro tratamiento porque existen &= y &&
            //debería derivar a un estado propio en ell sub-automata de operadores
            estado->siguiente = NULL;
            estado->nombre = c;
            estado->es_ultimo_extra = 0;
        case '^':
            //necesitaria otro tratamiento porque existe ^=
            //debería derivar a un estado propio en ell sub-automata de operadores
            estado->siguiente = NULL;
            estado->nombre = c;
            estado->es_ultimo_extra = 0;
            break;
        case '>':
            //necesitaria otro tratamiento porque existe >>
            //debería derivar a un estado propio en ell sub-automata de operadores
            estado->siguiente = NULL;
            estado->nombre = c;
            estado->es_ultimo_extra = 0;
            break;
        case '<':
            //deriva al subautomata de operadores
            estado->siguiente = op_ini_menor;
            break;
        default: 
            //se procesan y reconocen aqui lexemas de un solo caracter (ej: "[","{","\n"... )
            estado->siguiente = NULL;
            estado->nombre = c;
            estado->es_ultimo_extra = 0;
            break;
        }
    }
}

//estado interno al que se llega despues de procesar "/"
void _diagonal(struct estado *estado){
    switch (estado->caracter){
    case '/':
        // Deriva al subautomata de comentarios (// comentario de linea)
        estado->siguiente=coment_ini_linea;
        break;
    case '*':
        // Deriva al subautomata de comentarios (/ asterisco comentario de bloque)
        estado->siguiente=coment_ini_bloque;
        break;
    default:
        //reconoce el operador /
        estado->siguiente = NULL;
        estado->nombre = estado->caracter;
        //utilizo un caracter extra para reconocer
        estado->es_ultimo_extra = 1;
        break;
    }
}

//estado interno al que se llega despues de procesar "."
void _punto(struct estado *estado){
    if(isdigit(estado->caracter)){
        //si hay .(cifra) deriva al automata de numeros
        estado->siguiente = num_ini_punto_cifra;
    }else if(estado->caracter == '.'){
        //si hay .. deriva al automata de operadores 
        estado->siguiente = op_ini_pp;
    }else{
        //reconoce el operador simple
        estado->siguiente = NULL;
        estado->nombre = '.';
        //utilizo un caracter extra para reconocer
        estado->es_ultimo_extra = 1;
    }
}