#ifndef SISTEMA_ENTRADA_H
#define SISTEMA_ENTRADA_H

/*
* SISTEMA DE ENTRADA (singleton)
*/

/**
* Funcion que usa el analizador lexico
* para pedir el siguiente caracter del codigo
*/
char siguiente_caracter();

/**
* Funcion que usa al analizador lexico 
* para "des-consumir" un caracter
* devuelve un valor negativo si no se pudo realizar la operacion
*/
int devolver_caracter();

/**
* Funcion que usa al analizador lexico 
* para pedir el ultimo lexema al sistema de entrada que este devuelve como una dirección
* de memoria reservada de forma dinámica, es responsabilidad de quien lo invoca liberarla
*/
char* pedir_ultimo_lexema();

/**
* Funcion para inicializar el sistema de entrada y abrir el fichero con el cofigo
* @param filename nombre del fichero con el codigo
* devuelve un valor negativo si la operacion no se realiza son exito
*/
int inicializar_sis_entrada(char* filename);

/**
* Funcion que usa al analizador lexico 
* para "ignorar" los ultimos caracteres leidos, por ejemplo:
* se ignoran comentarios o espacios.
*/
void ignorar();

/**
* Funcion para cerrar el sistema de entrada y  el fichero con el codigo
* devuelve un valor negativo si la operacion no se realiza son exito
*/
int cerrar_sis_entrada();

#endif
