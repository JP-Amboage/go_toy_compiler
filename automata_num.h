#ifndef AUTOMATA_NUMEROS_H
#define AUTOMATA_NUMEROS_H

#include "automata.h"

/*
* SUB-AUTOMATA PARA RECONOCER NUMEROS (ej: entero decimal/hexadecimal; float; imaginarios)
*/


/**
* Funcion de estado inicial para reconocer literales numericos
* Se llega a el cuando el automata general ha procesado "1" … "9" 
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void num_ini_1_9(struct estado *estado);

/**
* Funcion de estado inicial para reconocer literales numericos
* Se llega a el cuando el automata general ha procesado "0"
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void num_ini_0(struct estado *estado);

/**
* Funcion de estado inicial para reconocer literales numericos
* Se llega a el cuando el automata general ha procesado "." "0" … "9" 
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void num_ini_punto_cifra(struct estado *estado);

#endif