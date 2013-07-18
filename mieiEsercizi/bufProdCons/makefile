all: prod_cons

prod_cons: prod_cons.o procedure.o
	gcc -o start prod_cons.o procedure.o

prod_cons.o: prod_cons.c header.h
	gcc -c prod_cons.c

procedure.o: procedure.c header.h
	gcc -c procedure.c

clean:
	 rm -f *.o 
	rm -f ./start
	rm -f *.kdev*
	rm -f *~
