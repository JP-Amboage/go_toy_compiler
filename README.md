# COMPILADORES PRACTICA 1

Práctica probada en ubuntu 20.04. No se garantiza el funcionamiento en sistemas Windows, se esperan códigos .go con retornos de carro tipo UNIX '\n' y no tipo Windows '\r'.

Varios módulos siguen el patrón singleton. Es responsabilidad de quien los use llamar a las funciones que exportan en orden adecuado (inicializar, acciones, cerrar).

## Como Ejecutar el Compilador

1. La primera vez debes compilar el compilador : 
    * Puedes hacerlo ejecutando el comando make en la carpeta del proyecto
    * Esto generará el ejecutable compilador.out

2. Para utilizar el compilador debes ejecutar compilador.out
    * compilador.out recibe como primer argumento el nombre del codigo a compilar: ./compilador.out codigo.go
    * Si no recibe ningún argumento intentará compilar concurrentSum.go (si no existe se produce un error)

## Relatorio de Ficheros
Como ya habrás visto hay un gran número de archivos en la carpeta del proyecto. Esto se debe a que hemos intentado hacer un diseño lo más modular posible. Hay un comentario en cada .c .h indicando la función del módulo. Pero si lo prefieres puedes ver aquí que hay en cada módulo sin tener que abrir todos los archivos.

1. **abb.c/.h** 
    * Librería que proporciona un árbol binario de búsqueda a la tabla de símbolos
    * De la materia Algoritmos y Estructuras de Datos con dos funciones extra: inorden() y buscar_insertar()

2. **ana_lexico.c/.h**
    * Librería encargada de realizar el análisis léxico (patrón singleton)
    * Se apoya en en el módulo autómata para realizar sus tareas de reconocimiento
    * El analizador sintáctico le pide lexemas llamando a siguiente_comp_lexico()

3. **ana_sintactico.c/.h**
    * Librería encargada de realizar el análisis sintáctico (patrón singleton)
    * En este proyecto su labor se reduce a imprimir los lexemas que pide al analizador léxico

4. **automata_alfanum.c/.h**
    * Sub-autómata con estados para el reconocimiento de cadenas alfanuméricas

5. **automata_com.c/.h**
    * Sub-autómata con estados para el reconocimiento de comentarios (bloque/linea)

6. **automata_num.c/.h**
    * Sub-autómata con estados para el reconocimiento de números
    * Soporte para integer / float / imaninary literals **decimales** sin separadores '_' entre cifras. 
    * Soporte para integer literals **hexadecimales** sin separadores '_'

6. **automata_op.c/.h**
    * Sub-autómata con estados para el reconocimiento de operadores que pueden formar parte de un lexema de longitud mayor a 1

6. **automata_str.c/.h**
    * Sub-autómata con estados para el reconocimiento de string literals
    * Soporte para strigns que empiezan por ". Sin implementar todas sus restricciones.

7. **automata.c/.h**
    * Autómata principal
    * Procesa el primer caracter y discrimina hacia el sub-autómata adecuado
    * Exporta el estado inicial 
    * Exporta el struct estado que representa al autómata en cada momento

8. **concurrentSum.go**
    * Código de ejemplo para probar el compilador

9. **definiciones.h**
    * Fichero de definiciones para los componentes léxicos de Go
    * No están todas las palabras reservadas y operadores (si aquellos necesarios para concurrentSum.go)

10. **ejemploErrores.go**
    * Código mal escrito que se puede pasar al compilador para ver en funcionamiento sistema de tratamiento de errores.

11. **errores.c/h**
    * Módulo para notificiación de errores
    * Tratamiento específico para:
        * No se pudo abrir el código a compilar (invocado por el sistema de entrada)
        * Lexema demasiado largo (invocado por el sistema de entrada)
        * Lexema mal formado: un par de casos concretos y tratamiento algo pobre (no se pedía) (invocado por el analizador lexico)
        * Fin de fichero inesperado: avisa de un fin de fichero inesperado durante el reconocimiento de string o comentario de bloque (evita que el compilador no entre en un bucle infinito si hay un comentario de bloque sin cerrar).

12. **main.c**
    * Módulo principal
    * Inicializa y cierra los módulos y pone en marcha el análisis.

13. **makefile**
    * Soporta los comandos make, clean y cleanall

14. **README.md**
    * Documentación

15. **sis_entrada.c/.h**
    * Sistema de entrada (patrón singleton)
    * Proporciona el siguiente carácter leído al analizador léxico

16. **tabla_simbolos.c/.h**
    * Tabla de símbolos (patrón singleton)
    * El analizar léxico interactúa con este módulo que le "oculta" los detalles de implementación de la tabla (en este caso abb.c/.h)

