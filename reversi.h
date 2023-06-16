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


// table
void reversiSetting(int y1, int x1, int y2, int x2, int row, int col);
void checkSize(int row, int col)

// client
int connect_ipaddr_port (const char * ip, int port);
void chat (int conn_fd);

// server
int listen_at_port (int portnum);
void chat (int conn_fd);

// start
void startServer(int y1, int x1, int y2, int x2, int row, int col);
void startClient(int row, int col);

// keyboard
void keyBoardMoving(int *y, int *x);

