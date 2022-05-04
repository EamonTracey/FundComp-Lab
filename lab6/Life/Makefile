playlife: lifefunc.o playlife.o
	gcc lifefunc.o playlife.o -o playlife

lifefunc.o: lifefunc.c
	gcc -c lifefunc.c -o lifefunc.o

playlife.o: playlife.c lifefunc.h
	gcc -c playlife.c -o playlife.o

clean:
	rm *.o
	rm playlife
