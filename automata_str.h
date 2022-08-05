#ifndef AUTOMATA_STRINGS_H
#define AUTOMATA_STRINGS_H

#include "automata.h"

/*
* SUB-AUTOMATA PARA RECONOCER STRINGS
*/

/*
* Por el momento solo procesa string literals que comienzan por "
* Para reconocer string literals con otros comienzos habría que 
* anadir nuevos estados iniciales (uno por cada comienzo admitido)
*/

/**
* Funcion de estado inicial para reconocer string literals
* Se llega a el cuando el automata general ha procesado "
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void str_ini(struct estado *estado);

#endif