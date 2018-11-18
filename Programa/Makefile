CFLAGS= -Wall -Wpedantic -O2 -std=c99 -g
CC=gcc
PROG=aventura
${PROG}.out: ${PROG}.o lista.o elemento.o tabSim.o lista_fptr.o libgame.o
	${CC} -o ${PROG}.out $^

clean:
	rm -f *.o *.out

run:
	./${PROG}.out

debug:
	valgrind ./${PROG}.out --leak-check=full --track-origins=yes 
