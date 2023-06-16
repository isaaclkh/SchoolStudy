#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>

int main(int argc, char ** argv)
{
    int row, col;
    int mode=0; // client : mode 1, server : mode 2

    struct sockaddr_in serv_addr; 
	int sock_fd ;
	int s, len ;
	char buffer[1024] = {0}; 
	char * data ;
    
    // client
    if (argc == 3) {
        mode = 1;
        int conn_fd = connect_ipaddr_port(argv[1], atoi(argv[2])) ;
        // chatC(conn_fd) ;
	}

    // server
    if (argc == 2) {
        mode = 2;
		int conn_fd = listen_at_port(atoi(argv[1])) ;
		// chatS(conn_fd) ;
	}

    if (argc < 2 || argc > 3){
        fprintf(stderr, "Wrong number of arguments\n") ;
        fprintf(stderr, "Usage:\n\t./reversi [IP addr] [Port num]\n");
        fprintf(stderr, "\t./reversi [Port num]\n");
        exit(EXIT_FAILURE) ;
    }


    initscr();
    clear();

    getmaxyx(stdscr, row, col);

    checkSize(int row, int col);

    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    curs_set(3);

    int y = 6, x = 7;
    move(y, x);

    refresh();

    keyBoardMoving(&y, &x);

    shutdown(conn_fd, SHUT_RDWR) ;

    endwin();
    return 0;
}
