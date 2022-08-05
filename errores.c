#include <stdlib.h>
#include <stdio.h>
#include "errores.h"
#include "ana_lexico.h"
#include "definiciones.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*
* Funcion que avisa de los errores
* Los cast de void* no son seguros => Es responsabilidad de quien use el modulo 
* usar el parametro info tal y como se indica en el .h
*/

void avisar_error(int error , void* info){
    switch (error){
        case NO_ABRIO_CODIGO:
            printf(ANSI_COLOR_RED"[ERROR: %d]"ANSI_COLOR_CYAN"-> No se pudo abrir el codigo a analizar\n"ANSI_COLOR_RESET,error);
            if (info != NULL) printf(ANSI_COLOR_CYAN"\t-> El fichero [%s] no existe o no tienes los permisos adecuados\n"ANSI_COLOR_RESET,(char*) info);
        break;
        case LEXEMA_LARGO:
            printf(ANSI_COLOR_MAGENTA"[WARNING: %d]"ANSI_COLOR_CYAN"-> Lexema demasiado largo\n"ANSI_COLOR_RESET, error);
            if (info != NULL) printf(ANSI_COLOR_CYAN"\t-> Solo se ha guardado [%s]\n"ANSI_COLOR_RESET, (char*) info);
        break;
        case UNEXPECTED_EOF:
            printf(ANSI_COLOR_RED"[ERROR: %d]"ANSI_COLOR_CYAN"-> FIN DE FICHERO INESPERADO\n"ANSI_COLOR_RESET, error);
            if (info != NULL) printf(ANSI_COLOR_CYAN"\t-> %s\n"ANSI_COLOR_RESET, (char*) info);
        break;
        case MAL_FORMADO:
            printf(ANSI_COLOR_RED"[ERROR: %d]"ANSI_COLOR_CYAN"-> Lexema mal formado\n"ANSI_COLOR_RESET, error);
            if(info == NULL) return;
            comp_lexico *comp = (comp_lexico*) info;
            char *nombre_comp, *sugerencia = NULL;
            /*
            * habria que anadir un case para cada componente lexico. De momento: 
            * implementado para aquellos para los que hay capacidad de reconocer malformados.
            */
            switch (comp->id){
                case TRES_PUNTOS:
                    nombre_comp = "operador";
                    sugerencia = ".";
                break;
                case FLOAT_LIT:
                    nombre_comp = "float literal";
                    sugerencia = "<numero>";
                break;
                case INTEGER_LIT:
                    nombre_comp = "integer literal";
                    sugerencia = "<numero>";
                break;
                case COMENTARIO:
                    nombre_comp = "comentario";
                    sugerencia = "*/";
                break;
                case STR_LIT:
                    nombre_comp = "string literal";
                    sugerencia = "\"";
                break;
                default:
                nombre_comp = "lexema";
                break;
            }
        printf(ANSI_COLOR_CYAN"\t-> [%s] no es un %s valido!\n"ANSI_COLOR_RESET, comp->lexema, nombre_comp);
        if(sugerencia) printf(ANSI_COLOR_CYAN"\t-> Tal vez querias escribir [%s%s]\n"ANSI_COLOR_RESET, comp->lexema, sugerencia);
    break;
    default:
        printf(ANSI_COLOR_RED"[ERROR:%d]"ANSI_COLOR_CYAN"-> Desconocido\n"ANSI_COLOR_RESET, error);
        if (info != NULL) printf(ANSI_COLOR_CYAN"\t %s\n"ANSI_COLOR_RESET, (char*) info);
        break;
    }
}