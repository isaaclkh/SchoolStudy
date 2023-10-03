.PHONY : all
all : tico

tico : tico.o
	gcc tico.o -o tico

tico.o : TICO.c
	gcc -c TICO.c -o tico.o

.PHONY : clean
clean :
	rm -rf tico.o
	rm -rf tico
