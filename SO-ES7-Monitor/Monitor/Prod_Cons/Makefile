SUBDIRS = monitor P_C_monitor

all: subs

subs:
	for dir in $(SUBDIRS) ; do make -C $$dir ; done

clean:
	for dir in $(SUBDIRS) ; do make clean -C $$dir ; done
