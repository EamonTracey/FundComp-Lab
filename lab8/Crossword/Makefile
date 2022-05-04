# Eamon Tracey (etracey)
# FundComp Lab 8
#
# Makefile
#

crossword: crossword.o crossfuncs.o
	gcc -Wall crossword.o crossfuncs.o -o crossword

crossword.o: crossfuncs.c
	gcc -Wall -c crossword.c -o crossword.o

crossfuncs.o: crossfuncs.c crossfuncs.h
	gcc -Wall -c crossfuncs.c -o crossfuncs.o

clean:
	rm *.o
	rm crossword