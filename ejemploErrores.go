package main

import "fmt"

a = 0x //hexadecimal mal formado
b = 1.E+a //float mal formado
c = 1.eb //float mal formado

func sum(s []float32, c chan float32) {
	var sum float32 = 0
	for _, v := range s {
			sum += v
	}
	"Este es un lexema muy largo Este es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largoEste es un lexema muy largo"
	c <- sum // send sum to c
}

/* este 
es un comentario
de bloque que no está cerrado
producira un error