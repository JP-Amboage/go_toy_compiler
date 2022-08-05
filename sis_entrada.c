#include <stdio.h>
#include <stdlib.h>
#include "sis_entrada.h"
#include "errores.h"

/*
* SISTEMA DE ENTRADA (singleton)
*/

//tamano del buffer
#define TAM_BUFFER 64

FILE* codigo = NULL;
//doble buffer con un espacio extra al final para EOF
char buffer[2][TAM_BUFFER+1];

//longitud leida
/*
* Necesario un contador de longitud por si se excede el tamano maximo
* Permite prescindir de "inicio" en el par "inicio"/"delantero"
*/
int len = -1;

//indice que indica la posicion en el buffer
int delantero = -1;

//incica qen que buffer estamos (0|1 una vez inicializada)
int actual = -1;

//indica si el siguiente buffer esta cargado (0|1 una vez inicializada)
int siguiente_cargado = -1; 

//indica si se ha acabado de leer el fichero
int fin = 0;


int _leer_bloque(char* bloque);

//inicializa el sistema de entrada y abre el fichero del codigo
int inicializar_sis_entrada(char* filename){
    //se ya se cargo el codigo aborta
    if(codigo != NULL) return -1;
    //abre el codigo en moddo lectura
    codigo = fopen(filename, "r");
    if (codigo == NULL){
        avisar_error(NO_ABRIO_CODIGO, filename);
        return -1;
    }
    //coloca los centinelas
    buffer[0][TAM_BUFFER] = EOF;
    buffer[1][TAM_BUFFER] = EOF;
    //carga el primer bloque
    _leer_bloque(buffer[0]);
    //inicializa demas variables
    len = 0;
    delantero = 0;
    siguiente_cargado = 0; 
    actual = 0;
    return 0;
}

//cierra el sistema de entrada
int cerrar_sis_entrada(){
    //reestablece valores de las variables
    len = -1;
    delantero = -1;
    siguiente_cargado = -1; 
    actual = -1;
    //cierra el fichero
    if(fclose(codigo)){
        avisar_error(0, "Algo ha ido mal al cerrar el fichero");
        return -1;
    } 
    codigo = NULL;
    return 0;
}

//funcion auxiliar privada para leer un bloque
int _leer_bloque(char* bloque){
    int leidos = fread(bloque, sizeof(char), TAM_BUFFER, codigo);
    //se se leen caracteres de menos se coloca un EOF al final
    if(leidos < TAM_BUFFER) bloque[leidos] = EOF;
    return leidos;
}

//funcion que devuelve el siguienre caracter
char siguiente_caracter(){
    char c = buffer[actual][delantero];
    
    if (c == EOF){//si estamos en EOF
        if(delantero == TAM_BUFFER){
	        //si es uno de los centinelas hacemos el cambio de buffer
            delantero = 0;
            actual = !actual;
            if(!siguiente_cargado) _leer_bloque(buffer[actual]);
            siguiente_cargado = 0;
            c = buffer[actual][delantero];
	    }else{
            // si ya hemos registrado el fin devuelve EOF
            if(fin) return EOF;
            //si no pone el siguiente a EOF y registra el fin
            buffer[actual][delantero+1] = EOF;
	        fin = 1;	
        }   
    }
    //desplazamos delantero e incrementamos la longitud
    delantero++;
    len ++;
    return c;
}

//funcion que para ignorar un lexema
void ignorar(){
    len = 0;
}

//funcion que devuelve el ultimo lexema (desde delantero hacia atras)
char* pedir_ultimo_lexema(){
    char* lexema;
    //despues de leer un caracter avanza delantero por lo que el tam maximo
    // del lexema es TAM_BUFFER
    int demasiado_largo = (len>TAM_BUFFER);
    
    //si es demasiado largo truncamos
    if (demasiado_largo) len = TAM_BUFFER;

    //reserva de memoria contando con el caracter de fin de cadena
    lexema = (char*) malloc(sizeof(char)*len +1);
    if(lexema == NULL) return NULL;
    lexema[len] = '\0';
    
    //inicializamos buffer actual y caracter actual en
    int b_actual = actual;
    int c_actual = delantero;
    
    //de delantero hacia atras
    for(int i = len -1; i >= 0; i--){
        //si estamos al ppio de un buffer saltamos al fin del otro
        if(c_actual == 0){
            c_actual = TAM_BUFFER -1;
            b_actual = !b_actual;
        }else{
            c_actual--;
        }
        //introducimos el caracter
        lexema[i] = buffer[b_actual][c_actual];
    }

    if(demasiado_largo) avisar_error(LEXEMA_LARGO, lexema);
   
    ignorar(); //establece len a 0
    return lexema;
}

//retrocede un caracter
int devolver_caracter(){
    if(delantero==0){ //estando al principio de un buffer
        //no es posible retroceder mas si ya se sobreescribio
        if(siguiente_cargado) return -1;
        //saltamos de buffer
        delantero = TAM_BUFFER -1;
        actual = !actual;
        siguiente_cargado = 1;
    }else{
        delantero--;
    }
    //reducimos la longitud
    len --;
    return 1;
}
