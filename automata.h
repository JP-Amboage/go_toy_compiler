#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "definiciones.h"

/*
* Libreria del autómata principal: procesa el/los primeros caracteres
* hasta que puede delegar el reconocimiento en algún sub-autómata.
*/


struct estado;

typedef void fn_estado(struct estado *);

/*
* Estructura estado que representa al automata
* fn_estado: funcion del estado que procesara la siguiente entrada
*            NULL cuando se ha aceptado y por lo tanto no hay siguiente. 
*
* caracter: ultimo caracter recibido por el automata.
*
* nombre: codigo del comp lexico reconocido (se establece al final)
*        "- CODIGO_LEXEMA" indica que el lexema está mal formado.
*
* es_ultimo_extra: indica si la ultima entrada usada para reconocer
*                  el lexema es parte del mismo.
*/
struct estado{
    fn_estado * siguiente;
    char caracter; 
    int nombre; 
    int es_ultimo_extra; 
};

/**
* Funcion de estado INICIAL procesa el primer caracter
* decide en función del mismo que sub-autómata será el adecuado
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/ 
void inicial(struct estado *estado);

#endif