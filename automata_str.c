#include "automata_str.h"
#include <stdlib.h>
#include <stdio.h>
#include "errores.h"

/*
* SUB-AUTOMATA PARA RECONOCER STRINGS
* Solo reconoce strings que empiezan por "
* Para las strings que empiexan por ` habria que replicar
* estos mismos estados substitutendo " por `en los if
*/


void _escape(struct estado *estado);

/*
*  Estado inicial del subautomata al que se llega depues
* de que el automata principal procese "
*/
void str_ini(struct estado *estado){
    if(estado->caracter == '\"'){
        //si se reciben otras comillas "cierra" el string y acaba
        estado->siguiente = NULL;
        estado->nombre = STR_LIT;
        estado->es_ultimo_extra = 0;
    }else if(estado->caracter == '\\'){
        //si se encuentra un escape cambia de estado
        estado->siguiente = _escape;
    }else if(estado->caracter == EOF){
        //si se ecuentra EOF el string acaba de forma inesperada
        avisar_error(UNEXPECTED_EOF,"Parece que te ha quedado un string sin cerrar");
        estado->siguiente = NULL;
        estado->nombre = -1*STR_LIT;
        estado->es_ultimo_extra = 1;
    }else{//devora caracteres
        estado->siguiente = str_ini;
    }
}

//estado al que se llega despues de un escape
void _escape(struct estado *estado){
    if(estado->caracter!=EOF){
        //ignora el caracter que hay despues del escape
        estado->siguiente = str_ini;
    }else{
        //si se ecuentra EOF el string acaba de forma inesperada
        avisar_error(UNEXPECTED_EOF,"Parece que te ha quedado un string sin cerrar");
        estado->siguiente = NULL;
        estado->nombre = -1*STR_LIT;
        estado->es_ultimo_extra = 1;
    }
}