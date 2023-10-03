#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>

#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <linux/socket.h> 
 
#include <unistd.h>
#include <sys/types.h>

extern int board[8][8]; // board[col][row]
extern int e_conn_fd;
extern int playable_direction[8][8][8];
extern int scores[2];
extern int current_player;

// table
void reversiSetting(int y1, int x1, int y2, int x2, int row, int col);
void drawing();

// client
int connect_ipaddr_port (const char * ip, int port);
void cSend(int x, int y);
void cReceive();

// server
int listen_at_port (int portnum);
void sSend(int x, int y);
void sReceive();

// start
void checkSize(int row, int col);
void initial();

// keyboard
void keyBoardMoving(int *y, int *x, int mode);

// function
char * itoa(int value, char* buffer, int base);
void mark_playable_positions();
int checkEnd();
void display_winner();
int make_next_move(int x, int y);

