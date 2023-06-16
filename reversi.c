#include "../reversi.h"

int main(int argc, char ** argv)
{
    char board[8][8];
    int playable_direction[8][8][8];
    
    int row, col;
    int mode=0; // mode 1 : client, mode 2 : server
    int end=0;

    struct sockaddr_in serv_addr; 
	int sock_fd ;
	int s, len ;
	char buffer[1024] = {0}; 
	char * data ;

    // client
	if (argc == 3) {
		int conn_fd = connect_ipaddr_port(argv[1], atoi(argv[2]));
        mode=1;
        // chatC(conn_fd);
	}

    // server
    if (argc == 2) {
		int conn_fd = listen_at_port(atoi(argv[1]));
        mode=2;
        // chatS(conn_fd);
	}

    // Wrong number of arguments : It should be 2 or 3 ONLY
    if (argc < 2 || argc > 3){
        fprintf(stderr, "Wrong number of arguments\n");
		fprintf(stderr, "Usage:\n\t./reversi [IP addr] [Port num]\n");
        fprintf(stderr, "\t./reversi [Port num]\n");
		exit(EXIT_FAILURE);
    }

    initscr();
    clear();

    getmaxyx(stdscr, row, col);
    checkSize(row, col);

    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    curs_set(3);

    int y = 6, x = 7;
    move(y, x);

    refresh();

    while(end)
    {
        if(mode==1);
        if(mode==2);
    }

    keyBoardMoving(&y, &x);
    
    shutdown(conn_fd, SHUT_RDWR);
    endwin();

    return EXIT_SUCCESS ;
}
