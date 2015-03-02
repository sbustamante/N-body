CC=gcc
CFLAGS=-g -I. -c

#Principal Program
Nbody.out:data.o physics.o numeric.o distributions.o nbody.o
	gcc -lm data.o physics.o numeric.o distributions.o nbody.o -o Nbody.out
	rm -r *.o

#Initial Conditions Module
IC.out:distributions.o IC.o
	gcc -lm distributions.o IC.o -o IC.out
	rm -r *.o

edit:
	kate *.c *.h &

clean:
	rm -r *.o *.out *.png *.tmp script.gpl
