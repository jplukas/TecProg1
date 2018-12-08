LOADLIBES= -lfl -lreadline
CFLAGS=-Wall -Wpedantic -O2 -std=c99 -g

%.c: %.y
	bison $<
	mv $*.tab.c $*.c

avent: main.o avent.o aventl.o coisas.o tabsim.o lista_fptr.o lista.o

avent.c : avent.y

aventl.o: aventl.l avent.c

clean:
	rm -f avent *tab* *.o *~ avent.c avent.tgz

dist:
	tar czf avent.tgz aventl.l avent.y coisas.c coisas.h main.c tabsim.c tabsim.h lista.o lista.h lista_fptr.o lista_fptr.h Makefile
