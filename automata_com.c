#include "automata_com.h"
#include <stdlib.h>
#include <stdio.h>
#include "errores.h"
/*
* SUB-AUTOMATA PARA RECONOCER COMENTARIOS
*/

void _coment_bloque_fin(struct estado *estado);

//estado inicial del sub-automata para comentarios de linea (ya se proceso //)
void coment_ini_linea(struct estado *estado){
    //el comentario acaba cuando llega a un salto de linea
    if(estado->caracter=='\n' || estado->caracter == EOF){
        estado->siguiente = NULL;
        estado->nombre = COMENTARIO;
        //el salto de linea no es parte del comentario
        estado->es_ultimo_extra = 1;
    }else{
        estado->siguiente=coment_ini_linea;
    }
}

//estado inicial del sub-automata para comentarios de bloque (ya se proceso /*)
void coment_ini_bloque(struct estado *estado){
    //la llegada de '*' puede indicar el principio del final => cambio de estado
    if(estado->caracter=='*'){ 
        estado->siguiente = _coment_bloque_fin;
    }else if(estado->caracter==EOF){ 
        //si ecuentra EOF TERMINA EL COMENTARIO
        avisar_error(UNEXPECTED_EOF,"Debes cerrar un comentario de bloque con */ antes del fin del fichero");
        estado->siguiente = NULL;
        estado->nombre = COMENTARIO;
        estado->es_ultimo_extra=0;
    }else{
        //devora caracteres
        estado->siguiente=coment_ini_bloque;
    }
}

//estado privado de comentario de bloque al que se llega despues de un '*'
void _coment_bloque_fin(struct estado *estado){
    // '*/' indica el fin del comentario de bloque
    if(estado->caracter=='/'){
        estado->siguiente = NULL;
        estado->nombre = COMENTARIO;
        //el / que cierra el comentario de bloque es parte del mismo
        estado->es_ultimo_extra=0;
    }else if(estado->caracter==EOF){ 
        //si ecuentra EOF TERMINA EL COMENTARIO
        avisar_error(UNEXPECTED_EOF,"Debes cerrar un comentario de bloque con */ antes del fin del fichero");
        estado->siguiente = NULL;
        estado->nombre = COMENTARIO;
        estado->es_ultimo_extra=0;
    }else{
        //si despues del '*' no hay '/' el comentario de bloque sigue
        estado->siguiente=coment_ini_bloque;
    }
}