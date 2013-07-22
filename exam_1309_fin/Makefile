

all: exam.o procedure.o monitor_sc.o

exam.o: exam.c procedure.o monitor_sc.o
	gcc -o exam_sc exam.c procedure.o monitor_sc.o

procedure.o: procedure.c procedure.h monitor_sc.o
	gcc -c procedure.c

monitor_sc.o: monitor_sc.c monitor.h
	gcc -c monitor_sc.c
      
clean:
	rm -f *.o 
	rm -f *~

