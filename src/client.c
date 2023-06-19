#include "../reversi.h"


int connect_ipaddr_port (const char * ip, int port)
{
	int sock_fd ;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0) ;
	if (sock_fd <= 0) {
		perror("socket failed : ") ;
		exit(EXIT_FAILURE) ;
	}
	int opt = 2 ;
	if (setsockopt(sock_fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt)) != 0) {
		fprintf(stderr, "fail at setsockopt\n") ;
		exit(EXIT_FAILURE) ;
	}

	struct sockaddr_in address ;
	bzero(&address, sizeof(address)) ;
	address.sin_family = AF_INET ; 
	address.sin_port = htons(port) ; 
	if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0) {
		perror("inet_pton failed : ") ; 
		exit(EXIT_FAILURE) ;
	} 

	if (connect(sock_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
		perror("connect failed : ") ;
		exit(EXIT_FAILURE) ;
	}
	return sock_fd ;
}


void chatC (int conn_fd, int x, int y)
{
	char buf[256] ;

	do {
		fgets(buf, 256, stdin) ;
		buf[strlen(buf) - 1] = '\0' ;
		if (strcmp(buf, "quit()") == 0)
			break ;

		send(conn_fd, buf, strlen(buf), 0);

		int s ;
		while ((s = recv(conn_fd, buf, 1024, 0)) == 0) curs_set(0);
		if (s == -1)
			break ;
		buf[s] = '\0' ;

		printf(">%s\n", buf) ;
	} while (strcmp(buf, "quit()") != 0) ;
}

void cSend(int x, int y){
	int sendingXY = x*10 + y;
	char buf[100];

	itoa(sendingXY, buf, 10);
	send(e_conn_fd, buf, strlen(buf), 0);
}

void cReceive(){
	int s;
	int XYfromS;
	int x, y;
	char buf[100];

	while ((s = recv(e_conn_fd, buf, 1024, 0)) == 0) curs_set(0);
	buf[s] = '\0';
	XYfromS = atoi(buf);

	board[XYfromS/10][XYfromS%10] = 1; // one : server
}
