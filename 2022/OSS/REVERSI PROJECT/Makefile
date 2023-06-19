
reversi : table.o reversi.o client.o server.o start.o keyboard.o itoaFunc.o reversiFunc.o
	gcc -o reversi table.o reversi.o client.o server.o start.o keyboard.o itoaFunc.o reversiFunc.o -lncurses

reversi.o : reversi.c
	gcc -c -o reversi.o reversi.c -lncurses

table.o : src/table.c
	gcc -c -o table.o src/table.c -lncurses

start.o : src/start.c
	gcc -c -o start.o src/start.c -lncurses

keyboard.o : src/keyboard.c
	gcc -c -o keyboard.o src/keyboard.c -lncurses

client.o : src/client.c
	gcc -c -o client.o src/client.c

server.o : src/server.c
	gcc -c -o server.o src/server.c

itoaFunc.o : function/itoaFunc.c
	gcc -c -o itoaFunc.o function/itoaFunc.c

reversiFunc.o : function/reversiFunc.c
	gcc -c -o reversiFunc.o function/reversiFunc.c


clean:
	rm *.o reversi
