INCLUDEDIR = -I/usr/include

all: clean
	swig -autorename $(INCLUDEDIR) -ruby -o vserver.c ../vserver.i
	ruby extconf.rb
	make -f Makefile

clean:
	rm -f vserver.c vserver.so
	rm -f Makefile mkmf.log
