# Eamon Tracey (etracey)
# FundComp Lab 9 Makefile
#
# Compile Lab 9
#

all: symbol bounce funanim

symbol: symbol.c 
	gcc -Wall symbol.c gfx_mac.o -lX11 -lm -o symbol

bounce: bounce.c 
	gcc -Wall bounce.c gfx_mac.o -lX11 -o bounce

funanim: funanim.c 
	gcc -Wall funanim.c gfx_mac.o -lX11 -lm -o funanim

clean:
	rm symbol bounce funanim

