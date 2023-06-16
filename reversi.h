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

extern int board[8][8];


// table
void reversiSetting(int y1, int x1, int y2, int x2, int row, int col);
void drawing();

// client
int connect_ipaddr_port (const char * ip, int port);
void chatC(int conn_fd, int x, int y);

// server
int listen_at_port (int portnum);
void chatS(int conn_fd, int x, int y);
int changeCharToInt(char c);

// start
void checkSize(int row, int col);
void initial();

// keyboard
void keyBoardMoving(int *y, int *x);

