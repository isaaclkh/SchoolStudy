
reversi : table.o reversi.o client.o server.o
	gcc -o reversi table.o reversi.o client.o server.o -lncurses

table.o : src/table.c
	gcc -c -o table.o src/table.c -lncurses

reversi.o : reversi.c
	gcc -c -o reversi.o reversi.c -lncurses

client.o : src/client.c
	gcc -c -o client.o src/client.c

server.o : src/server.c
	gcc -c -o server.o src/server.c

clean:
	rm table.o reversi.o client.o server.o
