.PHONY : all
all : mxxd

mxxd : mxxd.o
	gcc mxxd.o -o mxxd

mxxd.o : mxxd.c
	gcc -c mxxd.c -o mxxd.o

.PHONY : clean
clean :
	rm -rf mxxd.o
	rm -rf mxxd
