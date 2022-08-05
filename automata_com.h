#ifndef AUTOMATA_COMENTARIOS_H
#define AUTOMATA_COMENTARIOS_H

/*
* SUB-AUTOMATA PARA RECONOCER COMENTARIOS
*/

#include "automata.h"

/**
* Funcion de estado inicial para reconocer comentarios de linea 
* Se llega a el cuando el automata general ha procesado "//"
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void coment_ini_bloque(struct estado *estado);

/**
* Funcion de estado inicial para reconocer comentarios de bloque 
* Se llega a el cuando el automata general ha procesado "diagonal asterisco"
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void coment_ini_linea(struct estado *estado);

#endif