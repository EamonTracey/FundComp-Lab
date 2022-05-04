# Eamon Tracey (etracey)
# FundComp Lab 7 (1) Makefile
# 
# Compile program to path
#

path: path.o points.o
	gcc path.o points.o -lm -o path

path.o: path.c
	gcc -Wall -c path.c -o path.o

points.o: points.c
	gcc -Wall -c points.c -o points.o

clean:
	rm *.o
	rm path
