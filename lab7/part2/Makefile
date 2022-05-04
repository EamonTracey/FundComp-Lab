# Eamon Tracey (etracey)
# FundComp Lab 7 (2) Makefile
#
# Compile program to usastates
#

usastates: usastates.o states.o
	gcc usastates.o states.o -lm -o usastates

usastates.o: usastates.c
	gcc -Wall -c usastates.c -o usastates.o

states.o: states.c
	gcc -Wall -c states.c -o states.o

clean:
	rm *.o
	rm usastates
