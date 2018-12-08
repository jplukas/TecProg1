LOADLIBES= -lfl -lreadline
CFLAGS=-Wall -g

%.c: %.y
	bison $<
	mv $*.tab.c $*.c

avent: elemento.o main.o avent.o aventl.o coisas.o tabSim.o lista_fptr.o lista.o

avent.c : avent.y

aventl.o: aventl.l avent.c

clean:
	rm -f avent avent.tab* *.o *~ avent.c avent.tgz aventl.*

dist:
	tar czf avent.tgz aventl.l avent.y coisas.c coisas.h main.c tabSim.c tabSim.h lista.o lista.h lista_fptr.o lista_fptr.h Makefile
