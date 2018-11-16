CFLAGS= -Wall -O2 -Wpedantic -std=c99
CC=gcc
PROG=aventura
${PROG}.out: ${PROG}.o lista.o elemento.o tabSim.o lista_fptr.o
	${CC} -o ${PROG}.out $^

clean:
	rm -f *.o *.out

run:
	./${PROG}.out