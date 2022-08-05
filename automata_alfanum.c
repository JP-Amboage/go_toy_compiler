#include <ctype.h>
#include <stdlib.h>
#include "automata.h"
#include "definiciones.h"

/*
* SUB-AUTOMATA PARA RECONOCER CADENAS ALFANUMERICAS (palabras clave + identificadores)
*/

//estado inicial del sub-automata alfanumerico (ver .h)
void alfanum_ini(struct estado *estado){
    //si la entrada es alfanumerica ('_' es una letra en go) el siguiente estado es este mismo
    if(isdigit(estado->caracter) || isalpha(estado->caracter) || estado->caracter == '_'){
        estado->siguiente = alfanum_ini;
    }else{
        //cuando se encuentra una entrada no alfanumerica termina el reconocimiento
        estado->siguiente = NULL;
        estado->nombre = IDENTIFIER;
        //el ultimo caracter procesado no es parte del lexema
        estado->es_ultimo_extra = 1; 
    }
}