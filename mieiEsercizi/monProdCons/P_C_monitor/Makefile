MNTLIB=../monitor/monitor.o

all: p_c_monitor

p_c_monitor: p_c_monitor.o monitor.o
	gcc -o p_c_monitor p_c_monitor.o procedure.o $(MNTLIB)

p_c_monitor.o: p_c_monitor.c header.h
	gcc -c p_cmonitor.c

procedure.o: procedure.c header.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f *~
	rm -f *kdev*
