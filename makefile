CC = gcc -Wall -std=c11
LIBS = -lm
MAIN= compilador.out

SRCS = main.c ana_lexico.c ana_sintactico.c abb.c tabla_simbolos.c automata_alfanum.c automata_com.c automata_num.c automata_op.c automata_str.c automata.c sis_entrada.c errores.c

DEPS = ana_lexico.h ana_sintactico.h abb.h tabla_simbolos.h tabla_simbolos.h automata_alfanum.h automata_com.h automata_num.h automata_op.h automata_str.h automata.h definiciones.h sis_entrada.h errores.h

OBJS = $(SRCS:.c=.o)

$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) $(LIBS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

cleanall: clean
	rm -f $(MAIN)

clean:
	rm -f *.o *.~w