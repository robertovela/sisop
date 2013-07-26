all: start docente studente

start: main.o procedure.o
	gcc -o start main.o procedure.o
docente: docente.o procedure.o
	gcc -o docente docente.o procedure.o
studente: studente.o procedure.o
	gcc -o studente studente.o procedure.o

main.o: main.c header.h
	gcc -c main.c
procedure.o: procedure.c header.h
	gcc -c procedure.c
docente.o: docente.c header.h
	gcc -c docente.c
studente.o: studente.c header.h
	gcc -c studente.c

clean:
	rm -f *.o
	rm -f ./start
	rm -f ./docente
	rm -f ./studente
	rm -f *~
	
