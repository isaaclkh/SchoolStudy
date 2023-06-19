#include "../reversi.h"

int listen_at_port (int portnum) 
{
	int sock_fd = socket(AF_INET /*IPv4*/, SOCK_STREAM /*TCP*/, 0 /*IP*/) ;
	if (sock_fd == 0)  { 
		perror("socket failed : "); 
		exit(EXIT_FAILURE); 
	}
	int opt = 2 ;
	if (setsockopt(sock_fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt)) != 0) {
		fprintf(stderr, "fail at setsockopt\n") ;
		exit(EXIT_FAILURE) ;
	}

	struct sockaddr_in address ; 
	bzero(&address, sizeof(address)) ; 	
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY /* localhost */ ; 
	address.sin_port = htons(portnum); 

	if (bind(sock_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed: "); 
		exit(EXIT_FAILURE); 
	} 

	if (listen(sock_fd, 16 /* the size of waiting queue*/) < 0) { 
		perror("listen failed : "); 
		exit(EXIT_FAILURE); 
	} 

	int addrlen = sizeof(address); 
	int conn_fd = accept(sock_fd, (struct sockaddr *) &address, (socklen_t*)&addrlen) ;
	if (conn_fd < 0) {
		perror("accept failed: "); 
		exit(EXIT_FAILURE); 
	}
	return conn_fd ;
}

void chatS(int conn_fd, int x, int y)
{
	char buf[256];
    char colchar;
    int rown;

	do {
		int s ;
		
		while ( (s = recv(conn_fd, buf, 255, 0)) == 0 ) curs_set(0);
		if (s == -1)
			break ;

		buf[s] = '\0' ;
		// printf(">%s\n", buf) ;
        // buf를 sscanf(buf, "%c%d", &colchar, &rown) 이렇게 받아와서
        // server = 1, client = 2, buf is from client so it is 2
        // board[changeCharToInt(colchar)][rown] = 2;

		fgets(buf, 256, stdin) ;
		buf[strlen(buf) - 1] = '\0' ;
		if (strcmp(buf, "quit()") == 0)
			break ;

		send(conn_fd, buf, strlen(buf), 0) ;

	} while (strcmp(buf, "quit()") != 0) ;
}

void sSend(int x, int y){
	int sendingXY = x*10 + y;
	char buf[100];

	itoa(sendingXY, buf, 10);
	send(e_conn_fd, buf, strlen(buf), 0);
}

void sReceive(){
	int s;
	int XYfromS;
	int x, y;
	char buf[100];

	while ((s = recv(e_conn_fd, buf, 1024, 0)) == 0) curs_set(0);
	buf[s] = '\0';
	XYfromS = atoi(buf);

	board[XYfromS/10][XYfromS%10] = 1; // one : server
}