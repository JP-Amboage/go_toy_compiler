#ifndef AUTOMATA_OPERADORES_H
#define AUTOMATA_OPERADORES_H

#include "automata.h"

/*
* SUB-AUTOMATA PARA RECONOCER OPERADORES
*
* Muchos operadores y signos de puntuación son reconocidos 
* directamente por el automata general (ej: "{", ",", "~" )
* este sub-autómata se encarga de reconocer aquellos para los que 
* se necesita procesar más caracteres para decidir (ej: "-", "--", "-=")
*/

/**
* Funcion de estado inicial para reconocer operadores que comienzan por ":"
* Se llega a el cuando el automata general ha procesado ":"
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void op_ini_dospuntos(struct estado *estado);

/**
* Funcion de estado inicial para reconocer operadores que comienzan por "+"
* Se llega a el cuando el automata general ha procesado "+"
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void op_ini_mas(struct estado *estado);

/**
* Funcion de estado inicial para reconocer operadores que comienzan por "-"
* Se llega a el cuando el automata general ha procesado "-"
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void op_ini_guion(struct estado *estado);

/**
* Funcion de estado inicial para reconocer operadores que comienzan por "<"
* Se llega a el cuando el automata general ha procesado "<"
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void op_ini_menor(struct estado *estado);

/**
* Funcion de estado inicial para reconocer operadores que comienzan por ".."
* Se llega a el cuando el automata general ha procesado ".."
* @param estado puntero al struct estado que "representa" al automata
* cuyos valores deberá actualizar en función del carácter que contenga
*/
void op_ini_pp(struct estado *estado);

#endif