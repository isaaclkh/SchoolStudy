#include "reversi.h"

// board[col][row]
int board[8][8];
// black(client) : 2, white(server) : 1
int e_conn_fd;
int current_player;
int playable_direction[8][8][8];
int scores[2];

int main(int argc, char ** argv)
{
    int row, col;
    int end=1;

    struct sockaddr_in serv_addr; 
	int sock_fd ;
	int s, len ;
	char buffer[1024] = {0}; 
	char * data ;
    
    
    // client
    if (argc == 3) {
        current_player = 1;
        e_conn_fd = connect_ipaddr_port(argv[1], atoi(argv[2])) ;
        // chatC(conn_fd) ;
	}

    // server
    if (argc == 2) {
        current_player = 0;
		e_conn_fd = listen_at_port(atoi(argv[1])) ;
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
        mark_playable_positions();
        drawing();

        if(current_player==0){
            sReceive();
            mark_playable_positions();
            drawing();
        }
        
        keyBoardMoving(&y, &x, current_player);

        if(current_player==1){
            cReceive();
            mark_playable_positions();
            drawing();
        }

        end = checkEnd();
        
    }
    

    shutdown(e_conn_fd, SHUT_RDWR) ;
    display_winner();

    endwin();
    return 0;
}
