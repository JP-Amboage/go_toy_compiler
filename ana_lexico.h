#ifndef ANA_LEX_H
#define ANA_LEX_H

/*
* ANALIZADOR LEXICO (singleton)
*/

/*
* Estructura componente lexico que almacena
* El código del componente léxico (id)
* La cadena de texto correspondiente con dicho componente en el código (lexema)
*/
typedef struct {
    int id;
    char* lexema;
} comp_lexico;

/**
* Función de producción que invoca el analizador sintáctico
* Para pedir el siguiente componente léxico
* Devuelve un puntero a comp_lexico reservado dinámicamente 
* cuya propiedad pasa a ser de quién invoque la función
*(ie es responsable de liberar la struct y sus campos)
*/
comp_lexico* siguiente_comp_lexico();

/**
* Inicializacion (singleton)
*/
void inicializar_ana_lex();

/**
* Cierre (singleton)
*/ 
void cerrar_ana_lex();


#endif
