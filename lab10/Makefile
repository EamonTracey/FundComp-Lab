# Eamon Tracey (etracey)
# FundComp Lab 10 Makefile
#
# Fractals Makefile with compile instructions
#

fractals: fractals.c fractals.h gfx_mac.o gfx.h
	gcc -Wall fractals.c gfx_mac.o -lX11 -lm -o fractals

clean:
	rm fractals 
