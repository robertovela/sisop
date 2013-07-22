main : main.o procedure.o
	gcc -o magazzino main.o procedure.o ./monitor/monitor.o

main.o : main.c header.h ./monitor/monitor.h
	gcc -c main.c

procedure.o : procedure.c header.h ./monitor/monitor.h
	gcc -c procedure.c

clean :
	rm -f *.o
	rm -f magazzino 
