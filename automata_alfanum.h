#ifndef AUTOMATA_ALFANUM_H
#define AUTOMATA_ALFANUM_H

#include "automata.h"

/*
* SUB-AUTOMATA PARA RECONOCER CADENAS ALFANUMERICAS (palabras clave + identificadores)
*/

/**
* Funcion de estado inicial del automata alfanumerico 
* Se llega a el cuando el automata general ha procesado 
* una 'letra' de go: unicode_letter | "_"
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void alfanum_ini(struct estado *estado);

#endif