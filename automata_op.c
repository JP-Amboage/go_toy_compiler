#include "automata_op.h"
#include <stdlib.h>


/*
* SUB-AUTOMATA PARA RECONOCER OPERADORES que puedan tener más de un caracter
* (ej: +=, ++, +, -=, <, <-...)
*/

/*
* Funcion de estado inicial para reconocer operadores que empiezan por ":"
* Se llega a el cuando el automata general ha procesado ":" 
*/
void op_ini_dospuntos(struct estado *estado){
    //siempre acaba (i.e. no hay siguiente)
    estado->siguiente = NULL;
    if (estado->caracter == '='){ //:=
        //despues de : viene un =
        estado->nombre = DOS_PUNTOS_IGUAL;
        estado->es_ultimo_extra = 0;
    }else{ 
        //despues de : no viene un =
        //reconoce simplemente :
        estado->nombre = ':';
        estado->es_ultimo_extra = 1;
    }
}

/*
* Funcion de estado inicial para reconocer operadores que empiezan por "+"
* Se llega a el cuando el automata general ha procesado "+" 
*/
void op_ini_mas(struct estado *estado){
    //siempre acaba (i.e. no hay siguiente)
    estado->siguiente = NULL;
    if (estado->caracter == '='){ //+=
        //despues del + viene un =
        estado->nombre = MAS_IGUAL;
        estado->es_ultimo_extra = 0;
    }else if(estado->caracter == '+'){ //++
        //despues del + viene un +
        estado->nombre = MAS_MAS;
        estado->es_ultimo_extra = 0;
    }else{
        //en otro caso se reconoce un + simple
        estado->nombre = '+';
        estado->es_ultimo_extra = 1;
    }
}

/*
* Funcion de estado inicial para reconocer operadores que empiezan por "-"
* Se llega a el cuando el automata general ha procesado "-" 
*/
void op_ini_guion(struct estado *estado){
    //siempre acaba (i.e. no hay siguiente)
    estado->siguiente = NULL;
    if (estado->caracter == '='){ //-=
        //despues del - vino un =
        estado->nombre = MENOS_IGUAL;
        estado->es_ultimo_extra = 0;
    }else if(estado->caracter == '>'){ //->
        //despues del - vino un >
        estado->nombre = GUION_MAYOR;
        estado->es_ultimo_extra = 0;
    }else if(estado->caracter == '-'){ //--
        //despues del - vino un -
        estado->nombre = MENOS_MENOS;
        estado->es_ultimo_extra = 0;
    }else{
        //en otro caso reconoce un - simple
        estado->nombre = '-';
        estado->es_ultimo_extra = 1;
    }
}

/*
* Funcion de estado inicial para reconocer operadores que empiezan por "<"
* Se llega a el cuando el automata general ha procesado "<" 
*/
void op_ini_menor(struct estado *estado){
    //siempre acaba (i.e. no hay siguiente)
    estado->siguiente = NULL;
    if (estado->caracter == '='){ //<=
        //despues de < vino =
        estado->nombre = MENOR_IGUAL;
        estado->es_ultimo_extra = 0;
    }else if(estado->caracter == '<'){ //<<
        //despues de < vino <
        estado->nombre = MENOR_MENOR;
        estado->es_ultimo_extra = 0;
    }else if(estado->caracter == '-'){ //<-
        //despues de < vino -
        estado->nombre = MENOR_GUION;
        estado->es_ultimo_extra = 0;
    }else{
        //en otro caso es el operador < simle
        estado->nombre = '<';
        estado->es_ultimo_extra = 1;
    }
}

/*
* Funcion de estado inicial para reconocer operadores que empiezan por ".."
* Se llega a el cuando el automata general ha procesado ".." 
*/
void op_ini_pp(struct estado *estado){
    //siempre acaba (i.e. no hay estado siguiente)
    estado->siguiente = NULL;
    if (estado->caracter == '.'){
        estado->nombre = TRES_PUNTOS;
        estado->es_ultimo_extra = 0;
    }else{
        //mal formado no puede haber ".." nunca
        estado->nombre = -1* TRES_PUNTOS;
        estado->es_ultimo_extra = 1;
    }
}


