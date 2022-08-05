#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

/*
* TABLA DE SIMBOLOS (singleton)
*/

#include "definiciones.h"

/**
* Funcion que busca en la tabla de simbolos la cadena de texto
* lexema. Si está devuelve su código. Si no está la inserta
* y le asigna el codigo correspondiente a los identificadores
* @param lexema cadena de texto a buscar/insertar
*/
int buscar_comp_lexico(char *lexema);

/**
* Funcion para inicializar la tabla
*/
void inicializar_tabla();

/**
* Funcion para imprimir la tabla (en orden alfabetico)
*/
void print_tabla();

/**
* Funcion para borrar la tabla 
*/
void borrar_tabla();

#endif