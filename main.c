#include <stdlib.h>
#include <stdio.h>
#include "ana_sintactico.h"
#include "tabla_simbolos.h"
#include "sis_entrada.h"
#include "ana_lexico.h"

int main(int argc, char** argv){
    char *codigo = NULL;
    /*
    * Procesamiento de los argumentos de entrada
    */
    if(argc == 1){
        printf("-> No se ha proporcionado ningun argumento:\n");
        printf("-> Se tomará el archivo por defecto.\n");
        codigo = "./concurrentSum.go";
    }else{
        codigo = argv[1];
        if(argc !=2){
            printf("-> Se han proporcionado demasiados argumentos:\n");
            printf("-> Se tomará el primero de ellos como fichero a analizar.\n");
        }
    }
    printf("-> Codigo a analizar: [%s]\n",codigo);

    /*
    * Inicializacion de modulos 
    */
    //si no se abrio el sistema de entrada se aborta la ejecucion
    //es responsabilidad del sistema de entrada llamar a error
    if(inicializar_sis_entrada(codigo)<0) return -1;
    inicializar_tabla();
    inicializar_ana_lex();
    inicializar_ana_sintactico();

    /*
    * Impresion de la tabla de simbolos
    */
    print_tabla();
    
    /*
    * Fase de analisis
    */

    printf("\n========= INICIO ANALISIS =========\n");
    comenzar_analisis_sintactico();
    printf("========== FIN ANALISIS ===========\n\n");

    /*
    * Impresion de la tabla de simbolos
    */
    print_tabla();
    
    /*
    * Cierre de modulos
    */
    cerrar_ana_sintactico();
    cerrar_ana_lex();
    borrar_tabla();
    cerrar_sis_entrada();
    return 0;
}