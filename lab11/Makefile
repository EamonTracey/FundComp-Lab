# Eamon Tracey (etracey)
# FundComp Lab 11 Final Makefile
#
# Compile mini final project
#

project: project.o  gfx2_mac.o
	gcc -Wall project.o gfx2_mac.o -lX11 -o project

project.o: project.c project.h
	gcc -Wall -c project.c -o project.o

clean:
	rm project.o
	rm project
