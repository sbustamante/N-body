CC=gcc
CFLAGS=-g -I. -c

#Principal Program
Nbody.out:data.o physics.o numeric.o distributions.o nbody.o
	gcc data.o physics.o numeric.o distributions.o nbody.o -lm -o Nbody.out
	rm -r *.o

#Initial Conditions Module
IC.out:distributions.o IC.o
	gcc distributions.o IC.o -lm -o IC.out
	rm -r *.o

edit:
	kate *.c *.h &

clean:
	rm -r *.o *.out *.png *.tmp script.gpl
