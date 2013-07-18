start: procedure.o lettScritt.o
	gcc -o start procedure.o lettScritt.o
lettScritt.o: lettScritt.c header.h
	gcc -c lettScritt.c
procedure.o: procedure.c header.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f start
