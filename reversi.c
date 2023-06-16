#include "reversi.h"

// board[col][row]
int board[8][8];
// black(client) : 2, white(server) : 1

int main(int argc, char ** argv)
{
    int row, col;
    int mode=0; // client : mode 1, server : mode 2
    int end=0;

    struct sockaddr_in serv_addr; 
	int sock_fd ;
	int s, len ;
	char buffer[1024] = {0}; 
	char * data ;
    int conn_fd;
    
    // client
    if (argc == 3) {
        mode = 1;
        conn_fd = connect_ipaddr_port(argv[1], atoi(argv[2])) ;
        // chatC(conn_fd) ;
	}

    // server
    if (argc == 2) {
        mode = 2;
		conn_fd = listen_at_port(atoi(argv[1])) ;
		// chatS(conn_fd) ;
	}

    if (argc < 2 || argc > 3){
        fprintf(stderr, "Wrong number of arguments\n") ;
        fprintf(stderr, "Usage:\n\t./reversi [IP addr] [Port num]\n");
        fprintf(stderr, "\t./reversi [Port num]\n");
        exit(EXIT_FAILURE) ;
    }

    initial();

    initscr();
    clear();

    getmaxyx(stdscr, row, col);

    checkSize(row, col);
    drawing();

    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    curs_set(3);

    int y = 6, x = 7;
    
    move(y, x);

    refresh();

    while(end){
        drawing();

        if(mode==2) chatS(conn_fd);
        keyBoardMoving(&y, &x);
        if(mode==1) chatC(conn_fd);
        
    }
    

    shutdown(conn_fd, SHUT_RDWR) ;

    endwin();
    return 0;
}
