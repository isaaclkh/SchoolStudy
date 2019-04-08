C= gcc
CFLAGS = -W -Wall
TARGET = manager
OBJECTS = menu.o main.o user.o
D_OBJECTS = menu_d.o main_d.o user_d.o

all : $(TARGET)

manager_debug : $(D_OBJECTS)
	$(CC) $(CFLAGS) -o $@ ${D_OBJECTS}

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o ${TARGET} ${OBJECTS}

menu_d.o : menu.c
	$(CC) -DDBUG_MODE $(CFLAGS) -c -o $@ $^

main_d.o : main.c
	$(CC) -DDBUG_MODE $(CFLAGS) -c -o $@ $^

user_d.o : user.c
	$(CC) -DDBUG_MODE $(CFLAGS) -c -o $@ $^

clean :
	rm *.o manager manaer_debug 