## Atómatas

### Explicación y justificación de los autómatas

Uno de los pilares de este proyecto son los autómatas usados para el reconociento de los componentes léxicos en el código. Para esta tarea se sigue un modelos de máquina de estados en C tanto [eficiente](http://www.conman.org/projects/essays/states.html) como [popular](https://stackoverflow.com/a/1383453).

Esto nos permite, no solo que el compilador funcione bien, si no que también sea fácil para programadores familiarizados con este modelo añadir/modificar los autómatas presentes para reconocimiento de nuevos patrones.

La idea es representar la situación del autómata en cada momento mediante un struct que en su versión genérica puede ser:

```c
struct estado{
    funcion_estado *siguiente;
    char c; // datos
}
```
Donde definimos el tipo funcion_estado como:
```c
typedef void funcion_estado(struct estado *);
```
De esta forma para cada estado del autómata escribiremos una función de tipo:
```c
void estado_cualquiera(struct estado * estado){
    if(estado->c cumple condicion){
        estado->siguiente = otro_estado_cualquiera;

    }else if (estado->c cumple otra condicion){
        estado->siguiente = otro_estado_distinto;

    else if(estado-> permite aceptar){
        estado-> siguiente = NULL; // no hay siguiente
    }
    //etc...
    }else{
        estado->siguiente = otro_estado_distinto;
    }
}
```
Dentro de la función se puede usar cualquier otro método de discriminación en función del carácter. La ventaja de usar if/else frente a switch case es que if/else permite condiciones no constantes (ej: isdigit(estado->c)). Por esta razón en algunos estados del proyecto era mejor usar if/else por lo que se adoptó por este enfoque en prácticamente todos los autómatas por consistencia.

Para poner en marcha el autómata necesitamos un bucle como el siguiente:
```c
struct estado estado;
estado.siguiente=e estado_inicial;

while(estado.siguiente){
    estado.c = siguiente_caracter();
    estado.siguiente(&estado);
}
```

### Ejemplo anadir nuevo autómata.

Como avanzábamos en el apartado anterior, la popularidad de este diseño y la modularidad de su implementación facilitan que sea relativamente sencillo añadir nuevos autómatas. 

En el estado inicial se han añadido 'cases' para caracteres que pueden ser el principio de un operador compuesto para el que aún no hay soporte . Así para dar soporte para los mismos solo hay que rellenar el 'case' correspondiente con código análogo al de operadores compuestos implementados como el '+' (+; +=; ++..) y crear un nuevo estado en el sub-autómata de operadores análogo a los existentes.

El caso de querer añadir un autómata **completamente nuevo** lo ilustraremos con un ejemplo: Alguien que quiere añadir un autómata que reconozca string literals que comiencen por comilla simple deberá:

1. En el fichero del autómata principal **automata.c** añadir un nuevo case 'comilla simple' en el estado inicial para discriminar hacia su nuevo autómata con la sentencia 'estado->siguiente = str_ini_csimple;'. Siguiendo la nomenclatura usada en los autómatas ya implementados donde: 'str' hace referencia al sub-autómata de strings; 'ini' significa que es un estado inicial (se deriva a el desde fuera del sub-autómata y estará en su .h) y 'csimple' haría referencia a que reconoce strings que comienzan por comilla simple.

2. En el fichero **automata_str.h** añadir la línea: 'void str_ini_csimple(struct estado *estado);'

3. En el fichero **automata_str.c** programar la función 'str_ini_csimple' para que en función del valor del carácter que haya en el struct asigne a 'estado->siguiente' el siguiente estado (que debe programar) o 'NULL' en caso de que quiera aceptar el lexe,a. En caso de aceptar también deberá reyenar otros dos campos del struct. Estos son '->nombre' (con el código del lexema) y '->es_ultimo_extra' (0|1 según el carácter usado para aceptar forme parte del lexema en sí o no)


## Gestión de Errores
Para probar el sistema de tratamiento de errores puedes intentar compilar un fichero de código que no exista y el código ejemploErrores.go en el que encontrarás dos float mal formados distintos, un integer hexadecimal mal formado, un lexema demasiado largo y un final de fichero inesperado.

## Trabajo posterior

* Añadir todas las palabras reservadas en definiciones.h y modificar el array al inicio de tabla_simbolos.c para que se pre-inserten en la tabla al inicializarla.

* Añadir reconocimiento de enteros binarios y octales, floats en hexadecimal y el separador '_' entre números.

* Refinar el tratamiento de los errores.
