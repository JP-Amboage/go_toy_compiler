#ifndef ERRORES_H
#define ERRORES_H

/*
* Sistema de notificacion de errores
*/

/*
* Codigos de error
*/
#define NO_ABRIO_CODIGO 1001
#define MAL_FORMADO 33333
#define LEXEMA_LARGO 44444
#define UNEXPECTED_EOF 55555

/**
* Funcion para notificar un error (imprimira un aviso)
* @param error codigo del error
* @param info puntero a void con informacion relativa al error
* para un uso correcto de la funcion sus posibles valores son o bien NULL o 
* char* -> para el error NO_ABRIO_CODIGO;
* comp_lexico* -> para el error MAL_FORMADO;
* char* -> para el error LEXEMA_LARGO;
* char* -> para un codigo de error no definido
*/
void avisar_error(int error , void* info);

#endif